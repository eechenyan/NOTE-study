// 209. 长度最小的子数组

// 给定一个含有 n 个正整数的数组和一个正整数 target 。
// 找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
// 输入：target = 7, nums = [2,3,1,2,4,3]
// 输出：2
// 解释：子数组 [4,3] 是该条件下的长度最小的子数组。
 

#include <iostream>
#include <vector>
#include "VectorUtils.h"
#include <climits>
using namespace std;

class Solution {
public:
    int FindSubAry(const vector<int>& nums, int target) {
        int left{0},right{0};
        int result{INT_MAX};
        int cur_sum{0};
        while(right < nums.size()) {
            cur_sum = cur_sum + nums[right];
            while(cur_sum >= target) {
                result = min(result, right - left + 1);
                int left_num = nums[left];
                cur_sum = cur_sum - left_num;
                left++;
            }
            right++;
        }
        return result == INT_MAX ? 0 : result;
    }
};

int main() {
    Solution s;
    vector<int> nums{2,3,1,2,4,3};
    int target{7};
    cout<<"result is:"<<s.FindSubAry(nums, target)<<endl;
}
