#ifndef Base_Binary_Tree_H
#define Base_Binary_Tree_H
#pragma once

#include"..\TreeNodes\binary_tree_node.h"
#include"..\iterators\base_binary_tree_iter.h"

namespace fantasil
{
    namespace Tree
    {
        //----------------------------------------分割线-----------------------------------------
        /*
            普通二叉树
        */
        template <typename T>
        class base_binary_tree
        {
        
            using iterator = fantasil::iterator::base_binary_tree_iter<T>;
            using value_type = T;
            using reference = value_type &;
            using pointer = value_type *;
            using iterator_category = std::bidirectional_iterator_tag;
            using difference = std::size_t;

            using node_type = fantasil::node::binary_tree_node<T>;
            using node_ptr = node_type *;

        public:
            template <typename Iter>
            base_binary_tree(Iter beign, Iter end);

            ~base_binary_tree()
            { /*...*/
            }

        public:
            void insert(const reference val);

            template <typename Iter>
            void insert(Iter begin, Iter end);

            void erase(iterator pos);

        public:
            iterator begin() { return details::most_left_node(m_root); }
            iterator begin() const { return details::most_left_node(m_root); }
            iterator end() { return iterator{}; }
            iterator end() const { return iterator{}; }
            iterator find(const reference val);

        public:
            void pre_order();
            void mid_order();
            void post_order();

        private:
            iterator m_root;
        };

        //初始化
        template <typename T>
        template <typename Iter>
        base_binary_tree<T>::base_binary_tree(Iter begin, Iter end)
        {
            m_root.ptr = details::make_base_binary_tree<node_type>(begin, end);
        }

        //插入一个数据
        template <typename T>
        void base_binary_tree<T>::insert(const reference val)
        {
            node_ptr node = new node_type{val};
            m_root.ptr = details::node_insert_base_impl<node_type>(m_root.ptr, node);
        }

        //插入[begin,end)
        template <typename T>
        template <typename Iter>
        void base_binary_tree<T>::insert(Iter begin, Iter end)
        {
            for (auto p = begin; p != end; ++p)
            {
                insert(*p);
            }
        }

        //删除指定位置的数据
        template <typename T>
        void base_binary_tree<T>::erase(iterator pos)
        {
            m_root = details::node_erase_base_impl<node_type>(m_root, pos.data);
        }

        template <typename T>
        typename base_binary_tree<T>::iterator base_binary_tree<T>::find(const reference val)
        {
            node_ptr cur = m_root;
            iterator pos{};
            while (cur)
            {
                if (cur.data == val)
                {
                    pos.data = cur;
                    return pos;
                }
                else if (cur.data < val)
                    cur = cur->left;
                else
                    cur = cur->right;
            }
            return pos;
        }

        template<typename T>
        void base_binary_tree<T>::pre_order()
        {
            details::pre_order_seq(m_root.ptr,std::cout);
        }
        template<typename T>
        void base_binary_tree<T>::mid_order()
        {
            details::mid_order_seq(m_root.ptr,std::cout);
        }

        template<typename T>
        void base_binary_tree<T>::post_order()
        {
            details::post_order_seq(m_root.ptr,std::cout);
        }

    }

};

#endif