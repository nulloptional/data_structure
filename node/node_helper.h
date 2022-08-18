#include<iostream>
#include"..\my_concepts\my_concept.h"

#ifndef node_helper_h
#define node_helper_h
#pragma once


//节点之间的逻辑距离
template<Node T>
size_t distance_of_node(T* begin,T* end=nullptr)
{
    size_t distance{0};
    while(begin!=end)
    {
        begin=begin->next;
        ++distance;
    }
    return distance;
}

//给定节点，返回尾节点
template<Node T>
T* node_tail(T* node)
{
    using node_type=T;
    using node_ptr=T*;
    node_ptr cur=node;
    while(cur->next)
    {
        cur=cur->next;
    }
    return cur;
}

//给定节点，返回头节点
template<BiNode T>
T* node_head(T* node)
{
    using node_type=T;
    using node_ptr=T*;
    node_ptr cur=node;
    while(cur->prev)
    {
        cur=cur->prev;
    }
    return cur;
}

//将普通节点串联成单向链表
template<Node T,typename Iter>
T* make_forward_chain_list(Iter begin, Iter end)
{
    using value_type = std::iterator_traits<Iter>::value_type;
    using type = typename T::value_type;
    static_assert(std::is_same_v<value_type, type>);    //数据类型必须相同
    using node_type = T;
    using node_ptr = T *;
    node_ptr head = nullptr;
    if (begin!=end)
        head = new node_type{*begin};
    else
        return head;    //序列为空是返回空指针
    node_ptr cur = head;
    node_ptr next = nullptr;
    for(auto p=++begin;p!=end;++p)
    {
        next=new node_type{*p};
        cur->next=next;
        cur=next;
    }
    return head;
}

//将双向节点串联成链表
template<BiNode T,typename Iter>
T* make_bidirection_chain_list(Iter begin,Iter end)
{
    using value_type = std::iterator_traits<Iter>::value_type;
    using type = typename T::value_type;
    static_assert(std::is_same_v<value_type, type>);    //数据类型必须相同
    using node_type = T;
    using node_ptr = T *;
    node_ptr head = nullptr;
    if (begin!=end)
        head = new node_type{*begin};
    else
        return head;    //序列为空是返回空指针
    node_ptr cur = head;
    node_ptr next = nullptr;
    for(auto p=++begin;p!=end;++p)
    {
        next=new node_type{*p};
        cur->next=next;
        next->prev=cur;
        cur=next;
    }
    return head;
}

//作为后继节点
template<Node T>
inline void as_next(T* cur,T* next)
{
    cur->next=next;
}

//作为前驱节点
template<Node T>
inline void as_prev(T* cur,T* prev)
{
    cur->prev=prev;
}

template<Node T>
void insert_of_forward_node_impl(T* pos,T* head)
{
    auto next=pos->next;
    auto tail=node_tail(head);
    as_next(pos,head);
    as_next(tail,next);
}

//作为单向节点插入
template<Node T,typename Iter>
void insert_of_forward_node(T* pos,Iter begin,Iter end)
{
    if(begin==end)
        return;
    auto head=make_forward_chain_list<T>(begin,end);
    insert_of_forward_node_impl(pos,head);
}

template<BiNode T>
void insert_of_bi_node_impl(T* pos,T* head)
{
    auto r_head=pos->next;
    auto m_tail=node_tail(head);
    as_next(pos,head);
    as_prev(head,pos);
    as_next(m_tail,r_head);
    if(r_head)
        as_prev(r_head,m_tail);
    
}

//找到单向节点的前驱节点
template<Node T>
T* find_prev(T* head,T* node)
{
    auto cur=head;
    if(head==node)
        return nullptr;
    while(cur->next)
    {
        if(cur->next==node)
            return cur;
        cur=cur->next;
    }
    return nullptr;
}

template<Node T>
void deconstruct_nodes(T* begin,T* end=nullptr)
{
    if(begin==end)
        return;
    auto cur=begin;
    auto next=cur->next;
    while(next!=end)
    {
        delete cur;
        cur=next;
        next=cur->next;
    }
}

//删除单向节点
template<Node T>
void erase_forward_nodes(T* head,T* begin,T* end)
{
    if(begin==end)
        return;
    auto l_tail=find_prev(head,begin);
    auto r_begin=end;
    if(l_tail)
        as_next(l_tail,r_begin);
    deconstruct_nodes(begin,end);
}

//删除双向节点
template<BiNode T>
void erase_bi_nodes(T* begin,T* end)
{
    if(begin==end)
        return;
    auto l_tail=begin->prev;
    auto r_begin=end;
    if(l_tail)
        as_next(l_tail,r_begin);
    if(r_begin)
        as_prev(r_begin,l_tail);
    deconstruct_nodes(begin,end);
}

//作为双向节点插入
template<BiNode T,typename Iter>
void insert_of_bi_node(T* pos,Iter begin,Iter end)
{
    if(begin==end)
        return;
    auto head=make_bidirection_chain_list<T>(begin,end);
    insert_of_bi_node_impl(pos,head);
}



template<Node T>
void print_chain_details(T* head)
{
    std::cout<<"----------------------------------------------\n";
    std::cout<<"head:::";
    T* cur=head;
    while(cur)
    {
        std::cout<<cur->data<<" ";
        cur=cur->next;
    }
    std::cout<<":::tail\n";
}

#endif