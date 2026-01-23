#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int IsVaild(string s) {
        // 判断一个字符串是否合法
        // 栈模拟 遇到左括号就入栈 遇到右括号就找相应的左括号(hasp map)，然后看栈顶是不是这个 不是的话就错误 或者栈顶是空的那也错
        // 也就是说遇到右括号就无非判单栈顶的两种状态 空错 非空继续判断
        // 最终循环结束栈为空那就合法
        stack<char> st;
        for(char& c : s) {
            if(c >= 'a' && c <= 'z') continue;
            else if(c == '(') st.push(c);
            else if(c == ')') {
                if(st.empty() == true) return 0; //栈是空的 说明第一个就是右括号 非法
                if(st.empty() == false && st.top() == '(') st.pop(); //暂时合法
                else return 0; //错误
            }
        }
        if(st.empty() == true) return 111;
        return 0;
    }
};

int main() {
    Solution s;
    string str = "(a()())";
    cout<<s.IsVaild(str)<<endl;
}

