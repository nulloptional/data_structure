#include"..\node\forward_node.h"
#include"..\node\node_helper.h"
#include<iterator>
#include<type_traits>
#ifndef Chain_Queue_H
#define Chain_Queue_H
template<typename T>
class chain_queue{
    using value_type=T;
    using reference=T&;
    using pointer=T*;
    using node_type=forward_node<T>;
    using node_ptr=node_type*;

public:
    template<typename Iter>
    chain_queue(Iter beign,Iter end);

    ~chain_queue(){};

public:
    inline bool empty() const{return m_begin==nullptr;}
    void in(const reference val);
    reference out();
#ifdef DEBUG
    void print_details();
#endif
private:
    node_ptr m_begin;
    node_ptr m_tail;
    
};


template<typename T>
template<typename Iter>
chain_queue<T>::chain_queue(Iter begin,Iter end)
{
    using type=typename std::iterator_traits<Iter>::value_type;
    static_assert(std::is_same_v<value_type,type>);
    auto head=make_forward_chain_list<forward_node<type>>(begin,end);
    auto tail=node_tail(head);
    m_begin=head;
    m_tail=tail;
}

template<typename T>
void chain_queue<T>::in(const chain_queue<T>::reference val)
{
    node_ptr tmp=new node_type{val};
    m_tail->next=tmp;
    m_tail=tmp;
}

template<typename T>
chain_queue<T>::reference chain_queue<T>::out()
{
    auto tmp=m_begin;
    m_begin=m_begin->next;
    return tmp->data;
}

#ifdef DEBUG
    template<typename T>
    void chain_queue<T>::print_details()
    {
        print_chain_details(m_begin);
    }
#endif

#endif

