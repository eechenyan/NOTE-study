#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t thread_count) : is_running(true) {
    for(size_t i{0};i < thread_count; i++) {
        // 这里就是线程池从任务队列取任务出来 然后一直执行
        std::thread t([this](){ //1.启动一个线程 然后丢到池里面运行
            while(this->is_running) {
                task tk = safe_queue.pop();
                if(tk) tk();
            }
        });
        thread_pool.push_back(std::move(t)); // 2.丢到线程池里面 使用move避免拷贝
    }
}

ThreadPool::~ThreadPool() {
    // 需要加锁关闭这个is_running 
    // 这里不是怕多个线程竞争修改这个is_running 而是为了可见性 因为有可能主线程结束之后析构了改变了整个is_running  但是子线程可能没有看到 所以需要加锁保证可见行
    // 其实可以使用原子变量
    // {
    //     std::unique_lock<std::mutex> lock(mtx);
    //     is_running = false;
    // }
    is_running = false; // atomic自带内存屏障，保证所有线程可见
    // 关闭所有线程
    // 如果这个时候任务队列里面没有任务了 这个时候所有线程都会在阻塞等待任务 所以提交空任务唤醒所有线程并关闭
    for(size_t i{0};i < thread_pool.size(); i++) {
        safe_queue.push([]() {}); //提交空任务唤醒所有线程
    }
    for(auto& th : thread_pool) {
        if(th.joinable()) {
            th.join(); //等待所有任务执行完毕
        }
    }
}

void ThreadPool::submit(task tk) {
    if(is_running) {
        safe_queue.push(tk); //提交任务
    }
}

