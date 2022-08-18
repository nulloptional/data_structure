
#include"array_linear_list_iter.h"
#include<memory>
#include<type_traits>
#include<ranges>
#include<iterator>
#include<exception>
#include<algorithm>

#ifdef DEBUG
    #include<iostream>
    #include<string>
    const std::string head="Debug:";
#endif

std::size_t to_alloc_sz(std::size_t sz)
{
    size_t default_size=16;
    size_t threshold=65535;
    size_t to_alloc=default_size;
    double factor_0=2;
    double factor_1=1.5;
    double near_sacle_0=0.75;
    double near_scale_1=0.95;

    double scale=sz/default_size;
    if(scale>near_sacle_0)
    {
        double scale_2=sz/threshold;
        if(scale_2>near_scale_1)
        {
            to_alloc=sz*factor_1;
        }else{
            to_alloc=sz*factor_0;
        }
    }
    return to_alloc;
}

template<typename T,typename Alloc=std::allocator<T>>
class array_linear_list{

using iterator=array_linear_list_iter<T>;
using value_type=T;
using reference=T&;
using pointer=T*;
using difference_type=std::ptrdiff_t;
using iterator_category=std::random_access_iterator_tag;

using size_type=std::size_t;

public:
template<typename Iter>
array_linear_list(Iter _begin,Iter _end);

~array_linear_list();

//
public:
inline bool empty() {return m_begin==m_end;}
inline size_t size() {return m_end-m_begin;}
inline size_t capacity() {return m_end_of_storage-m_begin;}
inline size_t remain_space() {return m_end_of_storage-m_end;}
iterator begin() noexcept{return m_begin;}
iterator end()  noexcept{return m_end;}
const iterator begin() const noexcept{return m_begin;}
const iterator end() const noexcept{return m_end;}


//
template<typename Iter>
void insert(Iter _begin,Iter _end,iterator pos)
{
    if(!std::is_same<value_type,typename std::iterator_traits<Iter>::value_type>::value)
    {
        throw std::exception{};
    }

    using diff_t=typename std::iterator_traits<Iter>::difference_type;
    diff_t len=_end-_begin;
#ifdef DEBUG
    std::cout<<head<<"to insert sz:"<<len<<std::endl;
#endif
    if(len>remain_space())
    {

        auto cp=to_alloc_sz(size()+len);
#ifdef DEBUG
        std::cout << head << "remain space not enough,to allocate sz" << cp << "\n";
#endif
        auto ptr=s_alloc.allocate(cp);
        auto base=ptr;
        std::copy(m_begin,pos,base);
        base+=(pos-m_begin);
        std::copy(_begin,_end,base);
        base+=len;
        std::copy(pos,m_end,base);
        m_begin.ptr=ptr;
        m_end.ptr=ptr+size()+len;
        m_end_of_storage=ptr+cp;
    }else{
        std::copy_backward(pos,m_end,m_end+len);
        #ifdef DEBUG
            operator<<(*this,std::cout);
        #endif
        std::copy(_begin,_end,pos);
        m_end+=len;
    }
    
}

void erase(iterator _begin,iterator _end)
{
    difference_type len=_end-_begin;
    std::copy(_end,end(),_begin);
    m_end-=len;
}


//
iterator iter_of_index(size_t index) noexcept
{
    auto tmp=m_begin;
    return tmp+=index;
}

const iterator iter_of_index(size_t index) const noexcept
{
    auto tmp=m_begin;
    return tmp+=index;
}


private:
static Alloc s_alloc;
iterator m_begin;
iterator m_end;
iterator m_end_of_storage;
};



template<typename T,typename Alloc>
template<typename Iter>
array_linear_list<T,Alloc>::array_linear_list(Iter _begin,Iter _end)
{
    using iter_tag=typename std::iterator_traits<Iter>::iterator_category;
    using diff_type=typename std::iterator_traits<Iter>::difference_type;
    diff_type sz=_end-_begin;
    size_type to_alloc=to_alloc_sz(sz);
    pointer ptr=s_alloc.allocate(to_alloc);
    std::copy(_begin,_end,ptr);
    m_begin.ptr=ptr;
    m_end.ptr=ptr+sz;
    m_end_of_storage.ptr=ptr+to_alloc;
}

template<typename T,typename Alloc>
array_linear_list<T,Alloc>::~array_linear_list()
{
    if(!std::is_standard_layout_v<T>)
    {
        for(auto p=begin();p!=end();++p)
        {
            (*p).~T();
        }
    }
    s_alloc.deallocate(m_begin.ptr,capacity());
}


template<typename T,typename Alloc,typename Ostream>
Ostream& operator<<(const array_linear_list<T,Alloc>& list,Ostream& os)
{
    for(auto p=list.begin();p!=list.end();++p)
    {
        os<<*p<<" ";
    }
    os<<std::endl;
    return os;
}


template<typename T,typename Alloc>
Alloc array_linear_list<T,Alloc>::s_alloc={};


