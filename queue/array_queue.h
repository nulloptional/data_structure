
//array_queue仍然不需要迭代器的支持，因为其工作方式不需要迭代整个内部空间
//由于数组元素往头元素删除节点时，会导致整个数组的数据前移一个位置，其代价时O(n)，所以这里选择逻辑上的环形队列
#include"..\utils\my_utility.h"
#include<exception>
#include<iterator>
#include<type_traits>
#ifdef DEBUG
    #include<iostream>
#endif

template<typename T,typename Alloc=std::allocator<T>>
class array_queue{
    using value_type=T;
    using reference=value_type&;
    using pointer=value_type*;
    using size_type=std::size_t;
    using allocator_type=Alloc;
public:
    template<typename Iter>
    array_queue(Iter begin,Iter end);

    ~array_queue(){delete[] m_begin_of_storage;m_begin=m_end=m_begin_of_storage=m_end_of_storage=nullptr;}

public:
    void in(const reference val);
    reference out();
    inline bool empty() const{return m_begin==m_end;}

#ifdef DEBUG
    void print_details();
#endif

private:
    bool full() const;
    size_type size() const;
    inline size_type capacity() const{return m_end_of_storage-m_begin_of_storage;}
    inline bool end_ahead() const{return (m_end-m_begin)<0;}
    inline bool begin_ahead() const{return !((m_end-m_begin)<0);}
private:
    static allocator_type s_alloc;
    pointer m_begin;        //队首元素
    pointer m_end;          //队尾元素的后继
    pointer m_begin_of_storage;        //物理内存的起始位置
    pointer m_end_of_storage;   //物理内存的结束位置
};

template<typename T,typename Alloc>
template<typename Iter>
array_queue<T,Alloc>::array_queue(Iter begin,Iter end)
{
    using type=typename std::iterator_traits<Iter>::value_type;
    static_assert(std::is_same_v<value_type,type>);
    size_type sz=end-begin;
    size_type capa=to_alloc_sz(sz);
    auto ptr=s_alloc.allocate(capa);
    auto tmp=ptr;
    for(auto p=begin;p!=end;++p,++tmp)
    {
        *tmp=*p;
    }
    m_begin=ptr;
    m_begin_of_storage=m_begin;
    m_end=m_begin+sz;
    m_end_of_storage=m_begin+capa;
}

template<typename T,typename Alloc>
array_queue<T,Alloc>::size_type array_queue<T,Alloc>::size() const
{
    if(m_begin==m_end)
        return 0;
    else if(m_end>m_begin)
        return m_end-m_begin;
    else
        return (m_end_of_storage-m_begin)+(m_end-m_begin_of_storage);
}

template<typename T,typename Alloc>
bool array_queue<T,Alloc>::full() const
{
    return capacity()-size()==1;
}

template<typename T,typename Alloc>
void array_queue<T,Alloc>::in(const array_queue<T,Alloc>::reference val)
{
    if(full())
    {
        auto sz=size(); //当前容量
        auto len=sz+1;  
        auto new_capa=to_alloc_sz(len);
        auto ptr=s_alloc.allocate(new_capa);

        if(end_ahead())
        {
            std::copy(m_begin,m_end_of_storage,ptr);
            std::copy(m_begin_of_storage,m_end,ptr+(m_end_of_storage-m_begin));
        }else{
            std::copy(m_begin,m_end,ptr);
        }

        delete[] m_begin_of_storage;

        m_begin_of_storage=ptr;
        m_begin=m_begin_of_storage;
        m_end_of_storage=m_begin_of_storage+new_capa;
        m_end=m_begin+sz;
    }

    *m_end=val;
    ++m_end;
}

template<typename T,typename Alloc>
array_queue<T,Alloc>::reference array_queue<T,Alloc>::out()
{
    if(empty())
        throw std::logic_error{"empty queue"};
    
    
    auto tmp=m_begin;
    ++m_begin;
    return *tmp;
}

#ifdef DEBUG
template<typename T,typename Alloc>
void array_queue<T,Alloc>::print_details()
{
    std::cout<<"head:::";
    if(end_ahead())
    {
        for(auto p=m_begin;p!=m_end_of_storage;++p)
        {
            std::cout<<*p<<" ";
        }
        for(auto p=m_begin_of_storage;p!=m_end;++p)
        {
            std::cout<<*p<<" ";
        }
    }
    else{
        for(auto p=m_begin;p!=m_end;++p)
        {
            std::cout<<*p<<" ";
        }
    }
    std::cout<<":::tail\n";
}

#endif

template<typename T,typename Alloc>
array_queue<T,Alloc>::allocator_type array_queue<T,Alloc>::s_alloc{};