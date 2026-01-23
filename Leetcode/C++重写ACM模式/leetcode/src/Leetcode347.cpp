// 347. 前 K 个高频元素
// 已解答

// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

// 示例 1：
// 输入：nums = [1,2,1,2,1,2,3,1,3,2], k = 2
// 输出：[1,2]

// 思路：使用map来统计频率 然后遍历这个map 
// map：数值-频率 之后遍历map 或者map的size 然后建立vector桶 已频率为索引 建立对应的桶 然后把对应map的数字添加进去 最后倒叙遍历这个桶输出就是答案了

#include <iostream>
#include <unordered_map>
#include "VectorUtils.h"

using namespace std;

class Solution {
public:
    vector<int> FindKthNums(vector<int>& nums, int k) {
        unordered_map<int,int> umap;//数值-频率
        int max_fre{0};
        for(int& i : nums) {
            umap[i]++;
            max_fre = max(max_fre, umap[i]);
        }
        //建桶
        vector<vector<int>> bucket(max_fre + 1);
        for(auto it = umap.begin(); it != umap.end(); it++) {
            int fre = it->second;
            int num = it->first;
            bucket[fre].push_back(num);
        }
        vector<int> result;
        for(int i = bucket.size() - 1; i > 0 && result.size() < k; i--) {
            result.insert(result.end(), bucket[i].begin(), bucket[i].end());
        }
        return result;
    }
};

int main() {
    vector<int> nums{1,2,1,2,1,2,3,1,3,2};
    int k{3};
    Solution s;
    VectorUtils::PrintOneNums(s.FindKthNums(nums,k));
}