// 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

// 测试用例的答案是一个 32-位 整数。

// 请注意，一个只包含一个元素的数组的乘积是这个元素的值。

// dp[i]定义为当前的最大乘积 dp[i] = dp[i - 1] * nums[i] 和 当前数字取最大值

// 如果nums[i]是负数的话 那么乘积就是最小值乘当前数字 

// 那么就需要维护两个dp数组 一个正的 一个负的

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int FindMaxMul(vector<int> nums) {
        vector<int> dpmax(nums.size(), 0);
        vector<int> dpmin(nums.size(), 0);
        dpmax[0] = nums[0];
        dpmin[0] = nums[0];
        int max_mul = nums[0];
        for(int i{1};i<nums.size();i++) {
            int cur_num = nums[i];
            if(cur_num > 0) {
                dpmax[i] = max(dpmax[i - 1] * cur_num, nums[i]); //从这里更新开始截断 出现新i
                dpmin[i] = min(dpmin[i - 1] * cur_num, nums[i]);
            }
            else {
                dpmax[i] = max(dpmin[i - 1] * cur_num, nums[i]);
                dpmin[i] = min(dpmax[i - 1] * cur_num, nums[i]);
            }
            max_mul = max(max_mul, dpmax[i]);
        }
        return max_mul;
    }
};

int main() {
    Solution s;
    vector<int> nums{2,3,-2,4};
    cout<<s.FindMaxMul(nums)<<endl;
}