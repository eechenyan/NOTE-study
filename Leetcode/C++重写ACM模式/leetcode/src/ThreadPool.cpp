// // 线程池 一个并发安全的任务队列
// // 一个工作标志位 一个thread的vector线程池 构造的时候就开始每次都从队列里面取出任务进行工作
// // 一个submit-task函数 提交任务到任务队列里面
// // 析构函数 关闭所有线程。线程池就是消费者
// // 一般我们的线程就是 执行一个任务然后死掉 只存在于主线程声明周期的一部分 但是线程池的涉及理念是 我创建了线程 这个线程一直执行不同的任务 只要队列里面还有任务 那我的线程就一直不死 一直执行 
// // 那最后什么时候关闭线程 对象析构的时候
// #include <iostream>
// #include <queue>
// #include <vector>
// #include <mutex>
// #include <condition_variable>
// #include <thread>
// #include <functional>
// #include <chrono>
// using Task = std::function<void()>;
// class SafeQueue {
// private:
//    std::mutex mtx;
//    std::condition_variable cv;
//    std::queue<Task> que;
//    bool is_running;
// public:
//     SafeQueue(): is_running(true) {};
//     void push(Task task) {
//         std::unique_lock<std::mutex> lock(mtx);
//         que.push(std::move(task));
//         cv.notify_one();
//     }
//     Task pop() {
//         std::unique_lock<std::mutex> lock(mtx);
//         cv.wait(lock, [this](){ return this->que.empty() == false || this->is_running == false;});
//         if(que.empty() == true && is_running == false) return {}; //注意这里返回的是{} 空的funtion 而不是[](){}
//         Task task = que.front();
//         que.pop();
//         return task;
//     }
//     void is_ok() {
//         std::unique_lock<std::mutex> lock(mtx);
//         is_running = false;
//         cv.notify_all();
//     }
// };

// class ThreadPool {
// private:
//     SafeQueue task_que;
//     std::vector<std::thread> work_pool;
//     int pool_size;
// public:
//     ThreadPool(int _pool_size) :pool_size(_pool_size) {
//         for(int i{0}; i < pool_size; i++) {
//             // 需要创建函数丢到线程池里面运行
//             auto lambda = [this](){
//                 while(1) {
//                     Task task = task_que.pop();
//                     if(!task) break; // 如果是空任务说明队列已经空了而且结束了 这个时候就需要退出线程了
//                     task();
//                 }
//             };
//             work_pool.emplace_back(std::move(lambda)); //启动线程
//         }
//     }
//     void submit_task(Task task) {
//         task_que.push(task);
//     }
//     ~ThreadPool() {
//         task_que.is_ok();
//         for(int i{0}; i < work_pool.size(); i++) {
//             work_pool[i].join(); // 这里的join是为了等待最后退出的那个空任务执行完毕，也就是为了等待所有的线程执行完毕
//         }
//     }
// };

// int main() {
//     ThreadPool pool(2);
//     std::mutex cout_mtx;
//     size_t task_count{50};
//     // 提交多个任务
//     for(size_t i{0};i < task_count; i++) {
//         auto lambda = [i,&cout_mtx](){ //cout_mtx本身不可拷贝，所以只能引用捕获
//             std::unique_lock<std::mutex> lock(cout_mtx);
//             std::this_thread::sleep_for(std::chrono::microseconds(300000));
//             std::cout<<"this is thread"<<i<<" thread id is :"<<std::this_thread::get_id()<<std::endl;
//         };
//         pool.submit_task(lambda);
//     };

//     // 消费者进行消费输出

//     // 在作用域结束之后就是pool析构的时候要join一下 因为要等所有的消费者安全结束。
// }

// 2025.12.17第二次写
// 最简单的一个线程池 首先实现并发队列 之后实现线程池
// #include <iostream>
// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <thread>
// #include <functional>

// using Task  = std::function<void()>;

// class SafeQueue {
// private:
//     std::mutex mtx;
//     std::condition_variable cv;
//     bool is_ok;
//     std::queue<Task> que;
// public:
//     SafeQueue() : is_ok(true) {};
//     void push(Task tk) {
//         if(is_ok == false) return ;
//         std::unique_lock<std::mutex> lock(mtx);
//         que.push(tk);
//         cv.notify_one();
//     }
//     Task pop() {
//         // 需要考虑到没结束和结束两种情况
//         std::unique_lock<std::mutex> lock(mtx);
//         cv.wait(lock,[this](){ return this->que.empty() == false || this->is_ok == false;});
//         if(is_ok == false && que.empty() == true) {
//             return {}; 
//         }
//         Task tk = que.front();
//         que.pop();
//         return tk;
//     }
//     void shutdown() {
//         std::unique_lock<std::mutex> lock(mtx);
//         is_ok = false;
//         cv.notify_all();
//     }
// };

