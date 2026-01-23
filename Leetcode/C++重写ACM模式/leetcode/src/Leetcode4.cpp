// 4. 寻找两个正序数组的中位数

// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

// 算法的时间复杂度应该为 O(log (m+n)) 。

// 排序这两个数组，然后去中间 那这样子的时间复杂度是o m + n 我选择放弃时间复杂度的约束.......

// 变种：变为寻找两个正序数组里面第k个大的数字 这不就是数组中第k个大元素的变体嘛 使用快排 nlogn 的变体 快选 兄弟

#include <iostream>
#include "VectorUtils.h"
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int QuickSort(vector<double>& nums, int left, int right) {
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
    void Sort(vector<double>& nums, int left, int right, int y) {
        if(y < 0) return ;
        if(left >= right) return ;
        int base = QuickSort(nums, left, right);
        // if base > y left else right
        if(base > y) Sort(nums, left, base - 1, y);
        else if(base < y) Sort(nums, base + 1, right, y);
        else return ;
    }
};

int main() {
    Solution s;
    vector<int> nums1{1,3};
    vector<int> nums2{2};
    vector<double> nums;
    for(const int& i : nums1) nums.push_back(i * 1.0);
    for(const int& i : nums2) nums.push_back(i * 1.0);
    int lenth = nums.size();
    int k1  = lenth / 2; //奇数长度中位数就是这个位置，偶数位置就是中位数对的后一个位置
    int k2  = lenth / 2 - 1; //偶数下面的中位数对的前一个位置
    if(lenth % 2 != 0) {
        s.Sort(nums, 0, nums.size() - 1, k1);
        cout<<"middle number is :"<<nums[k1];
        // return nums[k1];
    } else {
        // 长度是偶数
        s.Sort(nums, 0, nums.size() - 1, k1);
        double number1 = nums[k1];
        cout<<"number1 is"<<number1<<endl;
        
        double number2 = nums[k2];
        cout<<"number2 is"<<number2<<endl;
        cout<<"middle number is :"<<(number1 + number2) / 2;
        // return (number1 + number2) / 2;
    }
}