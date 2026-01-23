// 这个是实现线程安全的任务队列 - 支持无参数无返回值的任务调用
// 因为线程池里面的线程会从这个任务队列里面取任务 所以这个队列要是线程安全的
// 队列要支持push和pop操作 但是需要上锁
#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using task = std::function<void()>; //用function封装一个返回值为void 无参数的函数模板

class SafeQueue {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<task> safe_queue;
public:
    void push(task tk);
    task pop();
    bool empty();
};