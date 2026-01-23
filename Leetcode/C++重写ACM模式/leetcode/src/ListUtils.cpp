#include <iostream>
#include "ListUtils.h"

std::vector<int> ListUtils::ConvertToVecor(Node* head) {
    std::vector<int> result;
    Node* cur = head;
    while(cur != nullptr) {
        result.push_back(cur->val);
        cur = cur->next;
    }
    std::cout<<"ConvertToVecor success!"<<std::endl;
    return result;
}

Node* ListUtils::ConvertToList(std::vector<int> nums) {
    Node* dummy = new Node();
    Node* head = dummy;
    for(const int& i : nums) {
        Node* cur = new Node(i);
        head->next = cur;
        head = head->next;
    }
    std::cout<<"ConvertToList success!"<<std::endl;
    return dummy->next;
}

void ListUtils::destroy(Node*& head) {
    // 删除之前必须先保存下一个节点 不然删除当前节点之后找不到下一个节点了bro
    while(head != nullptr) {
        Node* cur = head;
        head = head->next;
        delete cur;
        cur = nullptr;
    }
}