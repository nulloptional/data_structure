#include<type_traits>
#ifndef my_concept_h
#define my_concept_h

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

//是否含有FUNCNAME的函数成员对象
#define HAS_MEMBER_FUNC_(FUN_NAME)\
template<typename T,typename =void>\
struct has_member_func_##FUN_NAME:std::false_type{};\
\
template<typename T>\
struct has_member_func_##FUN_NAME<T,\
    std::void_t<decltype(std::declval<T>().FUN_NAME)>\
    >\
    :std::true_type{};\
template<typename T>\
constexpr bool has_member_func_##FUN_NAME##_v=has_member_data_##FUN_NAME<T>::value;\
\


//
#define IS_SELF_PTR(NAME)\
template<typename T>\
constexpr bool is_##NAME##_self_ptr=std::is_same_v<\
                                        has_member_data_##NAME##_t<T>,\
                                        T*\
                                    >;\
\

//对于forward_node而言
HAS_MEMBER_DATA_(data);
HAS_MEMBER_DATA_(next);
//bidirectional_node
HAS_MEMBER_DATA_(prev);
//binary_tree_node
HAS_MEMBER_DATA_(parent);
HAS_MEMBER_DATA_(left);
HAS_MEMBER_DATA_(right);

IS_SELF_PTR(next);
IS_SELF_PTR(prev);
IS_SELF_PTR(parent);
IS_SELF_PTR(left);
IS_SELF_PTR(right);

//
template<typename T>
concept Node=   has_member_data_data_v<T>&&
                has_member_data_next_v<T>&&
                is_next_self_ptr<T>;

template<typename T>
concept BiNode= has_member_data_data_v<T>&&
                has_member_data_next_v<T>&&
                is_next_self_ptr<T>&&
                is_prev_self_ptr<T>;

template<typename T>
concept BinaryTreeNode= has_member_data_data_v<T>&&
                        has_member_data_parent_v<T>&&
                        has_member_data_left_v<T>&&
                        has_member_data_right_v<T>&&
                        is_parent_self_ptr<T>&&
                        is_left_self_ptr<T>&&
                        is_right_self_ptr<T>;


#endif



