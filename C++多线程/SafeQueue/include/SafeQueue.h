// 设计一个并发安全的队列 要求包含push pop empty size的函数
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>

class SafeQueue {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<int> safe_queue;
    bool is_running;
public:
    SafeQueue();
    void push_nums(int nums);
    int pop();
    size_t size();
    bool empty();
    void notify();
};
