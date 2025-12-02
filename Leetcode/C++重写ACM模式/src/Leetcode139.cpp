// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true
// 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// dp[i]表示以i结尾的范围的字符可以被单词填满 那么dp[i]就和dp[j]和当前单词的长度有关 对于每一个长度都遍历worddict长度不就行了？

class Solution {
public:
    bool WordBreak(std::string s, std::vector<string> word_dict) {
        vector<bool> dp(word_dict.size(), false);
        for(int i{0};i<word_dict.size();i++) {
            for(const string& s : word_dict) {
                if(i < s.size()) continue;
                else {
                    int len = s.size();
                    int j = i - len + 1;
                    string ss = s.substr(j, len);
                    if(ss == s && dp[j] == true) dp[i] = true; 
                }
            }
        }
        return dp[word_dict.size() - 1];
    }
};

int main() {
    Solution s;
    string str = "leetcode";
    vector<string> word_dict{"leet", "code"};
    cout<<"结果是 1111"<<endl;
    cout<<"结果是"<<s.WordBreak(str,word_dict)<<endl;
}