#ifndef STREAMINGCYCLEBUFFER_H
#define STREAMINGCYCLEBUFFER_H

#include <vector>              // 使用 std::vector 作为底层存储
#include <mutex>               // 用于线程同步的互斥锁
#include <condition_variable>  // 用于线程间通信的条件变量
#include <chrono>              // 用于时间操作
#include <thread>              // 用于定时器线程
#include <atomic>              // 用于线程安全的标志位
#include <stdexcept>           // 用于抛出异常

template <typename T>
class StreamingCycleBuffer {
public:
    // 构造函数，初始化缓冲区容量和计算间隔
    explicit StreamingCycleBuffer(size_t capacity, std::chrono::milliseconds interval);

    // 析构函数，停止定时器线程
    ~StreamingCycleBuffer();

    // 向缓冲区尾部添加一个元素（线程安全）
    void push(const T& item);

    // 启动定时器线程，定期计算平均值
    void start();

    // 停止定时器线程
    void stop();

private:
    // 计算缓冲区中数据的平均值
    void calculate_average();

    std::vector<T> buffer;      // 底层存储容器
    size_t head;                // 指向缓冲区头部的位置
    size_t tail;                // 指向缓冲区尾部的位置
    size_t count;               // 当前缓冲区中的元素数量
    size_t cap;                 // 缓冲区的总容量

    mutable std::mutex mtx;     // 互斥锁，用于保护共享资源
    std::condition_variable not_full_cv;  // 条件变量，用于等待缓冲区不满
    std::condition_variable not_empty_cv; // 条件变量，用于等待缓冲区不空

    std::chrono::milliseconds interval; // 计算平均值的时间间隔
    std::thread timer_thread;           // 定时器线程
    std::atomic<bool> running;          // 标志位，表示定时器是否运行
};

#endif // STREAMINGCYCLEBUFFER_H