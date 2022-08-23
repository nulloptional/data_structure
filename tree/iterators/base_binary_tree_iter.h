#ifndef Base_Binary_Tree_Iter_H
#define Base_Binary_Tree_Iter_H
#include<iterator>
namespace fantasil
{
    namespace iterator
    {
        template <typename T>
        struct base_binary_tree_iter
        {
            
            using value_type = T;
            using reference = value_type &;
            using pointer=value_type*;
            using iterator_category=std::bidirectional_iterator_tag;
            using difference_type=std::size_t;

            using node_type = fantasil::node::binary_tree_node<T>;
            using node_ptr = node_type *;

            using self = base_binary_tree_iter<T>;
            using self_ref = self &;

            base_binary_tree_iter(node_ptr node = nullptr) : ptr{node} {}
            ~base_binary_tree_iter() { ptr = nullptr; }

            reference operator*() { return ptr->data; }
            node_ptr operator->() { return ptr; };
            self_ref operator++()
            {
                ptr = details::node_base_next(ptr);
                return *this;
            }
            self_ref operator--()
            {
                ptr = details::node_base_prev(ptr);
                return *this;
            }
            self operator++(int)
            {
                auto tmp = *this;
                ptr = details::node_base_next(ptr);
                return tmp;
            }
            self operator--(int)
            {
                auto tmp = *this;
                ptr = details::node_base_prev(ptr);
                return tmp;
            }

            node_ptr ptr;
        };

        template <typename  T>
        bool operator==(const base_binary_tree_iter<T> &lhs, const base_binary_tree_iter<T> &rhs)
        {
            return lhs.ptr == rhs.ptr;
        }

        template <typename  T>
        bool operator!=(const base_binary_tree_iter<T> &lhs, const base_binary_tree_iter<T> &rhs)
        {
            return lhs.ptr != rhs.ptr;
        }
    }

}

#endif