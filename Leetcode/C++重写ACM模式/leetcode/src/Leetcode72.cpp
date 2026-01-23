#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        //dp[i][j]定义为word1长度为i和word2长度为j的子字符串的最小编辑距离数
        // dp[i][0]不就是一直给word2一直增加i个操作数吗
        // dp[0][j] 也就是一直给word1增加j个操作数
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        dp[0][0] = 0;
        // for(int i{1}; i < word1.size() + 1; i++) {
        //     dp[i][0] = i;
        // }
        // for(int j{0}; j < word2.size() + 1; j++) {
        //     dp[0][j] = j;
        // }
        for(int i{1};i<word1.size() + 1;i++) {
            for(int j{1};j<word2.size() + 1;j++) {
                if(word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else {
                    dp[i][j] = min(dp[i][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i - 1][j - 1] + 1));
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};

int main() {
    string word1 = "horse";
    string word2 = "ros";
    Solution s;
    cout<<"minDistance is:"<<s.minDistance(word1,word2)<<endl;
}