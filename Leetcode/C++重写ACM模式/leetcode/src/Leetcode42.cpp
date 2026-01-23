// 42. 接雨水
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
// 示例 1
// 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
// 输出：6
// 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 


// 当前这个格子 接的雨水的量取决于当前块的高度 还有左右两边最大的一个高度 就是可以形成的最高高度

// 思路是维护两个dp数组 记录当前一个格子的左右两边的最大的格子高度

// dp_left[i] = max(dp_left[i - 1], height[i])

// 一个格子能够接的雨水就是 (min(dp_left,dpright) - height[i]) * 1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int MaxWater(vector<int> height) {
        vector<int> dp_left(height.size(), 0);
        vector<int> dp_right(height.size(), 0);
        // 初始化
        dp_left[0] = height[0];
        dp_right[height.size() - 1] = height[height.size() - 1];

        // dp
        for(int i{1}; i < height.size(); i++) {
            dp_left[i] = max(dp_left[i - 1], height[i]);
        }
        for(int i = height.size() - 2; i >= 0; i--) {
            dp_right[i] = max(dp_right[i + 1], height[i]);
        }
        int result{0};
        for(int i{0}; i < height.size(); i++) {
            int water = (min(dp_left[i], dp_right[i]) - height[i]) * 1;
            result = result + water;
        }
        return result;
    }
};

int main() {
    vector<int> height{4,2,0,3,2,5};
    Solution s;
    cout<<"result is:"<<s.MaxWater(height);
}