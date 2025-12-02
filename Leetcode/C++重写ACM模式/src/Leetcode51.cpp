// N皇后问题

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "VectorUtils.h"

using namespace std;

class Solution {
private:
    vector<string> chessboard;
    vector<vector<string>> result;
public:
    Solution(vector<string> _chessboard) : chessboard(_chessboard) {};
    ~Solution() {};
    bool IsValid(int x, int y, int col) {
        // 上
        for(int i{0}; i < x; i++) {
            if(chessboard[i][y] == 'Q') return false;
        }
        // 下

        // 45
        for(int i{x - 1}, j{y + 1}; i >= 0 && j < col; i--, j++) {
            if(chessboard[i][j] == 'Q') return false;
        }
        // 135
        for(int i{x - 1}, j{y - 1}; i >=0 && j>=0; i--, j--) {
            if(chessboard[i][j] == 'Q') return false;
        }
        return true;
    }

    void backtracking(int start_row) {
        if(start_row == chessboard.size()) {
            result.push_back(chessboard);
            return;
        }
        for(int j{0}; j < chessboard[0].size(); j++) {
            if(IsValid(start_row, j, chessboard[0].size()) == true) {
                chessboard[start_row][j] = 'Q';
                backtracking(start_row + 1);
                chessboard[start_row][j] = '.';
            }
        }
    }

    vector<vector<string>> GetResult() {
        return result;
    }
    int GetResultSize() {
        return result.size();
    }
};

int main() {
    vector<string> chessboard{".....",".....",".....",".....","....."};
    Solution s(chessboard);
    VectorUtils::PrintOneNums(chessboard);
    s.backtracking(0);
    VectorUtils::PrintTwoNums(s.GetResult());
    cout<<s.GetResultSize();

}