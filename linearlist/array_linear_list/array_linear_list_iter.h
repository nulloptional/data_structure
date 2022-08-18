

template<typename T>
struct array_linear_list_iter{
    using value_type=T;
    using pointer =value_type*;
    using reference =value_type&;

    using self=array_linear_list_iter<T>;
    using self_ptr=self*;
    using self_ref=self&;

    array_linear_list_iter(pointer _ptr=nullptr):ptr{_ptr}{}

    pointer operator->(){return ptr;}
    reference operator*(){return *ptr;}
    reference operator[](size_t n){ptr+=n;return *ptr;}
    self_ref operator++(){++ptr;return *this;}
    self_ref operator--(){--ptr;return *this;}
    self operator++(int){auto tmp=ptr;++tmp;return self{tmp};}
    self operator--(int){auto tmp=ptr;--tmp;return self{tmp};}
    self operator+(size_t n){auto tmp=*this;tmp.ptr+=n;return tmp;}
    self operator-(size_t n){auto tmp=*this;tmp.ptr-=n;return tmp;}
    size_t operator-(const self_ref rhs){return static_cast<size_t>(ptr-rhs.ptr);}
    self_ref operator+=(size_t n){ptr+=n;return *this;}
    self_ref operator-=(size_t n){ptr-=n;return *this;}

    pointer ptr;
};

template<typename T>
bool operator==(const array_linear_list_iter<T>& lhs,const array_linear_list_iter<T>& rhs)
{
    return lhs.ptr==rhs.ptr;
}

template<typename T>
bool operator!=(const array_linear_list_iter<T>& lhs,const array_linear_list_iter<T>& rhs)
{
    return lhs.ptr!=rhs.ptr;
}


