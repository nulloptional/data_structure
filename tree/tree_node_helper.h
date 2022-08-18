#include"..\my_concepts\my_concept.h"
#include<algorithm>

#ifndef Tree_Node_Helper_H
#define Tree_Node_Helper_H
#pragma once

//---------------------------Normal Tree----------------------------------
template<BinaryTreeNode T>
inline void set_left(T* parent,T* left=nullptr)
{
    parent->left=left;
}

template<BinaryTreeNode T>
inline void set_right(T* parent,T* right=nullptr)
{
    parent->right=right;
}

template<BinaryTreeNode T>
inline void set_parent(T* child,T* parent=nullptr)
{
    child->parent=parent;
}

template<BinaryTreeNode T>
void as_left (T* parent,T* left=nullptr)
{
    parent->left=left;
    if(left)
        left->parent=parent;
}


template<BinaryTreeNode T>
void as_right(T* parent,T* right=nullptr)
{
    parent->right=right;
    if(right)
        right->parent=parent;
}



template<BinaryTreeNode T>
bool is_left_child(T* parent,T* node)
{
    return parent->left==node;
}

template<BinaryTreeNode T>
bool is_right_child(T* parent,T* node)
{
    return parent->right==node;
}



template<BinaryTreeNode T>
inline bool has_left(T* node)
{
    return node->left;
}

template<BinaryTreeNode T>
inline bool has_right(T* node)
{
    return node->right;
}

template<BinaryTreeNode T>
inline bool is_root(T* node)
{
    return node->parent==nullptr;
}

template<BinaryTreeNode T>
bool has_child(T* node)
{
    return has_left(node)||has_right(node);
}

//插入节点到以root为根的二叉树结构中
template<BinaryTreeNode T,typename Comp=std::less<typename T::value_type>>
T* node_insert_base_impl(T* root,T* to_insert,Comp cmp={})
{
    using node_type=T;
    using node_ptr=node_type*;

    if(!root)
    {
        return to_insert;
    }
    node_ptr cur=root;
    while(has_child(cur))
    {
        if(cmp(cur->data,to_insert->data))
        {
            if(has_right(cur))
                cur=cur->right;
            else
            {
                as_right(cur,to_insert);
                return root;
            }
        }else{
            if(has_left(cur))
                cur=cur->left;
            else{
                as_left(cur,to_insert);
                return root;
            }
        }
    }

    if (cmp(cur->data, to_insert->data))
        as_right(cur, to_insert);
    else
        as_left(cur, to_insert);

    return root;
}

//生成普通的二叉树
template<BinaryTreeNode T,typename Iter>
T* make_base_binary_tree(Iter begin,Iter end)
{
    using node_type=T;
    using node_ptr=node_type*;
    if(begin==end)
        return nullptr;
    node_ptr root=new node_type{*begin};
    for(auto p=++begin;p!=end;++p)
    {
        node_ptr tmp=new node_type{*p};
        node_insert_base_impl(root,tmp);
    }
    return root;
}

//前序遍历
template <BinaryTreeNode T, typename Ostream>
void pre_order_seq(T *root, Ostream &os)
{
    if (root)
    {
        os << root->data << " ";
        pre_order_seq(root->left, os);
        pre_order_seq(root->right, os);
    }
}

//中序遍历
template <BinaryTreeNode T, typename Ostream>
void mid_order_seq(T *root, Ostream &os)
{
    if (root)
    {
        mid_order_seq(root->left, os);
        os << root->data;
        mid_order_seq(root->right, os);
    }
}

//后序遍历
template <BinaryTreeNode T, typename Ostream>
void post_order_seq(T *root, Ostream &os)
{
    if (root)
    {
        post_order_seq(root->left, os);
        post_order_seq(root->right, os);
        os << root->data << " ";
    }
}

//节点深度
template<BinaryTreeNode T>
size_t height_of_node(T* node)
{
    if(!node)
        return 0;
    size_t lh=height_of_node(node->left);
    size_t rh=height_of_node(node->right);
    return lh>rh?lh+1:rh+1;
}

// //左右子树高度差>1
// template<BinaryTreeNode T>
// bool is_unbalance(T* node)
// {
//     return std::abs(height_diff_of_child_node(node))>1;
// }

// //子树高度差
// template<BinaryTreeNode T>
// int height_diff_of_child_node(T* node)
// {
//     if(!node)
//         return 0;
//     size_t lh=height_of_node(node->left);
//     size_t rh=height_of_node(node->right);
//     return static_cast<int>(lh-rh);
// }

//-----------------AVL Tree----------------------------------




// //ll型旋转
// template<BinaryTreeNode T>
// T* ll_rotate(T* grandpa)
// {
//     return right_rotate(grandpa,grandpa->left); 
// }

