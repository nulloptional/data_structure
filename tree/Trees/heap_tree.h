#include<functional>
#ifndef fantasil_heap_tree_h
#define fantasil_heap_tree_h



#ifdef DEBUG
#include<iostream>
#endif

#pragma once

#include"..\..\utils\my_utility.h"

namespace fantasil
{
    template<typename T,typename Cmp=std::less<T>,typename Alloc=std::allocator<T>>
    class heap_tree{
        using value_type=T;
        using reference=value_type&;
        using pointer=value_type*;
        using allocator_type=Alloc;

    public:
   // heap_tree(std::initializer_list<T> list);
    
    template<typename Iter>
    heap_tree(Iter begin,Iter end);

    ~heap_tree(){delete[] m_begin;}

    public:
        void insert(const reference val);
       // void insert(value_type&& val);
        inline reference top(){return *m_begin;}
        void pop();
        inline bool empty() const{return m_begin==m_end;}
    private:
        inline size_t index(pointer pos);
        pointer left(pointer pos);
        pointer right(pointer pos);
        pointer parent(pointer pos);
        inline bool full() const{return m_end_of_storage==m_end;}
        inline size_t size() const{return m_end-m_begin;}
        pointer extream_value(pointer p1,pointer p2,pointer p3);

        void modify_from_top_to_bottom(pointer top);
        void modify_from_bottom_to_top(pointer bottom);

    private:
        static allocator_type s_alloc;
        pointer m_begin;
        pointer m_end;
        pointer m_end_of_storage;
    };

    // template<typename T,typename Cmp,typename Alloc>
    // heap_tree<T,Cmp,Alloc>::heap_tree(std::initializer_list<T> list)
    // {
    //     //allocate space
    //     auto sz=to_alloc_sz(list.size());
    //     m_begin=s_alloc.allocate(sz);
    //     m_end=m_begin;
    //     m_end_of_storage=m_begin+sz;
    //     //insert
    //     for(auto p=list.begin();p!=list.end();++p)
    //     {
    //         insert(*p);
    //     }
    // }
    
    template<typename T,typename Cmp,typename Alloc>
    template<typename Iter>
    heap_tree<T,Cmp,Alloc>::heap_tree(Iter begin,Iter end)
    {
        auto len=end-begin;
        auto sz=to_alloc_sz(len);
        m_begin=s_alloc.allocate(sz);
        m_end=m_begin;
        m_end_of_storage=m_begin+sz;
        for(auto p=begin;p!=end;++p)
        {
            insert(*p);
        }
    #ifdef DEBUG
        container_inner_data(m_begin,m_end,std::cout);
    #endif
    }

    //返回迭代器对应的索引位置
    template <typename T, typename Cmp,typename Alloc>
    size_t heap_tree<T, Cmp,Alloc>::index(pointer pos)
    {
        return pos-m_begin;
    }

    //返回指示左孩子的迭代器
    template<typename T,typename Cmp,typename Alloc>
    typename heap_tree<T,Cmp,Alloc>::pointer heap_tree<T,Cmp,Alloc>::left(pointer pos)
    {
        auto pos_index=index(pos);
        auto left_index=(pos_index<<1)+1;
        auto max_index=size()-1;
        return max_index<left_index?nullptr:m_begin+left_index;
    }

    //返回指示右孩子的迭代器
    template<typename T,typename Cmp,typename Alloc>
    typename heap_tree<T,Cmp,Alloc>::pointer heap_tree<T,Cmp,Alloc>::right(pointer pos)
    {
        auto pos_index=index(pos);
        auto right_index=(pos_index<<1)+2;
        auto max_index=size()-1;
        return max_index<right_index?nullptr:m_begin+right_index;
    }

    //返回指示父节点的迭代器
    template<typename T,typename Cmp,typename Alloc>
    typename heap_tree<T,Cmp,Alloc>::pointer heap_tree<T,Cmp,Alloc>::parent(pointer pos)
    {
        if(pos==m_begin)
            return nullptr;
        auto pos_index=index(pos);
        auto parent_index=(pos_index-1)>>1;
        return m_begin+parent_index;
    }

    //插入一个数据
    template<typename T,typename Cmp,typename Alloc>
    void heap_tree<T,Cmp,Alloc>::insert(const reference val)
    {
        if(full())
        {
            size_t n=size();
            size_t sz=to_alloc_sz(n+1);
            pointer ptr=s_alloc.allocate(sz);
            std::copy(m_begin,m_end,ptr);
            pointer tmp=m_begin;
            m_begin=ptr;
            m_end=m_begin+n;
            m_end_of_storage=m_begin+sz;
            s_alloc.deallocate(tmp,n);
        }

        *m_end=val;
        modify_from_bottom_to_top(m_end);
        ++m_end;
        
    }

    // template<typename T,typename Cmp,typename Alloc>
    // void heap_tree<T,Cmp,Alloc>::insert(value_type&& val)
    // {
    //     value_type v{val};
    //     insert(v);
    // }

    //弹出根数据
    template<typename T,typename Cmp,typename Alloc>
    void heap_tree<T,Cmp,Alloc>::pop()
    {
        if(empty())
            return;
        if(size()==1)
        {
            --m_end;
            return;
        }
        auto cur=m_end-1;
        std::swap(*m_begin,*cur);
        --m_end;
        modify_from_top_to_bottom(m_begin);
    }

    //从top开始向下追溯，保持堆树的结构
    template<typename T,typename Cmp,typename Alloc>
    void heap_tree<T,Cmp,Alloc>::modify_from_top_to_bottom(pointer top)
    {
        pointer cur=top;
        bool condition=true;
        pointer _left=nullptr;
        pointer _right=nullptr;
        pointer tmp=nullptr;
        Cmp cmp{};
        while(cur&&condition)
        {
            _left=left(cur);
            _right=right(cur);
            if(_left)
            {
                if(_right)
                {
                    tmp=cmp(*_left,*_right)?_right:_left;   //取左右节点的极值
                }else{
                    tmp=_left;  //右节点不存在
                }
            }else{
                return; //当前已经是叶子节点了
            }
            if(cmp(*tmp,*cur))
                condition=false;
            else
            {
                std::swap(*cur,*tmp);
                cur=tmp;
            }

        }

    }

    //从bottom开始，向上追溯，保持堆树的结构
    template<typename T,typename Cmp,typename Alloc>
    void heap_tree<T,Cmp,Alloc>::modify_from_bottom_to_top(pointer bottom)
    {
        auto cur=bottom;
        pointer p=nullptr;
        Cmp cmp{};
        while(cur)
        {
            p=parent(cur);
            if(!p||cmp(*cur,*p))
                return;
            else{
                std::swap(*cur,*p);
                cur=p;
            }
        }
    }

    template<typename T,typename Cmp,typename Alloc>
    Alloc heap_tree<T,Cmp,Alloc>::s_alloc={};

    //大根堆
    template<typename T>
    using max_heap=heap_tree<T,std::less<T>,std::allocator<T>>;

    //小根堆
    template<typename T>
    using min_heap=heap_tree<T,std::greater<T>,std::allocator<T>>;
}







#endif