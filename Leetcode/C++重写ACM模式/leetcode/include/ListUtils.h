#pragma once
#include <iostream>
#include <vector>

// 链表节点结构体
struct Node {
    int val;       
    Node* next;     
    Node() : val(0), next(nullptr) {};                  
    Node(int _val) : val(_val), next(nullptr) {};       
    Node(int _val, Node* _next) : val(_val), next(_next) {}; 
};

// 链表工具类（静态成员函数，无需实例化即可使用）
class ListUtils{
public:
    /**
     * @brief  将整数向量转换为单向链表（尾插法构建）
     * @param  nums 输入的整数向量，向量元素顺序对应链表节点顺序（首元素为链表头）
     * @return Node* 构建完成的链表头节点指针（若向量为空，返回 nullptr）
     */
    static Node* ConvertToList(const std::vector<int> nums);

    /**
     * @brief  将单向链表转换为整数向量
     * @param  head 链表的头节点指针（若为 nullptr，返回空向量）
     * @return std::vector<int> 存储链表节点值的向量，向量顺序与链表节点顺序一致（头节点对应首元素）
     */
    static std::vector<int> ConvertToVecor(Node* head); 

    /**
     * @brief  销毁单向链表，释放所有节点的动态内存
     * @param  head 链表头节点的引用指针（销毁后会被置为 nullptr）
     * @note   1. 采用遍历方式逐个释放节点，避免内存泄漏；
     */
    static void destroy(Node*& head);
};