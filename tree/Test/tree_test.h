#ifndef Tree_Test_H
#define Tree_Test_H

#define DEBUG

//for in and out
#include<vector>
#include<iostream>
//nodes
#include"..\TreeNodes\binary_tree_node.h"

//helpers
#include"..\helpers\tree_node_helper.h"
#include"..\helpers\avl_tree_helper.h"

//trees
#include"..\Trees\base_binary_tree.h"
#include"..\Trees\heap_tree.h"

//prompt
#include"..\helpers\prompt.h"


//关于二叉树节点的通用函数测试
void Base_Tree_Helper_Test()
{
   using namespace fantasil::node;
   using namespace fantasil::details;
   std::vector<int> data{{4,2,6,1,3,5,7}};
   auto root=make_base_binary_tree<binary_tree_node<int>>(data.begin(),data.end());
   std::cout<<"root:"<<root->data<<"\n";
   auto left=most_left_node(root);
   std::cout<<"most left:"<<left->data<<"\n";
   auto right=most_right_node(root);
   std::cout<<"most right:"<<right->data<<"\n";
   std::cout<<"seq:";
   binary_tree_node<int>* cur=left;
   while(cur)
   {
      std::cout<<cur->data<<" ";
      cur=node_base_next(cur);
   }
   
   std::cout<<"\npre order:";
   pre_order_seq(root,std::cout);
   std::cout<<"\nmid order:";
   mid_order_seq(root,std::cout);
   std::cout<<"\npost order:";
   post_order_seq(root,std::cout);
   std::cout<<"\nafter erase:";
   root=node_erase_base_impl(root,root);
   std::cout<<"\npre order:";
   pre_order_seq(root,std::cout);
   std::cout<<"\nmid order:";
   mid_order_seq(root,std::cout);
   std::cout<<"\npost order:";
   post_order_seq(root,std::cout);

}

//普通二叉树的测试
void Base_Tree_Test()
{
   
   using namespace fantasil::Tree;
   std::cout<<fantasil::details::base_tree_test_prompt<<std::endl;
   std::vector<int> data{{4,2,6,1,3,5,7}};
   base_binary_tree<int> t{data.begin(),data.end()};
   
   t.pre_order();
   std::cout<<"\n";
   t.mid_order();
   std::cout<<"\n";
   t.post_order();
   
}


//AVL树测试
void AVL_Tree_Test()
{
   using namespace fantasil;
   using namespace fantasil::node;
   using namespace fantasil::details;
   

   std::cout<<avl_tree_test_prompt<<std::endl;
   std::vector<int> data{{1,2,3,4,5,6,7,8,9}};
   auto root=make_binary_avl_tree<binary_tree_node<int>>(data.begin(),data.end());
   mid_order_seq(root,std::cout);
}

//二项堆的测试
void Heap_Tree_Test()
{
   using namespace fantasil;
   std::vector vi=get_random_vector(0,10000,50);
   max_heap<int> heap{vi.begin(),vi.end()};
   while(!heap.empty())
   {
      std::cout<<heap.top()<<" ";
      heap.pop();
   }
   std::cout<<"\n";
   min_heap<int> heap_2{vi.begin(),vi.end()};
   while(!heap_2.empty())
   {
      std::cout<<heap_2.top()<<" ";
      heap_2.pop();
   }

}

void Red_Black_Tree_Test()
{

}

void tree_test()
{
   Heap_Tree_Test();
}
#endif