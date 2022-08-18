#include"binode.h"

template<typename T>
struct chain_linear_list_iter{

    using value_type=T;
    using reference=value_type&;
    using pointer=value_type*;
    using node_type=binode<T>;
    using node_ptr=node_type*;
    using self=chain_linear_list_iter<T>;
    using self_ref=self&;
    using self_ptr=self*;

    chain_linear_list_iter(node_ptr _ptr=nullptr):ptr{_ptr}{}
    ~chain_linear_list_iter(){}

    self_ref operator++(){ptr=ptr->next;return *this;}
    self_ref operator--(){ptr=ptr->prev;return *this;}
    self operator++(int){auto tmp=*this;tmp.ptr=tmp.ptr->next;return tmp;}
    self operator--(int){auto tmp=*this;tmp.ptr=tmp.ptr->prev;return tmp;}


    reference operator*(){return ptr->val;}
    pointer operator->(){return ptr;}
    
    self tail(){return chain_linear_list_iter{node_tail(ptr)};}
    const self tail() const{return chain_linear_list_iter{node_tail(ptr)};}
    size_t distance(const self& rhs){return node_distance(ptr,rhs.ptr);}

    node_ptr ptr;
};

template<typename T>
bool operator==(const chain_linear_list_iter<T>& lhs,const chain_linear_list_iter<T>& rhs)
{
    return lhs.ptr==rhs.ptr;
}

template<typename T>
bool operator!=(const chain_linear_list_iter<T>& lhs,const chain_linear_list_iter<T>& rhs)
{
    return lhs.ptr!=rhs.ptr;
}

template<typename T>
size_t operator-(const chain_linear_list_iter<T>& lhs,const chain_linear_list_iter<T>& rhs)
{
    return node_distance(rhs.ptr,lhs.ptr);
}


