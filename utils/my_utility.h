#include<algorithm>
#include<vector>
#include<random>
#include<chrono>

#ifndef My_Utility_H
#define My_Utility_H

#pragma once

std::size_t to_alloc_sz(std::size_t sz)
{
    size_t default_size=16;
    size_t threshold=65535;
    size_t to_alloc=default_size;
    double factor_0=2;
    double factor_1=1.5;
    double near_sacle_0=0.75;
    double near_scale_1=0.95;

    double scale=sz/default_size;
    if(scale>near_sacle_0)
    {
        double scale_2=sz/threshold;
        if(scale_2>near_scale_1)
        {
            to_alloc=sz*factor_1;
        }else{
            to_alloc=sz*factor_0;
        }
    }
    #ifdef DEBUG
    std::cout<<"to allocate size:"<<to_alloc<<std::endl;
    #endif
    return to_alloc;
    
}

template<typename Iter,typename Ostream>
Ostream& container_inner_data(Iter begin,Iter end,Ostream& os)
{
    os<<"\nDEBUG:Container Inner Data:\n";
    size_t sz=end-begin;
    size_t row=std::round(std::sqrt(sz));
    for(auto p=begin,j=row;p!=end;++p,--j)
    {
        if(j==0)
        {
            os<<"\n";
            j=row;
        }
        os<<*p<<" ";
    }
    os<<"\n";
    return os;
}


std::vector<int> get_random_vector(int min,int max,size_t capacity)
{
    std::chrono::steady_clock clock{};
    auto count=clock.now().time_since_epoch().count();
    std::vector<int> v{};
    std::default_random_engine engine{};
    std::uniform_int_distribution u{min,max};
    engine.seed(count);
    for(size_t i=0;i<capacity;++i)
    {
        v.push_back(u(engine));
    }
    return v;
}


#endif