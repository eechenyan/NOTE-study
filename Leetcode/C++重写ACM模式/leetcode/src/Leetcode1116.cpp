// 输入：n = 2
// 输出："0102"
// 解释：三条线程异步执行，其中一个调用 zero()，另一个线程调用 even()，最后一个线程调用odd()。正确的输出为 "0102"。

// 输入：n = 5
// 输出："0102030405"


// 
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;


// 启动三个线程 和 一个主线程 主线程负责分配哪一个线程工作 每次子线程工作完回到主线程

mutex mtx;
condition_variable cv;
int flag_zero{-1};
int print_number{1};

void PrintZero(int count) {
    for(int i{1}; i <= count; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){ return flag_zero == 1; });
        cout<<"0";
        flag_zero = 0;
        cv.notify_all();
        // 出去unique_lock作用域自动释放锁
    }
}
void PrintEven(int count) {
    // while(1) {
    //while(1)会出现线程卡死 因为有一个线程永远不会退出 因为负责击鼓传花的主线程那边已经结束了
    for(int i{1}; i <= count; i = i + 2) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){
            if(print_number % 2 != 0 && flag_zero == 0) {
                //奇数
                return true;
            } 
            else {
                return false;
            }
        });
        cout<<print_number;
        print_number++;
        flag_zero = -1;
        cv.notify_all();
        if(print_number > count) break;
    }
}

void PrintOdd(int count) {
    // while(1) {
    for(int i{2}; i <= count; i = i + 2) { //使用这个明确确定打印次数
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){
            if(print_number % 2 == 0 && flag_zero == 0) {
                //偶数
                return true;
            } 
            else {
                return false;
            }
        });
        cout<<print_number;
        print_number++;
        flag_zero = -1;
        cv.notify_all();
        if(print_number > count) break;
    }
}

int main() {
    // main作击鼓传花的作用
    int count{5};

    thread t1(&PrintZero,count);
    thread t2(&PrintEven,count);
    thread t3(&PrintOdd,count);

    for(int i{0}; i < count; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[](){ return flag_zero == -1; });
        flag_zero = 1;
        cv.notify_all();
    }

    t1.join();
    t2.join();
    t3.join();

    cout<<endl;
}


// select
//     cl.class_name,
//     cl.class_id,
//     stu.student_id
// from
//     students as stu
// inner join course_selections as cs
// on stu.student_id = cs.student_id
// inner join class as cl
// on cl.class_id = stu.class_id
// group by class_name

