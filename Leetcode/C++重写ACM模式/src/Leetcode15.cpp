#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。

// 注意：答案中不可以包含重复的三元组。

// 三指针 双指针一定要使用while！！！
class Solution {
public:
    vector<vector<int>> FindNumVec(vector<int> nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for(int i{0};i<nums.size();i++) {
            if(i > 0 && nums[i] == nums[i - 1]) continue; // i去重
            int right = nums.size() - 1;
            int left = i + 1;
            while(left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if(sum > target) right--;
                else if(sum < target) left++;
                else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while(left < right && nums[left] == nums[left + 1]) left++;
                    while(left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                }
            }
        }
        return result;
    }
    void PrintVec(vector<vector<int>> result) {
        if(result.size() == 0) return ;
        int row = result.size();
        int col = result[0].size();
        for(int i{0};i<row;i++) {
            for(int j{0};j<col;j++) {
                cout<<result[i][j]<<" ";
            }
            cout<<endl;
        }
    };
};

int main() {
    Solution s;
    int target{0};
    vector<int> nums{-1,0,1,2,-1,-4};
    vector<vector<int>> result = s.FindNumVec(nums,target);
    s.PrintVec(result);
}