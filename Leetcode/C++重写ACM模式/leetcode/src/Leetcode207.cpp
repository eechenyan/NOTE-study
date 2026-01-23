// 207. 课程表
// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
// numCourses = 2, prerequisites = [[1,0],[0,1]]
// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

// 就是判断有没有环 使用三色法判断
// 当前遍历到当前节点设置为visit1 如果再一次遇到了1 那么设置为2 表示有环 退出
    // bool dfs(vector<vector<int>>& graph, vector<int>& visited, int x) { // 用于检测一个节点是否存在环的
    //     if(visited[x] == 1) return false; // 遇到自己了 说明有环
    //     if(visited[x] == 2) return true; // 被设置为2就说明可以正常遍历完 无环 也避免了重复检测
    //     visited[x] = 1;// 标记为正在访问
    //     //下面对可达路径进行深搜
    //     for(int i{0};i<graph[x].size();i++) {
    //         int next = graph[x][i];
    //         if(dfs(graph,visited,next) == false) return false;
    //     }
    //     visited[x] = 2;
    //     return true;
    // }

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
    int numCourses;
public:
    Solution(int _numCourses) : numCourses(_numCourses) {};
    ~Solution() {}
    bool dfs(vector<vector<int>>& graph, vector<int>& visited, int x) {
        if(visited[x] == 1) return false; 
        if(visited[x] == 2) return true; // 被设置为2就说明可以正常遍历完 无环 也避免了重复检测
        visited[x] = 1;
        vector<int> cur = graph[x];
        for(int i{0}; i < cur.size(); i++) {
            int next_x = cur[i];
            if(next_x >= 0 && next_x < numCourses) {
                bool fage = dfs(graph,visited,next_x);
                if(fage == false) return false;
            }
        }
        visited[x] = 2;
        return true;
    }
};

int main() {
    // 建立邻接图
    int numCourses{2};
    vector<vector<int>> prerequisites{{0,1}};
    vector<vector<int>> graph(numCourses);
    vector<int> visited(numCourses, 0);
    for(int i{0}; i < prerequisites.size(); i++) {
        int first = prerequisites[i][0];
        int second = prerequisites[i][1];
        graph[first].push_back(second);
    }
    Solution s(numCourses);
    for(int i{0}; i < numCourses; i++) {
        bool fage = s.dfs(graph,visited,i);
        if(fage == false) {
            cout<<"fasle"<<endl;
            return 0;
        }

    }
    cout<<"true"<<endl;
    return 1;
}