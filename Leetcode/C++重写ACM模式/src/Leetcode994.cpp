// 弗兰的句子
// 在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

// 值 0 代表空单元格；
// 值 1 代表新鲜橘子；
// 值 2 代表腐烂的橘子。
// 每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

// 返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

// 思路最小分钟就是dfs发生的次数？ 如果所有橘子都腐烂了 那么就返回结果 不然的话存在一个1 那就是返回-1

// dfs对于当前弗兰的句子进行腐蚀 直到不能再腐蚀 dfs需要一个全局变量统计时间 每发生一次就增1 

// 结果最后在遍历一下看看有没有不烂的句子 有的话就-1 没有的话就返回这个全局时间 只有2的时候才启动dfs

// 这个其实是统计这个dfs次数的 是不对的 正确的做法是在污染的时候 把污染时间传递给橘子

#include <iostream>
#include <vector>
#include "VectorUtils.h"
#include <climits>
#include <algorithm>

using namespace std;

class Solultion {
private:
    int time;
    vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
public:
    void dfs(vector<vector<int>> &graph, vector<vector<int>>& visited, int x, int y, int time) {
        //  if(visited[x][y] == 1) return ;
        if(visited[x][y] != 0 && time > visited[x][y]) return ; //说明已经被污染了, 而且再一次被污染到的时候这个时间比上一次污染的时间要大 说明当前不是最短路径 return
        visited[x][y] = time; //保留污染时间
        graph[x][y] = 2; //腐蚀
        for(int i{0}; i < dir.size(); i++) {
            int next_x = x + dir[i][0];
            int next_y = y + dir[i][1];
            if(next_x >= 0 && next_x < graph.size() && next_y >= 0 && next_y < graph[0].size() && visited[next_x][next_y] == 0 && graph[next_x][next_y] == 1) {
                dfs(graph, visited, next_x, next_y, time + 1); // 污染的时候 把时间也带到所有被污染的烂橘子那里去            
            }
        }  
    }
};

int main() {
    Solultion s;
    vector<vector<int>> graph{
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };
    // vector<vector<int>> graph{
    //     {2,1,1},
    //     {0,1,1},
    //     {1,0,1}
    // };
    // vector<vector<int>> graph{
    //     {0,2}
    // };
    int time{0};
    vector<vector<int>> visited(graph.size(), vector<int>(graph[0].size(), 0));
    for(int i{0};i<graph.size();i++) {
        for(int j{0};j<graph[0].size();j++) {
            if(graph[i][j] == 2 && visited[i][j] == 0) {
                s.dfs(graph,visited,i,j,0);
            }
        }
    }
    for(int i{0};i<visited.size();i++) {
        for(int j{0};j<visited[0].size();j++) {
            time = max(time, visited[i][j]);
            if(graph[i][j] == 1) {
                cout<<"fail! living station is:"<<i<<" "<<j<<endl;
                VectorUtils::PrintTwoNums(graph);
                return -1;
            }
        }
    }
    cout<<"success! time is:"<<time<<endl;
    VectorUtils::PrintTwoNums(graph);
}