#include"tree_node_helper.h"

#ifndef AVL_Binary_Tree_Node_Helper
#define AVL_Binary_Tree_Node_Helper
#pragma once

namespace fantasil
{
    namespace details{

        enum struct avl_unbalance_type{
            type_ll,type_lr,type_rl,type_rr,type_unknown
        };

       

        constexpr int min_diff=2; //高度之差>=2时为不平衡

        //子树高度差
        template <BinaryTreeNode T>
        int height_diff_of_child_node(T *node)
        {
            if (!node)
                return 0;
            size_t lh = height_of_node(node->left);
            size_t rh = height_of_node(node->right);
            return static_cast<int>(lh - rh);
        }

        //左右子树高度差>1
        template <BinaryTreeNode T>
        bool is_unbalance(T *node)
        {
            return std::abs(height_diff_of_child_node(node)) > 1;
        }

        template<BinaryTreeNode T>
        T* trace_up_to_balance(T* root,T* node)
        {
            using node_type=T;
            using node_ptr =node_type*;

            auto diff=height_diff_of_child_node(node);
            if(std::abs(diff)>2)
                throw std::logic_error{"bad node for trace back to balance"};
            
            node_ptr cur=node;
            node_ptr p=cur->parent;
            node_ptr tmp=nullptr;
            avl_unbalance_type type=avl_unbalance_type::type_unknown;
            while(cur)
            {
                if(is_unbalance(cur))
                {
                    type=unbalance_type(cur);
                    switch (type)
                    {
                    case avl_unbalance_type::type_ll:
                        tmp=ll_rotate(cur);
                        break;
                    case avl_unbalance_type::type_lr:
                        tmp=lr_rotate(cur);
                        break;
                    case avl_unbalance_type::type_rl:
                        tmp=rl_rotate(cur);
                        break;
                    case avl_unbalance_type::type_rr:
                        tmp=rr_rotate(cur);
                        break;
                    default:
                        throw std::logic_error{"error unknown unbalance type"};
                        break;
                    }
                    cur=tmp;
                }
                cur=cur->parent;

                
            }
        }

         //将parent左旋成child的左孩子
        template <BinaryTreeNode T>
        T*  left_rotate(T *parent, T *child)
        {
            using node_type = T;
            using node_ptr = node_type *;

            node_ptr gp = parent->parent;
            node_ptr bro = parent->left;
            node_ptr left = child->left;
            // 1.连接gp和child
            {
                child->parent = gp;
                if (gp)
                {
                    if (is_left_child(gp, parent))
                        gp->left = child;
                    else
                        gp->right = child;
                }
            }

            // 2.连接parent和child
            {
                as_left(child, parent);
            }

            // 3.连接parent和right
            {
                as_right(parent, left);
            }

            return child;
        }

        //将parent右旋至child的左孩子
        template<BinaryTreeNode T>
        T*  right_rotate(T *parent, T *child)
        {
            using node_type = T;
            using node_ptr = node_type *;

            node_ptr gp = parent->parent;
            node_ptr bro = parent->right;
            node_ptr right = child->right;
            //连接gp和child
            {
                child->parent = gp;
                if (gp)
                {
                    if (is_left_child(gp, parent))
                        gp->left = child;
                    else
                        gp->right = child;
                }
            }
            //连接parent和child
            {
                as_right(child, parent);
            }

            //连接parent和left
            {
                as_left(parent, right);
            }

            return child;
        }

        // ll型旋转
        template <BinaryTreeNode T>
        T*  ll_rotate(T *grandpa)
        {
            return right_rotate(grandpa, grandpa->left);
        }

        // lr型旋转
        template <BinaryTreeNode T>
        T*  lr_rotate(T *grandpa)
        {
            left_rotate(grandpa->left, grandpa->left->right);
            return right_rotate(grandpa, grandpa->left);
        }

        // rl型旋转
        template <BinaryTreeNode T>
        T*  rl_rotate(T *grandpa)
        {
            right_rotate(grandpa->right, grandpa->right->left);
            return left_rotate(grandpa, grandpa->right);
        }

        // rr型旋转
        template <BinaryTreeNode T>
        T*  rr_rotate(T *grandpa)
        {
            return left_rotate(grandpa, grandpa->right);
        }

       

        //查看不平衡的类型
        template<BinaryTreeNode T>
        avl_unbalance_type unbalance_type(T* gp)
        {
            using node_type=T;
            using node_ptr=node_type*;
            int height_diff=height_diff_of_child_node(gp);
            int child_height_diff=0;
            if(height_diff==2)
            {
                child_height_diff=height_diff_of_child_node(gp->left);
                if(child_height_diff==1)
                {
                    return avl_unbalance_type::type_ll;
                }else{
                    return avl_unbalance_type::type_lr;
                }
            }else if(height_diff==-2){
                child_height_diff=height_diff_of_child_node(gp->right);
                if(child_height_diff==1)
                {
                    return avl_unbalance_type::type_rl;
                }else{
                    return avl_unbalance_type::type_rr;
                }
            }else{
                return avl_unbalance_type::type_unknown;
            }
        }

        // AVL树的插入
        template <BinaryTreeNode T, typename Cmp = std::less<typename T::value_type>>
        T *node_insert_avl_impl(T *root, T *to_insert)
        {
            using node_type = T;
            using node_ptr = node_type *;

            //插入节点是树的唯一节点
            if (!root)
                return to_insert;

            node_insert_base_impl(root, to_insert);

            //根节点存在,to_insert->parent必然存在
            node_ptr gp = to_insert->parent->parent;
            node_ptr cur=gp;
            node_ptr tmp=nullptr;
    

            if (!gp)
                return root;

            avl_unbalance_type type=avl_unbalance_type::type_unknown;

            //从插入节点的祖父母节点开始回溯，平衡二叉树
            while (gp)
            {
                if (is_unbalance(gp))
                {
                    type=unbalance_type(gp);
                    switch (type)
                    {
                    case avl_unbalance_type::type_ll:
                        tmp=ll_rotate(gp);
                        break;
                    case avl_unbalance_type::type_lr:
                        tmp=lr_rotate(gp);
                        break;
                    case avl_unbalance_type::type_rl:
                        tmp=rl_rotate(gp);
                        break;
                    case avl_unbalance_type::type_rr:
                        tmp=rr_rotate(gp);
                        break;
                    default:
                    throw std::logic_error{"not the first unbalance node\n"};
                        break;
                    }
                   gp=tmp;
                }
                cur=gp;
                gp = gp->parent;
            }

            return cur; //cur必然是根节点
        }

        //构建AVL树
        template <BinaryTreeNode T, typename Iter>
        T *make_binary_avl_tree(Iter begin, Iter end)
        {
            using node_type = T;
            using node_ptr = node_type *;

            if (begin == end)
                return nullptr;

            node_ptr root = new node_type(*begin);
            node_ptr tmp = nullptr;
            for (auto p = ++begin; p != end; ++p)
            {
                tmp = new node_type{*p};
                root = node_insert_avl_impl(root, tmp);
            }
            return root;
        }

        template<BinaryTreeNode T>
        T* node_erase_avl_impl(T* root,T* node)
        {

        }

        
        
    }
}

#endif