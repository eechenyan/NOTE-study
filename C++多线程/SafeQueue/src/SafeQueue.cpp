#include "SafeQueue.h"

SafeQueue::SafeQueue(): is_running(true) {};

void SafeQueue::push_nums(int nums) {
    std::unique_lock<std::mutex> lock(mtx);
    safe_queue.push(nums);
    cv.notify_one(); //写入一个数据就唤醒一个消费者
}

int SafeQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this](){ 
        if(safe_queue.empty() == false || is_running == false) return true;
        else return false;
    }); // 
    // 不空或者停止了生产（避免生产结束消费者一直阻塞）就可以往下走 不然释放锁进入阻塞
    if(safe_queue.empty() == true && is_running == false) return -1; //空了而且结束生产 返回一个-1 让最外面的消费者退出循环
    int nums = safe_queue.front();
    safe_queue.pop();
    return nums;
}

size_t SafeQueue::size() {
    std::unique_lock<std::mutex> lock(mtx);
    return safe_queue.size();
}

bool SafeQueue::empty() {
    std::unique_lock<std::mutex> lock(mtx);
    return safe_queue.empty();
}

void SafeQueue::notify() {
    std::unique_lock<std::mutex> lock(mtx);
    is_running = false;
    cv.notify_all();
}