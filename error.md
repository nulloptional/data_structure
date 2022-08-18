此处用于记录在编程中遇到的错误之处

## 1
两种最常见的节点
```c++
template<typename T>
struct forward_node{
    T data;
    forward_node<T>* next;
};

template<typename T>
struct bi_node{
    T data;
    bi_node<T>* prev;
    bi_node<T>* next;
}
```

某些常见的节点操作是高度相似的，所以希望可以有相似的函数簇
