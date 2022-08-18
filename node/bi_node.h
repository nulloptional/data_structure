#include"node_traits.h"
#ifndef bi_node_h
#define bi_node_h
template <typename T>
struct bi_node
{
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using node_category = bidirectional_node_tag;
    using node_type = bi_node<T>;
    using node_ptr = node_type *;

    bi_node(const reference _data,node_ptr _prev=nullptr,node_ptr _next=nullptr):data{_data},prev{_prev},next{_next}{}
    ~bi_node(){data.~T();prev=nullptr,next=nullptr;}

    value_type data;
    node_ptr prev;
    node_ptr next;
};

#endif