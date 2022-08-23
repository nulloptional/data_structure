
#include"..\..\my_concepts\my_concept.h"
#include<algorithm>

#ifndef Tree_Node_Helper_H
#define Tree_Node_Helper_H
#pragma once

namespace fantasil
{

    namespace details
    {
        //---------------------------Normal Tree----------------------------------

        //使用replace代替be_replaced，但是be_replaced的节点关系不改变，其指针内容不改变
        template <BinaryTreeNode T>
        void replace_node(T *be_replaced, T *replace)
        {
            be_replaced->data = std::move(replace->data);
        }

        template<BinaryTreeNode T>
        void swap_node(T* lhs,T* rhs)
        {
            using value_type=typename T::value_type;
            std::swap(lhs->data,rhs->data);
            std::swap(lhs->parent,rhs->parent);
            std::swap(lhs->left,rhs->left);
            std::swap(lhs->right,rhs->data);
        }

        template <BinaryTreeNode T>
        inline void set_left(T *parent, T *left = nullptr)
        {
            parent->left = left;
        }

        template <BinaryTreeNode T>
        inline void set_right(T *parent, T *right = nullptr)
        {
            parent->right = right;
        }

        template <BinaryTreeNode T>
        inline void set_parent(T *child, T *parent = nullptr)
        {
            child->parent = parent;
        }

        template <BinaryTreeNode T>
        void as_left(T *parent, T *left = nullptr)
        {
            parent->left = left;
            if (left)
                left->parent = parent;
        }

        template <BinaryTreeNode T>
        void as_right(T *parent, T *right = nullptr)
        {
            parent->right = right;
            if (right)
                right->parent = parent;
        }

        template <BinaryTreeNode T>
        bool is_left_child(T *parent, T *node)
        {
            return parent->left == node;
        }

        template <BinaryTreeNode T>
        bool is_right_child(T *parent, T *node)
        {
            return parent->right == node;
        }

        template <BinaryTreeNode T>
        inline bool has_left(T *node)
        {
            return node->left;
        }

        template <BinaryTreeNode T>
        inline bool has_right(T *node)
        {
            return node->right;
        }

        template <BinaryTreeNode T>
        inline bool has_left_only(T *node)
        {
            return has_left(node) && !has_right(node);
        }

        template <BinaryTreeNode T>
        inline bool has_right_only(T *node)
        {
            return has_right(node) && !has_left(node);
        }

        template <BinaryTreeNode T>
        inline bool has_two_child(T *node)
        {
            return has_left(node) && has_right(node);
        }

        template <BinaryTreeNode T>
        inline bool has_one_child_only(T *node)
        {
            return has_left_only(node)||has_right_only(node);
        }

        template <BinaryTreeNode T>
        inline bool is_root(T *node)
        {
            return node->parent == nullptr;
        }

        template <BinaryTreeNode T>
        inline bool is_leaf(T *node)
        {
            return !has_child(node);
        }

        template <BinaryTreeNode T>
        bool has_child(T *node)
        {
            return has_left(node) || has_right(node);
        }

         //最左节点
        template<BinaryTreeNode T>
        T* most_left_node(T* root)
        {
            using node_type=T;
            using node_ptr=node_type*;

            node_ptr cur=root;
            while(cur->left)
            {
                cur=cur->left;
            }
            return cur;
        }

        //最右节点
        template<BinaryTreeNode T>
        T* most_right_node(T* root)
        {
            using node_type=T;
            using node_ptr=node_type*;

            node_ptr cur=root;
            while(cur->right)
            {
                cur=cur->right;
            }
            return cur;
        }

        //向下追溯前驱节点
        template <BinaryTreeNode T>
        T *trace_down_of_prev(T *node)
        {
            using node_type = T;
            using node_ptr = node_type *;

            node_ptr left = node->left;
            
            return most_right_node(left);
        }

