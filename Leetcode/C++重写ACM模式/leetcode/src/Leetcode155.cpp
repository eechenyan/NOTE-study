// 155. 最小栈

// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

// 实现 MinStack 类:

// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。

// 这道题目相当于就是维护当前数组下标为止的最小值。 
// 把栈看成数组 注意st栈顶就是当前下标的数值， 我们使用另外一个数组/栈st_min保存0-i的最小值，这个就是当前的最小值了。就是使用额外空间维护一个最小值就行了。
// 那么边界条件是什么 当第一个元素是没有可以和栈顶比较的 所以需要压入一个最大值 因此怎么比较都是它了。

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class MinStack {
private:
    stack<int> st;
    stack<int> st_min;
public:
    // MinStack() 初始化堆栈对象。
    MinStack() {
        st.push(INT_MAX);
    }
    // void push(int val) 将元素val推入堆栈。
    void push(int val) {
        int num = st.top();
        int min_num = min(val, num);
        st.push(val);
        st_min.push(min_num);
    }
    // void pop() 删除堆栈顶部的元素。
    void pop() {
        st.pop();
        st_min.pop();
    }
    // int top() 获取堆栈顶部的元素。
    int top() {
        return st.top();
    }
    // int getMin() 获取堆栈中的最小元素。
    int getMin() {
        return st_min.top();
    }
};
