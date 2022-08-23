#ifndef fantasil_rb_tree_node_h
#define fantasil_rb_tree_node_h
#include<algorithm>


#pragma once


namespace fantasil
{
    namespace node{

        enum class rb_color{red,black};

        template<typename K,typename V>
        struct  rb_tree_node
        {
            using value_type=V;
            using reference=value_type&;
            
            using key_type=K;

            using node_type=rb_tree_node<K,V,Cmp>;
            using node_ptr=node_type*;

            rb_tree_node(const key_type& _key,const value_type& _val,node_ptr _parent=nullptr,node_ptr _left=nullptr,node_ptr _right=nullptr)
                :key(_key),data{_val},parent(_parent),left(_left),right(_right)
                {

                }

            node_ptr parent;
            node_ptr left;
            node_ptr right;
            std::pair<K,V> pair;
            key_type& key=pair.first;       //别名
            value_type& data=pair.second;   //别名
            rb_color clr;
        };

        template<typename K,typename V>
        inline bool operator==(const rb_tree_node<K,V>& lhs,const rb_tree_node<K,V>& rhs)
        {
            return lhs.key==rhs.key&&lhs.data==rhs.data;
        }

        template<typename K,typename V>
        inline bool operator!=(const rb_tree_node<K,V>& lhs,const rb_tree_node<K,V>& rhs)
        {
            return !(lhs==rhs);
        }

        template<typename K,typename V>
        inline bool operator<(const rb_tree_node<K,V>& lhs,const rb_tree_node<K,V>& rhs)
        {
            return lhs.key<rhs.key;
        }

        template<typename K,typename V>
        inline bool operator>(const rb_tree_node<K,V>& lhs,const rb_tree_node<K,V>& rhs)
        {
            return lhs.key>rhs.key;
        }
        


    }
}


#endif