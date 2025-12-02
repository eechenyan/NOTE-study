// 核心思路：对于 nums 中的元素 x，以 x 为起点，不断查找下一个数 x+1,x+2,⋯ 是否在 nums 中，并统计序列的长度。
// 使用哈希表来优化
#include <iostream>
#include <vector>
#include "VectorUtils.h"
#include <unordered_set>

using namespace std;

class Solution {
public:
    int FindMaxLen(vector<int>& nums) {
        unordered_set<int> uset(nums.begin(), nums.end());
        int max_len{0};
        for(int i{0}; i < nums.size(); i++) {
            int x = nums[i];
            if(uset.find(x - 1) != uset.end()) continue; //实现on的关键
            int next_x = x + 1;
            while(uset.find(next_x) != uset.end()) {
                next_x++;
            }
            // 最后的数字是next-x - 1,因为最后找到next_x还会自增的
            max_len = max(max_len, next_x - x);
        }
        return max_len;
    }
};

int main() {
    Solution s;
    vector<int> nums{0,3,7,2,5,8,4,6,0,1,9,11,10,13,12,15,16,14};
    cout<<"max len is:"<<s.FindMaxLen(nums)<<endl;
}