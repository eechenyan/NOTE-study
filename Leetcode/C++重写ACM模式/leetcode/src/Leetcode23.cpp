// 23. 合并 K 个升序链表

// 给你一个链表数组，每个链表都已经按升序排列。

// 请你将所有链表合并到一个升序链表中，返回合并后的链表。

// 示例 1：
// 输入：lists = [[1,4,5],[1,3,4],[2,6]]
// 输出：[1,1,2,3,4,4,5,6]
// 解释：链表数组如下：
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// 将它们合并到一个有序链表中得到。
// 1->1->2->3->4->4->5->6

// 归并排序 递归-分治 两两有序链表进行合并
#include <iostream>
#include "VectorUtils.h"
#include "ListUtils.h"
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    Node* Merge(Node* node1, Node* node2) {
        Node* dummy = new Node();
        Node* p = dummy;
        while(node1 != nullptr && node2 != nullptr) {
            if(node1->val <= node2->val) {
                p->next = node1;
                node1 = node1->next;
                p = p->next;
            } 
            else {
                p->next = node2;
                node2 = node2->next;
                p = p->next;
            }
        }
        p->next = node1 == nullptr ? node2 : node1;
        return dummy->next;
    }
    // 递归-分治 需要一个递归来实现最后的逻辑
    Node* traversal(vector<Node*>& NodeList, int left, int right) {
        if(left > right) return nullptr; //区间违法 那就是递归结束
        if(left == right) return NodeList[left]; //区间相等 那就是只有一个链表 这个链表是有序的
        // 后序遍历
        int k = left + (right - left) / 2;
        Node* left_node = traversal(NodeList, left, k);
        Node* right_node = traversal(NodeList, k + 1, right);
        return Merge(left_node, right_node);
    }
};

int main() {
    Solution s;
    vector<int> nums1{1,4,5};
    vector<int> nums2{1,3,4};
    vector<int> nums3{2,6};
    Node* node1 = ListUtils::ConvertToList(nums1);
    Node* node2 = ListUtils::ConvertToList(nums2);
    Node* node3 = ListUtils::ConvertToList(nums3);
    vector<Node*> NodeList{node1, node2, node3};
    Node* result = s.traversal(NodeList, 0, NodeList.size() - 1);
    vector<int> return_num = ListUtils::ConvertToVecor(result);
    VectorUtils::PrintOneNums(return_num);
}
