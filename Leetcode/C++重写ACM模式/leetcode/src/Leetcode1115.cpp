// 给你一个类：

// 两个不同的线程将会共用一个 FooBar 实例：

// 线程 A 将会调用 foo() 方法，而
// 线程 B 将会调用 bar() 方法
// 请设计修改程序，以确保 "foobar" 被输出 n 次。


// 示例 1：

// 输入：n = 1
// 输出："foobar"
// 解释：这里有两个线程被异步启动。其中一个调用 foo() 方法, 另一个调用 bar() 方法，"foobar" 将被输出一次。

// 先不用类看看 先直接写两个线程

#include <iostream>
#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <thread>

using namespace std;

mutex mtx;
condition_variable cv;
int flag{0};

void Print_Foo(int count) {
    while(count--) {
        unique_lock<mutex> lock(mtx); //尝试获得锁
        cv.wait(lock, [](){ return flag == 1; });
        // cout<<"Print_Foo is running!" <<endl;
        cout<<"foo";
        flag = 2;
        cv.notify_all();
    }
}

void Print_Bar(int count) {
    while(count--) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){ return flag == 2; });
        // cout<<"Print_Bar is running!" <<endl;
        cout<<"bar ";
        flag = 0;
        cv.notify_all();
    }
}

int main() {
    int count{5};

    thread t1(&Print_Foo, count);
    thread t2(&Print_Bar, count);

    {
        while(count --) {
            unique_lock<mutex> lock(mtx);
            flag = 1;
            // cout<<"First function is main."<<endl;
            cv.notify_all();
            cv.wait(lock, [](){ return flag == 0; });
        }
    }

    t1.join(); //想当于打了一个阻塞点在这里 告诉main说 在这里等t1执行完 可以理解成同步原语。
    t2.join();

}