// class ThreadPool {
// private:
//     SafeQueue task_que;
//     std::vector<std::thread> thread_pool;
//     size_t cap;
// public:
//     void submit(Task tk) {
//         task_que.push(tk);
//     }
//     ThreadPool(size_t _cap) : cap(_cap) {
//         // 启动线程 从队列里面不断取出任务进行处理
//         for(size_t i{0}; i < cap; i++) {
//             auto lamdba = [this](){
//                 while(1) {
//                     Task tk = this->task_que.pop();
//                     if(!tk) break;
//                     tk();
//                 }
//             };
//             std::thread t(lamdba);
//             thread_pool.emplace_back(std::move(t));
//         }
//     }
//     ~ThreadPool() {
//         task_que.shutdown();
//         for(auto& it : thread_pool) {
//             if(it.joinable()) {
//                 it.join();
//             }
//         }
//     }
// };

// int main() {
//     size_t cap{2};
//     ThreadPool pool(cap);
//     std::mutex cout_mtx;
//     // 压入十个任务
//     for(int i{1}; i < 10; i++) {
//         Task tk = [i, &cout_mtx](){
//             std::unique_lock<std::mutex> lock(cout_mtx);
//             std::cout<<"This word id is"<<i<<" and thread id is"<<std::this_thread::get_id()<<std::endl;
//         };
//         pool.submit(tk);
//     }

//     std::cout<<"main is over"<<std::endl;
// }

// 2025.12.30第三次写
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

using task = std::function<void()>;

class SafeQueue {
private:
    std::queue<task> que;
    std::mutex mtx;
    std::condition_variable cv;
    bool is_ok;
public:
    SafeQueue(): is_ok(true) {};
    void push(task tk) {
        std::unique_lock<std::mutex> lock(mtx);
        que.push(tk);
        cv.notify_one();
    }
    task pop() {
        // 弹出的情况需要考虑到队列空和队列不空的情况
        std::unique_lock<std::mutex> lock(mtx);
        //队列不空的时候往下走
        cv.wait(lock,[this](){ return this->que.empty() == false || this->is_ok == false;});
        if(que.empty() == true && is_ok == false) return {};
        task tk = que.front();
        que.pop();
        return tk;
    }
    void shutdown() {
        std::unique_lock<std::mutex> lock(mtx);
        is_ok = false;
        cv.notify_all();
    }
};

class ThreadPool {
    // 一个线程池要有任务队列 锁 容量 线程池
    // 提交任务
private:
    std::vector<std::thread> work_thread;
    int cap;
    SafeQueue task_que;
public:
    void submit(task tk) {
        task_que.push(tk);
    }
    ThreadPool(int _cap) : cap(_cap) {
        // 构造就是从任务队列里面取出任务 然后一个一个放入线程池运行
        for(int i{0}; i < cap; i++) { //1.构造cap个线程
            // 2.每个线程要做的事情是lambda
            auto lamdba = [&]() {
                while(1) {
                    task tk = task_que.pop();
                    if(!tk) break;
                    tk();
                }
            };
            // 3.启动一个线程
            std::thread t(lamdba);
            // 4.放入这个线程池中 重复for步
            work_thread.emplace_back(std::move(t));
        }
    }
    ~ThreadPool() {
        task_que.shutdown();
        for(int i{0}; i < work_thread.size(); i++) {
            if(work_thread[i].joinable()) {
                work_thread[i].join();
            }
        }
    }
};

int main() {
    int cap{2};
    ThreadPool p(2);
    int nums{10};
    std::mutex cout_mtx;
    for(int i{0}; i < nums; i++) {
        auto lambda = [i,&cout_mtx](){
            std::unique_lock<std::mutex> lock(cout_mtx);
            std::cout<<"This is "<<i<<" thread"<<std::endl;
        };
        p.submit(lambda);
    }
    std::unique_lock<std::mutex> lock(cout_mtx);
    std::cout<<"main is ok"<<std::endl;
}