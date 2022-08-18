#define DEBUG
#include"array_queue.h"
#include"chain_queue.h"
#include<vector>
#ifndef Array_Queue_Test_H
#define Array_Queue_Test_H

void array_queue_test()
{
    using namespace std;
    vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    vector<int> vj{{10,20,30,40,50,60,70,80,90}};

    array_queue<int> queue{vi.begin(),vi.end()};
    queue.print_details();
    for(auto p=vj.begin();p!=vj.end();++p)
    {
        queue.in(*p);
        queue.print_details();
    }

    

    for(int i=0;i<10;++i)
    {
        queue.out();
        queue.print_details();
    }
   
    vector<int> vk{{100,200,300,400,500}};
    for(auto p=vk.begin();p!=vk.end();++p)
    {
        queue.in(*p);
        queue.print_details();
    }
}

void chain_queue_test()
{
    using namespace std;
    vector<int> vi{{1,2,3,4,5,6,7,8,9}};
    vector<int> vj{{10,20,30,40,50,60,70,80,90}};

    chain_queue<int> queue{vi.begin(),vi.end()};
    queue.print_details();
    for(auto p=vj.begin();p!=vj.end();++p)
    {
        queue.in(*p);
        queue.print_details();
    }

    

    for(int i=0;i<10;++i)
    {
        queue.out();
        queue.print_details();
    }
   
    vector<int> vk{{100,200,300,400,500}};
    for(auto p=vk.begin();p!=vk.end();++p)
    {
        queue.in(*p);
        queue.print_details();
    }
}

#endif