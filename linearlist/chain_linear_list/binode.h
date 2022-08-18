#include<iterator>

template<typename T>
struct binode{
    using value_type=T;
    using reference=value_type&;
    using const_reference=const reference;
    using node_type=binode<T>;
    using node_ptr=node_type*;

    binode(const_reference _val,node_ptr _prev=nullptr,node_ptr _next=nullptr):prev{_prev},val{_val},next{_next}{}
    node_ptr prev;
    node_ptr next;
    value_type val;
};

template<typename T>
bool operator==(const binode<T>& lhs,const binode<T>& rhs)
{
    return lhs.prev==rhs.prev&&lhs.next=rhs.next&&lhs.val==rhs.val;
}

template<typename T>
bool operator!=(const binode<T>& lhs,const binode<T>& rhs)
{
    return !lhs==rhs;
}

//给定一个节点，返回尾节点
template<typename T>
binode<T>* node_tail(binode<T>* node)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    node_ptr cur=node;
    while(cur->next)
    {
        cur=cur->next;
    }
    return cur;
}

//给定一个节点，返回头节点
template<typename T>
binode<T>* node_head(binode<T>* node)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    node_ptr cur=node;
    while(cur->prev)
    {
        cur=cur->prev;
    }
    return cur;
}

//两个节点之间的距离
template<typename T>
size_t node_distance(binode<T>* begin,binode<T>* end=nullptr)
{
    size_t distance{0};
    while(begin!=end)
    {
        ++distance;
        begin=begin->next;
    }
    return distance;
    
}

//将[begin,end)转换成节点组成的链表
template<typename Iter,typename T=std::iterator_traits<Iter>::value_type>
binode<T>* make_chain_list(Iter _begin,Iter _end)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    if(_begin==_end)
    {
        return nullptr;
    }
    node_ptr head=new node_type{*_begin};
    node_ptr cur=head;
    node_ptr next=nullptr;
    for(auto p=++_begin;p!=_end;++p)
    {
        next=new node_type{*p};
        cur->next=next;
        next->prev=cur;
        cur=next;
    }
    return head;
}

//连接两个节点
template<typename T>
binode<T>& operator+(binode<T>& lhs,binode<T>& rhs)
{
    lhs.next=&rhs;
    rhs.prev=&lhs;
    return lhs;
}

//连接链表
template<typename T>
binode<T>* nodes_connect(binode<T>* lhs,binode<T>* rhs)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    node_ptr l_tail=node_tail(lhs);
    node_ptr r_head=node_head(rhs);
    l_tail->next=r_head;
    r_head->prev=l_tail;
    return lhs;
}

//在指定位置插入节点
template<typename T>
void node_insert_impl(binode<T>* pos,binode<T>* begin,binode<T>* end=nullptr)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    if((!pos)||(!begin))
        return ;
    node_ptr l_tail=pos;
    node_ptr r_head=pos->next;
    node_ptr m_head=begin;
    node_ptr m_tail=nullptr;
    if(end)
        m_tail=end->prev;
    else
        m_tail=node_tail(begin);
    l_tail->next=m_head;
    m_head->prev=l_tail;
    m_tail->next=r_head;
    if(r_head)
        r_head->prev=m_tail;
    
}

//在指定位置插入数据
template<typename T,typename Iter>
void node_insert(binode<T>* pos,Iter _begin,Iter _end)
{
    using value_type=std::iterator_traits<Iter>::value_type;
    using node_type=binode<T>;
    using node_ptr=node_type*;
    static_assert(std::is_same_v<T,value_type>);
    node_ptr m_head=make_chain_list(_begin,_end);
    node_insert_impl(pos,m_head);
}

//析构指定节点
template<typename T>
void desconstruct(binode<T>* begin,binode<T>* end=nullptr)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    if(!begin)
        return;
    node_ptr cur=begin;
    node_ptr next=cur->next;
    while(cur&&cur!=end)
    {
        delete cur;
        cur=next;
        if(next)
            next=cur->next;
    }
}

//指定位置删除节点
template<typename T>
void node_erase(binode<T>* begin,binode<T>* end=nullptr)
{
    using node_type=binode<T>;
    using node_ptr=node_type*;
    if(!begin)
        return;
    node_ptr l_tail=begin->prev;
    node_ptr m_head=begin;
    node_ptr m_tail=nullptr;
    if(end)
        m_tail=end->prev;
    else
        m_tail=node_tail(m_head);
    node_ptr r_head=end;
    if(l_tail)
        l_tail->next=r_head;
    if(r_head)
        r_head->prev=l_tail;
    desconstruct(begin,end);

}

//输出单节点
template<typename T,typename ostream>
ostream& operator<<(const binode<T>& node,ostream& os)
{
    os<<node.val<<" ";
    return os;
    
}

//输出链表
template<typename T,typename ostream>
ostream& operator<<(binode<T>* head,ostream& os)
{
    while(head)
    {
        os<<head->val<<" ";
        head=head->next;
    }
    return os;
}