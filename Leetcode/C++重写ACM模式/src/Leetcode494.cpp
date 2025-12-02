// 494. 目标和

// 给你一个非负整数数组 nums 和一个整数 target 。

// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

// 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

// 要找的是target + sum / 2 这个目标

// dp[i][j]表示背包容量为j的情况下 从0 - i 下标选取的刚好装满j的方案数目

#include <iostream>
#include "VectorUtils.h"
#include <algorithm>
#include <climits> 
using namespace std;

class Solution {
public:
    int FindSolution(vector<int> nums, int target) {
        int sum{0};
        for(const int& i : nums) {
            sum = sum + i;
        }
        int find_num = (sum + target) / 2;
        vector<vector<int>> dp(nums.size(), vector<int>(find_num + 1, 0));
        // dp[0][j] 当j == nums的时候 dp[0][j] = 1
        // dp[0][j] j 《 nums【0】的时候 没有方案 大于的时候也灭有
        // dp[i][0] 那就是不装 等于1
        for(int j{0};j<dp[0].size();j++) {
            if(j == nums[0]) dp[0][j] = 1;
        }
        for(int i{0};i<dp.size();i++) {
            dp[i][0] = 1;
        }
        for(int i{1};i<dp.size();i++) {
            for(int j{1};j<dp[0].size();j++) {
                // j > nums[i] 可以装的时候 可以考虑 小于的时候没有考虑的余地
                if(j < nums[i]) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];
                }
            }
        }
        return dp[nums.size() - 1][find_num];
    }
};

int main() {
    Solution s;
    vector<int> nums{1,1,1,1,1};
    int target{3};
    cout<<"result is:"<<s.FindSolution(nums,target)<<endl;
}