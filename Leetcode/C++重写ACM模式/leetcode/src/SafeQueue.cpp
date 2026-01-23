// 在复习一个线程安全的队列
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <windows.h>  // 需包含这个头文件

class SafeQueue {
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool is_running;
    std::queue<int> que;
public:
    SafeQueue(): is_running(true) {};
    int push(int& num) {
        std::unique_lock<std::mutex> lock(mtx);
        if(is_running == false) return -1;
        que.push(num);
        cv.notify_one();
        return 0;
    }
    int pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return que.empty() == false || this->is_running == false;}); //队列不为空的情况下取数据 和 关闭队列的也要放下走 因为关闭了 不往下走会一直阻塞在这里
        if(is_running == false && que.empty() == true) return -1;
        int num = que.front();
        que.pop();
        return num;
    }
    void notify() {
        std::unique_lock<std::mutex> lock(mtx);
        is_running = false; //关闭队列
        cv.notify_all(); //通知所有阻塞的消费者
    }
    size_t size() {
        std::unique_lock<std::mutex> lock(mtx);
        return que.size();
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SafeQueue s;
    std::mutex cout_mtx;
    std::thread t1([&]() {
        // 生产者
        int num = 1;
        int is_vaild = s.push(num);
        if(is_vaild == 0) {
            std::unique_lock<std::mutex> lock1(cout_mtx);
            std::cout<<"生产者1已完成生产:"<<num<<std::endl;
        } else {
            std::unique_lock<std::mutex> lock1(cout_mtx);
            std::cout<<"队列没有工作，生产者1没有生产"<<std::endl;
        }
    });
    std::thread t2([&](){
        // 生产者
        int num = 2;
        int is_vaild = s.push(num);
        if(is_vaild == 0) {
            std::unique_lock<std::mutex> lock2(cout_mtx);
            std::cout<<"生产者2已完成生产:"<<num<<std::endl;
        } else {
            std::unique_lock<std::mutex> lock2(cout_mtx);
            std::cout<<"队列没有工作，生产者2没有生产"<<std::endl;
        }
    });
    std::thread t3([&](){
        // 消费者
        while(1) {
            int num = s.pop();
            if(num == -1) {
                std::unique_lock<std::mutex> lock3(cout_mtx);
                std::cout<<"队列已关闭并且空"<<std::endl;
                break;
            }
            else {
                std::unique_lock<std::mutex> lock3(cout_mtx);
                std::cout<<"消费者拿到一个数据:"<<num<<std::endl;
            }
        }
    });

    t1.join();
    t2.join();
    s.notify();
    t3.join();

    std::cout<<"主线程退出"<<std::endl;
}