// //lr型旋转
// template<BinaryTreeNode T>
// T* lr_rotate(T* grandpa)
// {
//     left_rotate(grandpa->left,grandpa->left->right);
//     return right_rotate(grandpa,grandpa->left);

// }

// //rl型旋转
// template<BinaryTreeNode T>
// T* rl_rotate(T* grandpa)
// {
//     right_rotate(grandpa->right,grandpa->right->left);
//     return left_rotate(grandpa,grandpa->right);
// }

// //rr型旋转
// template<BinaryTreeNode T>
// T* rr_rotate(T* grandpa)
// {
//     return left_rotate(grandpa,grandpa->right);
// }

// //将parent左旋成child的左孩子
// template<BinaryTreeNode T>
// T* left_rotate(T* parent,T* child)
// {
//     using node_type=T;
//     using node_ptr=node_type*;

//     node_ptr gp=parent->parent;
//     node_ptr bro=parent->left;
//     node_ptr left=child->left;
//     //1.连接gp和child
//     {
//         child->parent=gp;
//         if(gp)
//         {
//             if(is_left_child(gp,parent))
//                 gp->left=child;
//             else
//                 gp->right=child;
//         }
//     }

//     //2.连接parent和child
//     {
//         as_left(child,parent);
//     }

//     //3.连接parent和right
//     {
//         as_right(parent,left);
//     }
    
//     return child;
    
// }

// //将parent右旋至child的左孩子
// template<BinaryTreeNode T>
// T* right_rotate(T* parent,T* child)
// {
//     using node_type=T;
//     using node_ptr=node_type*;

//     node_ptr gp=parent->parent;
//     node_ptr bro=parent->right;
//     node_ptr right=child->right;
//     //连接gp和child
//     {
//         child->parent = gp;
//         if (gp)
//         {
//             if (is_left_child(gp, parent))
//                 gp->left=child;
//             else
//                 gp->right=child;
//         }
//     }
//     //连接parent和child
//     {
//         as_right(child,parent);
//     }

//     //连接parent和left
//     {
//         as_left(parent,right);
//     }

//     return child;
// }

// template<BinaryTreeNode T>
// bool is_ll_unbalance(T* gp)
// {
//     if((!gp)||(!gp->left))
//         return false;
//     if(height_diff_of_child_node(gp)==2)
//     {
//         if(height_diff_of_child_node(gp->left)==1)
//         {
//             return true;
//         }
//     }
//     return false;
// }

// template<BinaryTreeNode T>
// bool is_rr_unbalance(T* gp)
// {
//     if((!gp)||(!gp->right))
//         return false;
//     if(height_diff_of_child_node(gp)==-2)
//     {
//         if(height_diff_of_child_node(gp->right)==-1)
//             return true;
//     }
//     return false;
// }

// //AVL树的插入
// template<BinaryTreeNode T,typename Cmp=std::less<typename T::value_type>>
// T* node_insert_avl_impl(T* root,T* to_insert)
// {
//     using node_type=T;
//     using node_ptr =node_type*;

//     if(!root)
//         return to_insert;
    
//     node_insert_base_impl(root,to_insert);

//     node_ptr child=to_insert;
//     node_ptr p=to_insert->parent;
//     node_ptr gp=p->parent;

//     if(!gp)
//         return root;

//     while (gp)
//     {
//         if (is_node_start_to_unbalance(gp))
//         {
//             if (is_left_child(gp, p))
//             {
//                 if (is_left_child(p, child))
//                 {
//                     // ll型不平衡
//                     ll_rotate(gp);
//                     if (root == gp)
//                         root = p;
//                 }
//                 else
//                 {
//                     // lr型不平衡
//                     lr_rotate(gp);
//                     if (root == gp)
//                         root = child;
//                 }
//             }
//             else
//             {
//                 if (is_right_child(p, child))
//                 {
//                     // rr型不平衡
//                     rr_rotate(gp);
//                     if (root == gp)
//                         root = p;
//                 }
//                 else
//                 {
//                     // rl型不平衡
//                     rl_rotate(gp);
//                     if (root == gp)
//                         root = child;
//                 }
//             }
//         }
//         gp=root->parent;
//         p=root;
//         child=p;
//     }

//     return root;
// }

// //构建AVL树
// template<BinaryTreeNode T,typename Iter>
// T* make_binary_avl_tree(Iter begin,Iter end)
// {
//     using node_type=T;
//     using node_ptr=node_type*;

//     if(begin==end)
//         return nullptr;
    
//     node_ptr root=new node_type(*begin);
//     node_ptr tmp=nullptr;
//     for(auto p=++begin;p!=end;++p)
//     {
//         tmp=new node_type{*p};
//         root=node_insert_avl_impl(root,tmp);
//     }
//     return root;
// }
#endif