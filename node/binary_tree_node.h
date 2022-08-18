
#ifndef Binary_Tree_Node_H
#define Binary_Tree_Node_H


template<typename T>
struct binary_tree_node{
    using value_type=T;
    using reference=T&;
    using pointer=T*;
    using node_type=binary_tree_node<T>;
    using node_ptr=node_type*;

    binary_tree_node()
        :data{T{}},parent{nullptr},left{nullptr},right{nullptr}{}

    binary_tree_node(const reference val,node_ptr _parent=nullptr,node_ptr _left=nullptr,node_ptr _right=nullptr)
        :data{val},parent{_parent},left{_left},right{_right}{} 
        
    ~binary_tree_node()
    {
        data.~T();
        parent=left=right=nullptr;
    }

    value_type data;
    node_ptr parent;
    node_ptr left;
    node_ptr right;
};

template<typename T>
bool operator==(const binary_tree_node<T>& lhs,const binary_tree_node<T>& rhs)
{
    return lhs.data==rhs.data&&lhs.parent==rhs.parent&&lhs.left==rhs.left&&lhs.right==rhs.right;
}

template<typename T>
bool operator!=(const binary_tree_node<T>& lhs,const binary_tree_node<T>& rhs)
{
    return !(lhs==rhs);
}

template<typename T>
bool operator<(const binary_tree_node<T>& lhs,const binary_tree_node<T>& rhs)
{
    return lhs.data<rhs.data;
}

template<typename T>
bool operator>(const binary_tree_node<T>& lhs,const binary_tree_node<T>& rhs)
{
    return lhs.data>rhs.data;
}
#endif