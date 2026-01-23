// 给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

// 我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

// 必须在不使用库内置的 sort 函数的情况下解决这个问题。

// 你能想出一个仅使用常数空间的一趟扫描算法吗？

// 本质不就是排序嘛 排序那就是快速排序和冒泡排序了

// 刚好复习快排了

#include <iostream>
#include "VectorUtils.h"
#include <climits> 
#include <algorithm>

using namespace std;

class Solution {
public:
    int QuickSort(vector<int>& nums, int left, int right) {
        // 快排的思路是找到一个base 然后一轮就是比他小的在左边 比他大的在右边
        // 「一次划分定一值，递归分治定全局」
        int base = nums[left];
        while(left < right) {
            while(left < right && nums[right] >= base) right--;
            swap(nums[left], nums[right]);
            while(left < right && nums[left] <= base) left++;
            swap(nums[left], nums[right]);
        }
        nums[left] = base;
        return left;
    }
    // 递归-分治
    void Sort(vector<int>& nums, int left, int right) {
        if(left >= right) return ;
        int base = QuickSort(nums,left,right);
        Sort(nums,left,base); // 必须要base - 1 这个基准元素不需要在排序了 因为它已经处在正确位置了
        Sort(nums,base + 1, right);
    }
};

int main() {
    vector<int> nums{5,4,3,2,1};
    Solution s;
    s.Sort(nums,0,nums.size() - 1);
    VectorUtils::PrintOneNums(nums);
}