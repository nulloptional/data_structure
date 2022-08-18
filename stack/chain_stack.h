#include"..\node\forward_node.h"
#include"..\node\node_helper.h"

// template<typename T>
// struct chain_stack_iter{
//     using node_type=forward_node<T>;
//     using node_ptr=node_type*;
//     using value_type=T;
//     using reference=T&;
//     using pointer=T*;
//     using self=chain_stack_iter<T>;
//     using self_ref=self&;
    
//     chain_stack_iter(node_ptr _ptr=nullptr):ptr{_ptr}{}
//     ~chain_stack_iter(){}
//     self_ref operator++(){ptr=ptr->next;return *this;}
//     self operator++(int){auto tmp=*this;ptr=ptr->next;return tmp;}
//     reference operator*(){return ptr->data;}
//     node_ptr operator->(){return ptr;}
//     node_ptr ptr;
// };

// template<typename T>
// bool operator==(const chain_stack_iter<T>& lhs,const chain_stack_iter<T>& rhs)
// {
//     return lhs.ptr==rhs.ptr;
// }

// template<typename T>
// bool operator!=(const chain_stack_iter<T>& lhs,const chain_stack_iter<T>& rhs)
// {
//     return lhs.ptr!=rhs.ptr;
// }

//由于stack限制了数据的操作，所以这里就不适用Iterator的工作场景
template<typename T>
class chain_stack{
    using value_type=T;
    using reference=T&;
    using node_type=forward_node<T>;
    using node_ptr=node_type*;
public:
    template<typename Iter>
    chain_stack(Iter begin,Iter end)
    {
        auto first=make_forward_chain_list<node_type>(begin,end);
        auto last=node_tail(first);
        auto last_prev=find_prev(first,last);
        head=first;
        tail=last;
        tail_prev=last_prev;
    }

    ~chain_stack()
    {
        erase_forward_nodes<forward_node<T>>(head,head,nullptr);
        head=tail=tail_prev=nullptr;
    }

    inline bool empty() const{return head==nullptr;}

    void push(const reference val)
    {
        node_ptr tmp=new node_type{val};
        if(empty())
        {
            head=tail=tmp;
            tail_prev=nullptr;
        }else{
            as_next(tail,tmp);
            tail_prev=tail;
            tail=tmp;
        }
    }

    reference top()
    {
        if(empty())
            throw std::logic_error{"empty stack"};
        return tail->data;
    }

    void pop()
    {
        if(empty())
            return;
        delete tail;
        tail=tail_prev;
        tail_prev=find_prev(head,tail);
        tail->next=nullptr;
    }

#ifdef DEBUG
    void print_details()
    {
        print_chain_details(head);
    }
#endif

private:
    node_ptr head;
    node_ptr tail;
    node_ptr tail_prev;
};
