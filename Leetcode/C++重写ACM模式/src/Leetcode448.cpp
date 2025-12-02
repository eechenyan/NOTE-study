#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 思路是分成两个一样的数组 然后上数组的数字当成下标 注意要减一
// 上数组的下标对应的下数组的数字进行一个标记（做负数） 遍历一次
// 第二次遍历如果存在缺失的数字那么会有整数存在 这个整数对应的下标就是缺失的数字了
class Solution {
public:
    vector<int> FindLossNum(vector<int> nums) {
        vector<int> result;
        for(int i{0};i<nums.size();i++) {
            int index = nums[i] > 0 ? nums[i] - 1 : abs(nums[i]) - 1;
            if(nums[index] > 0) nums[index] = -nums[index];
            else nums[index] = nums[index];
        }
        for(int i{0};i<nums.size();i++) {
            if(nums[i] > 0) result.push_back(i + 1);
        }
        return result;
    }

    void PrintVec(vector<int> nums) {
        for(int i{0};i<nums.size();i++) {
            cout<<nums[i]<<" ";
        }
        cout<<endl;
    }
};

int main() {
    Solution s;
    vector<int> nums{1,1,2,2,6,5,4};
    s.PrintVec(s.FindLossNum(nums));
}