#include "SafeQueue.h"

void SafeQueue::push(task tk) {
    std::unique_lock<std::mutex> lock(mtx);
    // 不涉及什么顺序执行 直接谁抢到锁了谁执行
    safe_queue.push(std::move(tk)); // 移动语义减少开销
    cv.notify_one();
}

task SafeQueue::pop() {
    // 这里实现的pop保证了一定非空
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock,[this](){
        return this->safe_queue.empty() == false;
        // 队列为空的时候 释放锁
        // 注意wait的第二个条件是true就继续，false的话就释放锁 所以这里非空的时候蚩尤锁继续进行
    });
    // 非空进行取出任务操作
    task tk = std::move(safe_queue.front());
    safe_queue.pop();
    return tk;
}

bool SafeQueue::empty() {
    // 不涉及什么顺序执行 直接谁抢到锁了谁执行
    std::unique_lock<std::mutex> lock(mtx);
    return safe_queue.empty();
}

