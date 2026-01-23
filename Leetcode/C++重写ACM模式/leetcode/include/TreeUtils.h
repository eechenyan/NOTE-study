#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 实现二叉树的工具类
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int _val) :  val(_val), left(nullptr), right(nullptr) {};
    TreeNode(int _val, TreeNode* _left, TreeNode* _right) :  val(_val), left(_left), right(_right) {};
};

class TreeUtils{
public:
    //工具类不需要构造和析构 但是需要手动实现主动释放的函数

    /**
     * 递归释放二叉树所有节点内存，并将根指针置空
     * @param root 二叉树根节点指针的引用（确保外部指针同步置空）
     */
    static void destory(TreeNode*& head);  //必须传引用

    /**
     * 从层序遍历序列构建二叉树
     * @param nums 层序遍历序列，-1 表示空节点
     * @return 构建的二叉树根节点指针，空序列返回 nullptr
     */
    static TreeNode* VectorToTree(const vector<int>& nums); //加上const修饰更加安全

    /**
     * 层序遍历二叉树并返回每层节点值
     * @param root 二叉树根节点指针
     * @return 嵌套向量，每层节点值组成一个子向量，空树返回 {{-1}}
     */
    static vector<vector<int>> PrintTree(TreeNode* root); 

};