#include"node_traits.h"
#ifndef forward_node_h
#define forward_node_h
// forward_node是最简单的节点
template <typename T>
struct forward_node
{
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using node_category = forward_node_tag;
    using node_type = forward_node<T>;
    using node_ptr = node_type *;
    
    forward_node(const reference _data,node_ptr _next=nullptr):data{_data},next{_next}{};
    ~forward_node(){data.~T();next=nullptr;}
    value_type data;
    node_ptr next;
};
#endif