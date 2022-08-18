
#ifndef node_traits_h
#define node_tratis_h
#pragma once

struct forward_node_tag
{
};
struct bidirectional_node_tag
{
};
struct binary_tree_node_tag
{
};

template <typename Node>
struct node_traits
{
    using node_type = Node;
    using node_ptr = node_type *;
    using value_type = typename Node::value_type;
    using reference = typename Node::reference;
    using pointer = typename Node::pointer;
    using node_category = typename Node::node_category;
};

#endif