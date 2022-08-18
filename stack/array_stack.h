#define DEBUG

#ifdef DEBUG
    #include<iostream>
#endif

#include"..\utils\my_utility.h"
#include<exception>



template<typename T,typename Alloc=std::allocator<T>>
class array_stack{
    using value_type=T;
    using reference=T&;
    using pointer=T*;
    using size_type=std::size_t;
    using allocator_type=Alloc;
public:
    array_stack(size_type _capacity=16):m_capacity{_capacity}
    {
        m_ptr=s_alloc.allocate(m_capacity);
        m_sz=0;
    }

    template<typename Iter>
    array_stack(Iter begin,Iter end)
    {
        using type=std::iterator_traits<Iter>::value_type;
        static_assert(std::is_same_v<value_type,type>);
        size_type len=end-begin;
        m_capacity=to_alloc_sz(len);
        m_ptr=s_alloc.allocate(m_capacity);
        m_sz=0;
        for(auto p=begin;p!=end;++p)
        {
            push(*p);
        }
    }

    ~array_stack()
    {
        delete[] m_ptr;
        m_sz=0;
        m_capacity=0;
    }

public:
    inline bool empty() const{return m_sz==0;}
    //栈顶元素
    reference top()
    {
        if(empty())
        {
            throw std::logic_error{"empty stack;"};
        }
        size_type tail=m_sz-1;
        return *(m_ptr+tail);
    }
    //入栈
    void push(const reference val)
    {
        if(full())
        {
            size_type new_capacity=to_alloc_sz(m_capacity+1);
            pointer tmp=s_alloc.allocate(new_capacity);
            m_capacity=new_capacity;
            std::copy(m_ptr,m_ptr+m_sz,tmp);
           delete[] m_ptr;
           m_ptr=tmp;
        }

        *(m_ptr+m_sz)=val;
        ++m_sz;
    }
    //出栈
    void pop()
    {
        size_type tail=m_sz-1;
        (m_ptr+tail)->~T();
        --m_sz;
    }

//DebugMode模式查看内部细节
#ifdef DEBUG
    template<typename OStream>
    OStream& stack_details(OStream & os)
    {
        os<<"bottom:";
        size_t q=0;
        pointer p=m_ptr;
        while(q<m_sz)
        {
            os<<*p<<",";
            ++q;++p;
        }
        os<<"top;";
        os<<"  size:"<<m_sz<<" capacity:"<<m_capacity<<"\n";
        return os;
    }
#endif

private:
    inline bool full() const{return m_sz==m_capacity;}
private:
    static allocator_type s_alloc;
    pointer m_ptr;
    size_type m_sz;
    size_type m_capacity;
};

template<typename T,typename Alloc>
Alloc array_stack<T,Alloc>::s_alloc{};
