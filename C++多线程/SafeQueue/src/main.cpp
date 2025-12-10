#include "SafeQueue.h"
#include <thread>
#include <chrono>

// 创三个线程 两个加 一个读

int main() {
    SafeQueue s;
    std::mutex cout_mtx;
    auto add1 = [&](int num1){
        std::this_thread::sleep_for(std::chrono::seconds(1)); //如果没有这个休眠 那么所有线程执行顺序都是随机的 多执行几次main就可以验证了。
        s.push_nums(num1);
        std::unique_lock<std::mutex> lock1(cout_mtx);
        std::cout<<"add1 add num. the num is: "<<num1<<std::endl;
    };
    auto add2 = [&](int num2){
        s.push_nums(num2);
        std::unique_lock<std::mutex> lock2(cout_mtx);
        std::cout<<"add1 add num. the num is: "<<num2<<std::endl;
    };
    auto get = [&](){
        // while(s.empty() == false) { 不可以这么写 因为一开始队列就是空的！ 这样子写直接就让消费者退出线程了。 所以只能死循环 然后让队列内部的标志位来结束消费者
        while(1) {
            int num = s.pop();
            if(num == -1) break;
            std::unique_lock<std::mutex> lock3(cout_mtx);
            std::cout<<"get num. the num is: "<<num<<std::endl;
        }
    };

    std::thread t1(add1,1);
    std::thread t2(add2,2);
    std::thread t3(get);

    t1.join();
    t2.join();
    // main跑到这里的时候 t1和t2已经退出了
    s.notify();
    t3.join();
    std::cout<<"main is ok"<<std::endl;
}