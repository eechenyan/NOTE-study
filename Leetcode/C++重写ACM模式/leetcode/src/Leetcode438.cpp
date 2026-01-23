// 438. 找到字符串中所有字母异位词
// 已解答
// 中等
// 相关标签
// premium lock icon
// 相关企业
// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

 
// 使用一个map和双指针
// 示例 1:

// s = "acbd" p = "go"

// 输入: s = "cbaebabacd", p = "abc"
// 输出: [0,6]
// 解释:
// 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
// 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
//  示例 2:

// 输入: s = "abab", p = "ab"
// 输出: [0,1,2]
// 解释:
// 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
// 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
// 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

#include <unordered_map>
#include <iostream>
#include <string>
#include "VectorUtils.h"
using namespace std;

// 思路就是使用两个map去统计 和不定长滑动窗口 对于当前的那个right下标的 这个是会进到滑动窗口的 然后就看这个和p里面有没有 如果没有那么就不对 或者数量大于也是不对的 
// 这个时候就需要缩小窗口 缩小窗口就从左边离开 直到当前这个下标的和对应的p的哈希表里面的一样就说明目前是合理的 两个while循环 
class Solution {
public:
    vector<int> FindIndex(string s, string p) {
        unordered_map<char,int> umap;
        unordered_map<char,int> pmap;
        vector<int> result;
        for(char& c : p) {
            pmap[c]++;
        }
        int left{0};
        int right{0};
        while(right < s.size()) {
            // 1.进入窗口
            char c = s[right];
            umap[c]++;
            // 2.维护窗口
            while(umap[c] > pmap[c]) {
                char left_char = s[left];
                umap[left_char]--;
                left++;
            }
            // 3.更新答案 移动
            if(right - left + 1 == p.size()) result.push_back(left);
            right++;
        }
        return result;
    }
};

int main() {
    Solution s;
    string ss = "abab";
    string p = "ab";
    VectorUtils::PrintOneNums(s.FindIndex(ss,p));
}