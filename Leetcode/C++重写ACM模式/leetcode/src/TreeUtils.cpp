#include <iostream>
#include <queue>
#include "TreeUtils.h"

using namespace std;

TreeNode* TreeUtils::VectorToTree(const vector<int>& nums) {
    // 每次使用队列存储当前要处理的节点 因为必然是两两成对处理的 所以存进去暂存就解决了顺序匹配问题
    // 但是其实并不要求手动实现这个层序建树的函数吧，直接手动建树就可以了
    if(nums.size() == 0) return nullptr;
    // 创建队列
    queue<TreeNode*> q;
    TreeNode* root = new TreeNode(nums[0]);
    q.push(root);
    size_t i{1};
    while(i < nums.size() && q.empty() == false) {
        // 取出当前节点进行后面的操作
        TreeNode* cur = q.front();
        q.pop();
        // 处理左节点 注意判断是否是-1
        if(i < nums.size()) {
            int LeftVal = nums[i];
            if(LeftVal != -1) {
                TreeNode* left = new TreeNode(nums[i]);
                cur->left = left;
                q.push(left);
            }
            i++;
        }
        // 处理右节点
        if(i < nums.size()) {
            int RightVal = nums[i];
            if(RightVal != -1) {
                TreeNode* right = new TreeNode(nums[i]);
                cur->right = right;
                q.push(right);
            }
            i++;
        }
    }
    return root;
}

vector<vector<int>> TreeUtils::PrintTree(TreeNode* root) {
    if(root == nullptr) return {{-1}};
    // 层序遍历二叉树 打印当前节点的时候把左右孩子压进去队列呗
    queue<TreeNode*> q;
    q.push(root);
    vector<vector<int>> result;
    while(q.empty() == false) {
        // 取出当前节点
        vector<int> ans;
        size_t len = q.size();
        for(size_t i{0};i<len;i++) {
            TreeNode* cur = q.front();
            q.pop();
            ans.push_back(cur->val);
            // 注意 不为空才入队!!
            if(cur->left != nullptr) q.push(cur->left);
            if(cur->right != nullptr) q.push(cur->right);
        }
        result.push_back(ans);
    }
    return result;
}

void TreeUtils::destory(TreeNode*& root) { 
    // 不能传递* 而是要传递*& 前者是值传递 拷贝了副本修改的是副本的值 后者是引用才可以同步修改外部指针的值
    if(root == nullptr) return ;
    destory(root->left);
    destory(root->right);
    delete root;
    root = nullptr; //避免野指针
}