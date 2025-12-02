// 802. 找到最终的安全状态
// 已解答
// 有一个有 n 个节点的有向图，节点按 0 到 n - 1 编号。图由一个 索引从 0 开始 的 2D 整数数组 graph表示， graph[i]是与节点 i 相邻的节点的整数数组，这意味着从节点 i 到 graph[i]中的每个节点都有一条边。

// 如果一个节点没有连出的有向边，则该节点是 终端节点 。如果从该节点开始的所有可能路径都通向 终端节点（或另一个安全节点），则该节点为 安全节点。

// 返回一个由图中所有 安全节点 组成的数组作为答案。答案数组中的元素应当按 升序 排列。

// 这里这个graph就是已经建好的邻接表了 你只需要返回路径上没有环的节点

#include <iostream>
#include <vector>
#include <algorithm>
#include "VectorUtils.h"

using namespace std;

class Solution{
private:
public:
    Solution() {};
    ~Solution() {};
    bool dfs(vector<vector<int>>& graph, vector<int>& visited, int x) {
        if(visited[x] == 1) return false; // 遇到正在访问的节点说明有环了
        if(visited[x] == 2) return true; // 遇到标记为2的说明这个节点已经验证了没有环了
        visited[x] = 1;
        for(int i{0}; i < graph[x].size(); i++) {
            int next_x = graph[x][i];
            bool fage = dfs(graph, visited, next_x);
            if(fage == false) return false;
        }
        //一条路径遍历完了并且没有环,把当前节点设置为2
        // 但是由于递归的存在,栈上面的所有节点,就是路径上面的所有节点都会被设置为了2
        visited[x] = 2;
        return true;
    }
};

int main() {
    Solution s;
    vector<vector<int>> graph{{1,2},{2,3},{5},{0},{5},{},{}};
    vector<int> vistied(graph.size(), 0);
    vector<int> result;
    for(int i{0}; i < graph.size(); i++) {
        bool fage = s.dfs(graph, vistied, i);
        if(fage == true) result.push_back(i);
    }
    VectorUtils::PrintOneNums(result);
}
