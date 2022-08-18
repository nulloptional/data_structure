#include<algorithm>

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

#endif