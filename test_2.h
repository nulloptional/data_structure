#include"node\node_helper.h"
#include"node\forward_node.h"
#include<vector>
#include<iterator>
#include"stack\chain_stack.h"

template<Node T>
void f()
{
    std::vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    auto head=make_forward_chain_list<T>(vi.begin(),vi.end());
    print_chain_details(head);
    std::vector<int> vj{{10,20,30,40,50,60}};
    insert_of_forward_node(head,vj.begin(),vj.end());
    print_chain_details(head);
    erase_forward_nodes<forward_node<int>>(head,head->next,nullptr);
    print_chain_details(head);
}

template<BiNode T>
void f2()
{
    std::vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    auto head=make_bidirection_chain_list<T>(vi.begin(),vi.end());
    print_chain_details(head);
    std::vector<int> vj{{10,20,30,40,50,60}};
    insert_of_bi_node(head,vj.begin(),vj.end());
    print_chain_details(head);
    erase_bi_nodes<bi_node<int>>(head->next,nullptr);
    print_chain_details(head);
}

void chain_stack_test()
{
    std::vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    chain_stack<int> st{vi.begin(),vi.end()};
    st.print_details();
    while(!st.empty())
    {
        st.pop();
        st.print_details();
    }
    
}

void test()
{
   chain_stack_test();

}