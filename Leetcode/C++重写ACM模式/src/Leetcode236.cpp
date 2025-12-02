#include <iostream>
#include <algorithm>
#include "TreeUtils.h"
#include "VectorUtils.h"

using namespace std;

class Solution {
public:
    TreeNode* FindNode(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        TreeNode* left = FindNode(root->left,p,q);
        TreeNode* right = FindNode(root->right,p,q);
        // cur
        if(root == q || root == p) return root;
        // return
        if(left == nullptr && right != nullptr) return right;
        if(left != nullptr && right == nullptr) return left;
        if(left != nullptr && right != nullptr) return root;
        if(left == nullptr && right == nullptr) return nullptr;
        return nullptr; // 永远不会到达这里
    }
};

int main() {
    Solution s;
    vector<int> nums{3,5,1,6,2,0,8,-1,-1,7,4};
    TreeNode* head = TreeUtils::VectorToTree(nums);
    TreeNode* p = head->left;
    TreeNode* q = head->left->right->right;
    TreeNode* father = s.FindNode(head,p,q);
    cout<<father->val<<endl;
    vector<vector<int>> result = TreeUtils::PrintTree(head);
    TreeUtils::destory(head);
    VectorUtils::PrintTwoNums(result);
}