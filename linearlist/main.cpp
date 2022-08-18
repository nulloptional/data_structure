#define DEBUG
#include<iostream>
#include<vector>
#include"..\node\forward_node.h"
#include"..\node\bi_node.h"
// #include"..\node\my_concept.h"


#include"..\node\node_helper.h"
#include"..\test_2.h"
#include"..\queue\queue_test.h"

#include"..\my_concepts\my_concepts_test.h"
#include"..\tree\tree_test.h"

template<typename T>
struct binary_tree_node_2{
    using value_type=T;
    using node_type=binary_tree_node_2<T>;
    using node_ptr=node_type*;
    
    node_ptr parent;
    node_ptr left;
    node_ptr right;
    value_type data;
};

template<std::integral T>
T func_ii(T* a,T* b)
{
    return *a-*b;   
}

int main()
{
    tree_test();
    return 0;
    
}