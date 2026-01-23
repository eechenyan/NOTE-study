// 使用c++20复现1114的go多线程题目 太爆炸了
// 这个代码有很多问题 其中一个就是线程其实并灭有关闭 它还在一直死循环 这个在c++里面需要手动关闭的...
// 还有就是建议学习mutex实现方式 

#include <iostream>
#include <vector>
#include <semaphore>
#include <thread>

using namespace std;

class Solution {
private:
    counting_semaphore<1> sem1;
    counting_semaphore<1> sem2;
    counting_semaphore<1> sem3;
    counting_semaphore<1> is_ok;
public:
    Solution() :sem1(0), sem2(0), sem3(0), is_ok(0) {}

    void first() {
        while(1) {
            sem1.acquire();
            cout<<"first ";
            is_ok.release();
        }
    }

    void second() {
        while(1) {
            sem2.acquire();
            cout<<"second ";
            is_ok.release();
        }
    }

    void third() {
        while(1) {
            sem3.acquire();
            cout<<"third ";
            is_ok.release();
        }
    }

    void Set_Sem1_release() {
        sem1.release();
    }

    void Set_Sem2_release() {
        sem2.release();
    }

    void Set_Sem3_release() {
        sem3.release();
    }

    void Set_Is_Ok_acquire() {
        is_ok.acquire();
    }
    void run() {
        thread t1(&first,this);
        thread t2(&second,this);
        thread t3(&third,this);

        t1.detach();
        t2.detach();
        t3.detach();
    }
};

int main() {
    Solution s;
    vector<int> nums{1,2,3,3,2,1};
    s.run();
    for(const int& i : nums) {
        if(i == 1) {
            s.Set_Sem1_release();
        } else if(i == 2) {
            s.Set_Sem2_release();
        } else {
            s.Set_Sem3_release();
        }
        s.Set_Is_Ok_acquire();
    }
}