        //向上追溯前驱节点
        template <BinaryTreeNode T>
        T *trace_up_of_prev(T *node)
        {
            using node_type = T;
            using node_ptr = node_type *;

            node_ptr cur = node;
            node_ptr p = cur->parent;
            while (p)
            {
                if (is_right_child(p, cur))
                    return p;
                else
                {
                    cur = p;
                    p = cur->parent;
                }
            }
            return nullptr;
        }

        //向下追溯后继节点
        template <BinaryTreeNode T>
        T *trace_down_of_next(T *node)
        {
            using node_type = T;
            using node_ptr = node_type *;

            node_ptr right = node->right;

            
            return most_left_node(right);
        }

        //向上追溯后继节点
        template <BinaryTreeNode T>
        T *trace_up_of_next(T *node)
        {
            using node_type = T;
            using node_ptr = node_type *;

            node_ptr cur = node;
            node_ptr p = cur->parent;
            while (p)
            {
                if (is_left_child(p, cur))
                    return p;
                else
                {
                    cur = p;
                    p = cur->parent;
                }
            }
            return nullptr;
        }

        //前驱节点
        template <BinaryTreeNode T>
        T *node_base_prev(T *node)
        {
            if (has_left(node))
                return trace_down_of_prev(node);
            else
                return trace_up_of_prev(node);
        }

        //后继节点
        template <BinaryTreeNode T>
        T *node_base_next(T *node)
        {
            if (has_right(node))
                return trace_down_of_next(node);
            else
                return trace_up_of_next(node);
        }

       

        //插入节点到以root为根的二叉树结构中
        template <BinaryTreeNode T, typename Comp = std::less<typename T::value_type>>
        T *node_insert_base_impl(T *root, T *to_insert, Comp cmp = {})
        {
            using node_type = T;
            using node_ptr = node_type *;

            if (!root)
            {
                return to_insert;
            }
            node_ptr cur = root;
            while (has_child(cur))
            {
                if (cmp(cur->data, to_insert->data))
                {
                    if (has_right(cur))
                        cur = cur->right;
                    else
                    {
                        as_right(cur, to_insert);
                        return root;
                    }
                }
                else
                {
                    if (has_left(cur))
                        cur = cur->left;
                    else
                    {
                        as_left(cur, to_insert);
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

        template <BinaryTreeNode T>
        T *node_erase_base_impl(T *root, T *to_erase)
        {
            using node_type = T;
            using node_ptr = node_type *;

            if (has_child(to_erase))
            {
                //节点不是叶子节点，就是用其前驱/后继节点来替代当前节点，并删除其前驱/后继节点
                //删除的是其前驱/后继节点，该节点不可能是根节点
                node_ptr tmp = nullptr;
                if (has_left(to_erase))
                {
                    tmp = node_base_prev(to_erase);
                }
                else
                {
                    tmp = node_base_next(to_erase);
                }
                replace_node(to_erase, tmp);
                node_ptr p=tmp->parent;
                if(is_left_child(p,tmp))
                    set_left(p);
                else
                    set_right(p);
                delete tmp;
            }
            else
            {
                //节点是叶子节点，直接删除即可，注意节点是根节点时的情况
                if (root == to_erase)
                    root = nullptr;
                delete to_erase;
            }
            return root;
        }

        //生成普通的二叉树
        template <BinaryTreeNode T, typename Iter>
        T *make_base_binary_tree(Iter begin, Iter end)
        {
            using node_type = T;
            using node_ptr = node_type *;
            if (begin == end)
                return nullptr;
            node_ptr root = new node_type{*begin};
            for (auto p = ++begin; p != end; ++p)
            {
                node_ptr tmp = new node_type{*p};
                node_insert_base_impl(root, tmp);
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
                os << root->data<<" ";
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
        template <BinaryTreeNode T>
        size_t height_of_node(T *node)
        {
            if (!node)
                return 0;
            size_t lh = height_of_node(node->left);
            size_t rh = height_of_node(node->right);
            return lh > rh ? lh + 1 : rh + 1;
        }
    }
}

#endif