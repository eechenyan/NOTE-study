// 这个是线程池 支持消费任务 创建一个容量的线程池 然后每个线程从任务队列里面取出任务进行消费
// 什么时候消费结束 需要一个标志位 就是当前任务完成之后就结束当前任务 但是线程池需要回到池中并抽取队列剩下的任务
#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <atomic>
#include "SafeQueue.h"

using task = std::function<void()>;

class ThreadPool {
private:
    std::mutex mtx;
    SafeQueue safe_queue;
    std::atomic<bool> is_running;
    std::vector<std::thread> thread_pool;
public:
    ThreadPool(size_t thread_count);
    ~ThreadPool();
    void submit(task tk);
};