#include<algorithm>
#include<iterator>

template<typename T>
struct binary_tree_node{
    using value_type=T;
    using reference=T&;
    using const_reference=const reference;
    using pointer=T*;
    using node_type=binary_tree_node<T>;
    using node_ptr=node_type*;

    binary_tree_node(const_reference _val,node_ptr p=nullptr,node_ptr l=nullptr,node_ptr r=nullptr):val{_val},parent{p},left{l},right{r}{}
    ~binary_tree_node()
    {
        parent=left=right=nullptr;
        val.~T();
    }
    node_ptr parent;
    node_ptr left;
    node_ptr right;
    value_type val;
};

//左孩子
template<typename T>
binary_tree_node<T>* tree_node_left(binary_tree_node<T>* cur)
{
    return cur->left;
}

//右孩子
template<typename T>
binary_tree_node<T>* tree_node_right(binary_tree_node<T>* cur)
{
    return cur->right;
}

//父节点
template<typename T>
binary_tree_node<T>* tree_node_parent(binary_tree_node<T>* cur)
{
    return cur->parent;
}

//作为左孩子
template<typename T>
void as_left(binary_tree_node<T>* parent,binary_tree_node<T>* left)
{
    parent->left=left;
    left->parent=parent;
}

//作为右孩子
template<typename T>
void as_right(binary_tree_node<T>* parent,binary_tree_node<T>* right)
{
    parent->right=right;
    right->parent=parent;
}

//是否有左孩子
template<typename T>
bool has_left(binary_tree_node<T>* node)
{
    if(node&&node->left)
        return true;
    return false;
}

//是否有右孩子
template<typename T>
bool has_right(binary_tree_node<T>* node)
{
    if(node&&node->right)
        return true;
    return false;
}

//是否有父节点
template<typename T>
bool has_parent(binary_tree_node<T>* node)
{
    if(node&&node->parent)
        return true;
    return false;
}

//是否有孩子
template<typename T>
bool has_child(binary_tree_node<T>* node)
{
    return has_left(node)||has_right(node);
}

//是否是根节点
template<typename T>
bool is_root(binary_tree_node<T>* node)
{
    return !has_parent(node);
}

//插入一个节点
template<typename T,typename Comp=std::less<T>>
void node_insert_impl(binary_tree_node<T>* root,binary_tree_node<T>* node)
{
    using node_type=binary_tree_node<T>;
    using node_ptr=node_type*;
    node_ptr cur=root;
    while(has_child(cur))
    {
        if(Comp(cur,node))
            cur=cur->left;
        else
            cur=cur->right;
    }
    if(Comp(cur,node))
        as_left(cur,node);
    else
        as_right(cur,node);
}

//形成一棵普通的二叉树
template<typename T,typename Iter,typename Comp=std::less<T>>
binary_tree_node<T>* make_tree(Iter begin,Iter end)
{
    using value_type=typename std::iterator_traits<Iter>::value_type;
    using node_type=binary_tree_node<T>;
    using node_ptr=node_type*;
    
    static_assert(std::is_same_v<T,value_type>);
    
}
