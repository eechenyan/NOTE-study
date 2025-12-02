// 25. K 个一组翻转链表

// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

#include <iostream>
#include "ListUtils.h"
#include "VectorUtils.h"
using namespace std;

class Solution {
public:
    Node* RevertList(Node* head, int k) {
        // 使用两个指针pre和cur来进行反转
        // pre初始化为nullptr
        // cur初始化为head
        // 同时使用虚拟头节点
        // 同时保持一下当前进行组反转前的node的节点 需要连接后面
        // cout<<"begin"<<endl;
        int length{0};
        Node* p = head;
        while(p != nullptr) {
            length++;
            p = p->next;
        }
        Node* dummy = new Node();
        dummy->next = head;
        p = dummy;
        Node* pre = nullptr;
        Node* cur = head;
        for(;length >= k;length = length - k) {
            Node* out_next = p->next;
            for(int i{0}; i< k; i++) {
                Node* next = cur->next;
                cur->next = pre;
                pre = cur;
                cur = next;
            }
            p->next = pre;
            out_next->next = cur;
            p = out_next;
        }
        // cout<<"end"<<endl;
        return dummy->next;
    }
};

int main() {
    vector<int> nums{1,2,3,4,5};
    VectorUtils::PrintOneNums(nums);
    int k = 2;
    Node* head = ListUtils::ConvertToList(nums);
    Solution s;
    Node* result_node = s.RevertList(head, k);
    // if(result_node == nullptr) {
    //     cout<<"result_node length is nullptr"<<endl;
    // }
    // else cout<<"result_node length is not nullptr"<<endl;
    // int len{0};
    // Node* cur = result_node;
    // while(cur) {
    //     len++;
    //     cur = cur->next;
    // }
    // cout<<"result_node length is :"<<len<<endl;
    vector<int> result_nums = ListUtils::ConvertToVecor(result_node);
    // cout<<"result_nums size is :"<<result_nums.size()<<endl;
    VectorUtils::PrintOneNums(result_nums);
}