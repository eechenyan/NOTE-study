// 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

// 给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int FindMoney(vector<int> money) {
        // dp[i]表示下标-i范围内能够获得最大的金额
        // dp[i] = money-i + dp-i-2 和dp-i-1 取最大
        vector<int> dp(money.size(), 0);
        dp[0] = money[0];
        dp[1] = max(dp[0], money[1]);
        for(int i{2};i<money.size();i++) {
            dp[i] = max(dp[i - 1], money[i] + dp[i - 2]);
        }
        return dp[dp.size() - 1];
    }
};

int main() {
    Solution s;
    vector<int> money{2,7,9,3,1};
    cout<<"Max Money is: "<<s.FindMoney(money)<<endl;
}