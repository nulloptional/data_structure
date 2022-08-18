
#include"..\node\forward_node.h"
#include"..\node\bi_node.h"
#include"..\node\binary_tree_node.h"
#include"my_concept.h"
#include<string>
#ifndef My_Concepts_Test_H
#define My_Concepts_Test_H

template<typename Node>
void my_concepts_test_impl(const std::string& info)
{
    std::cout<<"---------------------------------------------------\n";
    std::cout<<info<<"\n";
    // std::cout << "has_member_data?:" << has_member_data_data_v<Node> << "\n";
    // std::cout << "has_member_prev?:" << has_member_data_prev_v<Node> << "\n";
    // std::cout << "has_member_next?:" << has_member_data_next_v<Node> << "\n";
    // std::cout << "has_member_parent?:" << has_member_data_parent_v<Node> << "\n";
    // std::cout << "has_member_left?:" << has_member_data_left_v<Node> << "\n";
    // std::cout << "has_member_right?:" << has_member_data_right_v<Node> << "\n";
    std::cout<<"has_mmeber:";
    if(has_member_data_data_v<Node>)
        std::cout<<"data"<<" ";
    if(has_member_data_prev_v<Node>)
        std::cout<<"prev"<<" ";
    if(has_member_data_next_v<Node>)
        std::cout<<"next"<<" ";
    if(has_member_data_parent_v<Node>)
        std::cout<<"parent"<<" ";
    if(has_member_data_left_v<Node>)
        std::cout<<"left"<<" ";
    if(has_member_data_right_v<Node>)
        std::cout<<"right"<<" \n";
    std::cout<<"\n";
    
}

void my_concepts_test()
{
    my_concepts_test_impl<forward_node<int>>("forward_node");
    my_concepts_test_impl<bi_node<int>>("bidirectional_node");
    my_concepts_test_impl<binary_tree_node<int>>("binary_tree_node");
}


#endif