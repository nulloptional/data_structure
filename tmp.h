#include<type_traits>

//是否含有名为NAME的数据成员对象
#define HAS_MEMBER_DATA_(NAME)\
template<typename T,typename =void>\
struct has_member_data_##NAME:std::false_type{using member_type=void;};\
\
template<typename T>\
struct has_member_data_##NAME<T,\
    std::void_t<decltype(std::declval<T>().NAME)>\
    >\
    :std::true_type{using member_type=decltype(std::declval<T>().NAME);};\
template<typename T>\
constexpr bool has_member_data_##NAME##_v=has_member_data_##NAME<T>::value;\
template<typename T>\
using has_member_data_##NAME##_t=typename has_member_data_##NAME<T>::member_type;\
\

template<typename T>
struct forward_node{
    forward_node<T>* next;
    T data;
};

template<typename T>
struct bi_node{
    bi_node<T>* prev;
    bi_node<T>* next;
    T data;
};

HAS_MEMBER_DATA_(next);
HAS_MEMBER_DATA_(data);
HAS_MEMBER_DATA_(prev);