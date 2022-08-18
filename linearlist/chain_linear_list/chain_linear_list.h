#include"chain_linear_list_iter.h"
#include<iterator>
#include<type_traits>
#include<exception>
#ifdef DEBUG
    #include<iostream>
#endif


template<typename T>
class chain_linear_list{
    using iterator=chain_linear_list_iter<T>;
    using value_type=T;
    using reference=T&;
    using pointer=T*;
    using difference_type=std::size_t;
    using iterator_category=std::bidirectional_iterator_tag;

    using size_type=std::size_t;
    //node
    using node_type=binode<T>;
    using node_ptr=node_type*;


public:
    //
    template<typename Iter>
    chain_linear_list(Iter _begin,Iter _end)
    {
        node_ptr head=make_chain_list(_begin,_end);
        m_begin.ptr=head;
        m_end.ptr=nullptr;
        m_sz=node_distance(head);
    }
    //
    ~chain_linear_list()
    {
        if(!empty())
        {
            desconstruct(m_begin.ptr);
        }
    }

public:
    iterator begin() noexcept {return m_begin;}
    const iterator begin() const noexcept{return m_begin;}
    iterator end() noexcept{return m_end;}
    const iterator end()    const noexcept{return m_end;}
    size_type size() const noexcept{return m_sz;}
    bool empty() const noexcept{return m_begin==m_end;}
    iterator tail() {return m_begin.tail();}
    const iterator tail() const noexcept{return m_begin.tail();}

public:
    template<typename Iter>
    void insert(Iter _begin,Iter _end,iterator pos)
    {
        // using type = typename std::iterator_traits<Iter>::value_type;
        // if (!std::is_same_v<value_type, type>)
        // {
        //     throw std::exception{};
        // }

        // iterator prev = pos;
        // iterator next = ++pos;
        // if (std::is_same_v<Iter, iterator>)
        // {
        //     iterator _tail = tail(_begin);
        //     prev.ptr->next = _begin.ptr;
        //     _begin.ptr->prev = prev;
        //     _tail.ptr->next = next.ptr;
        //     next.ptr->prev = _tail.ptr;
        //     size_t d = distance(_begin, _end);
        //     m_sz += d;
        // }
        // else
        // {
        //     node_ptr cur = new node_type{*_begin};
        //     node_ptr next = nullptr;
        //     for (auto p = ++_begin; p != _end; ++p)
        //     {
        //         next = new node_type{*p};
        //         cur->next = next;
        //         next->prev = cur;
        //         cur = next;
        //         ++m_sz;
        //     }
        //     m_end.ptr = nullptr;
        // }
        node_insert(pos.ptr,_begin,_end);
        m_sz+=(_end-_begin);
        
    }

    void erase(iterator _begin,iterator  _end)
    {
        if(m_begin==_begin)
            m_begin=_end;
        m_sz-=(_end-_begin);
        node_erase(_begin.ptr,_end.ptr);
    }

private:
    iterator m_begin;
    iterator m_end;
    size_type m_sz;
};


template<typename T,typename ostream>
ostream& operator<<(const chain_linear_list<T>& list,ostream& os)
{
    for(auto p=list.begin();p!=list.end();++p)
    {
        os<<*p<<" ";
    }
    return os;
}

#ifdef DEBUG
    template<typename T,typename ostream>
    void print_list_detail(const chain_linear_list<T>& list,ostream& os)
    {
        using iterator =chain_linear_list_iter<T>;
        iterator p{};
        p=list.begin();
        os<<"head:"<<*p<<"\n";
        p=list.tail();
        os<<"tail:"<<*p<<"\n";
        os<<"size:"<<list.size()<<"\n";
        operator<<(list,os);
        os<<"\n";

    }
#endif




