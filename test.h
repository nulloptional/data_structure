#include<vector>
#include"stack\array_stack.h"
#include"linearlist\chain_linear_list\chain_linear_list.h"
#include"linearlist\array_linear_list\array_liear_list.h"
#include"node\node_helper.h"
#include"node\forward_node.h"

void array_stack_test()
{
    using namespace std;
    vector<int> v1{{0,1,2,3,4,5,6,7,8,9}};
    vector<int> v2{{10,20,30,40,50,60,70,80,90}};
    std::cout<<v1.end()-v1.begin()<<std::endl;
    array_stack<int> as{v1.begin(),v1.end()};
    as.stack_details(std::cout);
    for(auto p=v2.begin();p!=v2.end();++p)
    {
        as.push(*p);
    }
    as.stack_details(std::cout);
    size_t i=v1.size()+v2.size();
    for(;i>0;--i)
    {
        as.pop();
        as.stack_details(std::cout);
    }
}
template<std::ranges::range C,typename ostream>
ostream& operator<<(const C& c,ostream& os)
{
    for(auto p=std::ranges::begin(c);p!=std::ranges::end(c);++p)
    {
        os<<*p;
    }
}

void binode_test()
{
    std::vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    std::vector<int> v2{{10,20,30,40,50,70}};
    binode<int>* head=make_chain_list(vi.begin(),vi.end());
    std::cout<<"the head is:";
    operator<<(*head,std::cout);
    std::cout<<"\nthe data is:";
    operator<<(head,std::cout);
    std::cout<<"\nthe tail is:";
    auto tail=*node_tail(head);
    operator<<(tail,std::cout);
    std::cout<<"\nthe distance is:";
    std::cout<<node_distance(head);
    node_insert(head,v2.begin(),v2.end());
    std::cout<<"\nafter insert:";
    operator<<(head,std::cout);
    node_erase(head->next);
    std::cout<<"\nafter erase:";
    operator<<(head,std::cout);
    std::cout<<"\n";
}

void chain_linear_list_test()
{
    std::vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    std::vector<int> v2{{10,20,30,40,50,70}};
    chain_linear_list<int> list(vi.begin(),vi.end());
    print_list_detail(list,std::cout);
    list.insert(v2.begin(),v2.end(),list.begin());
    print_list_detail(list,std::cout);
    list.erase(++list.begin(),list.end());
    print_list_detail(list,std::cout);
}



void node_test()
{
    
}