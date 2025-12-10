#include "ThreadPool.h"
#include "SafeQueue.h"
#include <chrono>     // 用于测试时的休眠
#include <mutex>
// 测试任务：打印任务ID和执行线程ID，模拟耗时操作

std::mutex cout_mtx; //输出锁

void test_task(int task_id) {
    // 获取当前线程ID（注意：std::thread::id 可直接输出）
    std::thread::id thread_id = std::this_thread::get_id();
    
    // 打印任务开始信息
    {
        std::unique_lock<std::mutex> lock1(cout_mtx);
        std::cout << "Task " << task_id << " started (thread: " << thread_id << ")\n";
    }
    // 模拟任务执行耗时（100ms）
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // 打印任务结束信息
    {
        std::unique_lock<std::mutex> lock2(cout_mtx);
        std::cout << "Task " << task_id << " finished (thread: " << thread_id << ")\n";
    }
}

int main() {
    // 创建一个包含 3 个工作线程的线程池
    ThreadPool pool(3);
    std::cout << "ThreadPool created with 3 workers.\n";

    // 提交 6 个测试任务
    for (int i = 0; i < 6; ++i) {
        // 用 lambda 封装任务，捕获 i 并传递给 test_task
        // 注意：捕获时用 mutable 允许修改拷贝的 i，或通过参数传递（这里用参数更安全）
        // 注意看这里是怎么传递函数的 submit要求的无参无返回值的函数 那么这个使用一个lambda函数包装一个有参函数 参数通过捕获列表获得 这里的这个lambda是无参的() 满足传递的条件
        auto lambda = [i]() { test_task(i); };
        pool.submit(lambda);

    }

    // 等待所有任务执行完（实际项目中可通过“任务计数器”精确控制，这里简化为休眠）
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 足够 5 个任务执行（每个 100ms，2 线程并行）

    std::cout << "Main thread exiting. ThreadPool will shutdown.\n";
    return 0;
} // 主线程结束，线程池析构函数会自动调用，关闭线程池