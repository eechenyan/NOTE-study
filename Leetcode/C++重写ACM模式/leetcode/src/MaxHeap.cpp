#include <iostream>
#include <queue>
#include <vector>
using namespace std;


// 大根堆 用于找前k个大的数字

// struct Node {
//     int val; //数值
//     int vec_idx; //位于第几个数组
//     int elm_idx; //位于数组中的第几个位置
//     bool operator<(const Node& other) const { // 重载运算符 满足《 大根堆
//         return val < other.val;
//     }
//     Node(int _val, int _vec_idx, int _elm_idx) : val(_val), vec_idx(_vec_idx), elm_idx(_elm_idx) {};
// };

// class Solution {
// private:
//     priority_queue<Node> max_heap;
// public:
//     vector<int> FindKnum(vector<vector<int>>& nums, int k) {
//         vector<int> result;
//         // 第一步 取出每一个vector的最后一个元素压入大根堆
//         for(int i{0}; i < nums.size(); i++) {
//             vector<int> num_i = nums[i];
//             max_heap.push(Node(num_i[num_i.size() - 1], i, num_i.size() - 1));
//         }
//         for(int i{0}; i < k; i++) {
//             // 循环k步 依次取出堆顶元素并压入
//             Node cur = max_heap.top();
//             max_heap.pop();
//             result.push_back(cur.val);
//             int nex_vec_idx = cur.vec_idx; // 当前的数组；
//             int nex_elm_idx = cur.elm_idx - 1;
//             if(nex_elm_idx >= 0) {
//                 max_heap.push({nums[nex_vec_idx][nex_elm_idx], nex_vec_idx, nex_elm_idx});
//             }
//         }
//         return result;
//     }
// };


// ----------------------------------------------------
// 小根堆 用于找最小的前k个元素
struct Node {
    int val;
    int arr_idx;
    int num_idx;
    bool operator<(const Node& other) const {
        return val > other.val;
    };
};

class Solution {
private:
    priority_queue<Node> min_heap;
public:
    vector<int> FindKnum(vector<vector<int>> nums, int k) {
        // 第一步把数组的第一个元素压入小根堆
        // 第二步取出堆顶的元素 之后这个元素的数组里面取出数组在压入小根堆 排序小根堆自己做
        vector<int> result;
        // 第一步把数组的第一个元素压入小根堆
        for(int i{0}; i < nums.size(); i++) {
            min_heap.push({nums[i][0], i, 0});
        }
        // 第二步取出堆顶的元素 之后这个元素的数组里面取出数组在压入小根堆 排序小根堆自己做
        for(int i{0}; i < k; i++) {
            Node cur = min_heap.top();
            min_heap.pop();
            result.push_back(cur.val);
            int nex_arr_idx = cur.arr_idx;
            int nex_num_idx = cur.num_idx + 1;
            if(nex_num_idx < nums[nex_arr_idx].size()) {
                min_heap.push({nums[nex_arr_idx][nex_num_idx], nex_arr_idx, nex_num_idx});
            }
        }
        return result;
    }
};
int main() {
    vector<vector<int>> nums{
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {0, 9, 10, 11}
    };
    Solution s;
    vector<int> result = s.FindKnum(nums,5);
    for(const auto& i : result) {
        cout<<i<<" ";
    }
    cout<<endl;
}