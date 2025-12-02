#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {};
    ListNode(int _val, ListNode* _next) : val(_val), next(_next) {};
    ListNode(int _val) : val(_val), next(nullptr) {};
};

class Solution {
public:
    ListNode* AddTwoNumbers(ListNode* l1, ListNode* l2) {
        // 创建一个新的链表
        ListNode* dummy = new ListNode();
        ListNode* head = dummy;
        int temp{0};
        while(l1 != nullptr || l2 != nullptr || temp != 0) {
            int val1 = l1 == nullptr ? 0 : l1->val;
            int val2 = l2 != nullptr ? l2->val : 0;
            int sum = val1 + val2 + temp;
            int low_num = 0;
            if(sum >= 10) {
                low_num = sum % 10;
                temp = sum / 10;
            } else {
                temp = 0;
                low_num = sum;
            }
            ListNode* node = new ListNode(low_num);
            head->next = node;
            head = head->next;
            l1 = l1 -> next;
            l2 = l2 ->next;
        }
        return dummy->next;
    }
    ListNode* Convert(vector<int> nums) {
        ListNode* dummy = new ListNode();
        ListNode* head = dummy;
        for(int i{0}; i < nums.size(); i++) {
            ListNode* node = new ListNode(nums[i]);
            head->next = node;
            head = head->next;
        }
        return dummy->next;
    }
    void Print(ListNode* node) {
        while(node != nullptr) {
            cout<<node->val;
            node = node->next;
        }
        cout<<endl;
    }
};

int main() {
    Solution s;
    vector<int> nums1{2,4,3};
    vector<int> nums2{5,6,4};
    ListNode* list1 = s.Convert(nums1);
    ListNode* list2 = s.Convert(nums2);
    ListNode* result = s.AddTwoNumbers(list1,list2);
    s.Print(result);
}