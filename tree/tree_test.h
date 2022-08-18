#ifndef Tree_Test_H
#define Tree_Test_H

#include"tree_node_helper.h"
#include<vector>
#include<iostream>
#include"..\node\binary_tree_node.h"
#include"avl_tree_helper.h"

void Base_Tree_Test()
{
   std::vector<int> data{{1,2,3,4,5,6,7,8,9}};
   auto root=make_base_binary_tree<binary_tree_node<int>>(data.begin(),data.end());
   mid_order_seq(root,std::cout);
}

void AVL_Tree_Test()
{
   using namespace fantasil;
   using namespace fantasil::helper_details;

   
   std::vector<int> data{{1,2,3,4,5,6,7,8,9}};
   auto root=make_binary_avl_tree<binary_tree_node<int>>(data.begin(),data.end());
   mid_order_seq(root,std::cout);
}

void Red_Black_Tree_Test()
{

}

void tree_test()
{
   AVL_Tree_Test();
}
#endif