#include "StreamingCycleBuffer.h"
#include <iostream>

// 构造函数
template <typename T>
StreamingCycleBuffer<T>::StreamingCycleBuffer(size_t capacity, std::chrono::milliseconds interval)
    : buffer(capacity), head(0), tail(0), count(0), cap(capacity), interval(interval), running(false) {
    // 初始化缓冲区容量，并设置 head、tail、count 为 0
}

// 析构函数
template <typename T>
StreamingCycleBuffer<T>::~StreamingCycleBuffer() {
    stop(); // 停止定时器线程
}

// 向缓冲区尾部添加一个元素（线程安全）
template <typename T>
void StreamingCycleBuffer<T>::push(const T& item) {
    std::unique_lock<std::mutex> lock(mtx); // 加锁

    // 如果缓冲区已满，等待直到有空间
    not_full_cv.wait(lock, [this]() { return !is_full(); });

    buffer[tail] = item;       // 将元素放入尾部位置
    tail = (tail + 1) % cap;   // 更新尾部位置，使用模运算实现循环
    ++count;                   // 增加元素计数

    not_empty_cv.notify_one(); // 通知等待的消费者线程
}

// 启动定时器线程，定期计算平均值
template <typename T>
void StreamingCycleBuffer<T>::start() {
    if (running) return; // 如果已经在运行，直接返回
    running = true;      // 设置运行标志位

    // 启动定时器线程
    timer_thread = std::thread([this]() {
        while (running) {
            std::this_thread::sleep_for(interval); // 等待指定的时间间隔
            calculate_average();                   // 计算平均值
        }
    });
}

// 停止定时器线程
template <typename T>
void StreamingCycleBuffer<T>::stop() {
    if (!running) return; // 如果已经停止，直接返回
    running = false;      // 设置运行标志位为 false

    if (timer_thread.joinable()) {
        timer_thread.join(); // 等待定时器线程结束
    }
}

// 计算缓冲区中数据的平均值
template <typename T>
void StreamingCycleBuffer<T>::calculate_average() {
    std::unique_lock<std::mutex> lock(mtx); // 加锁

    if (count == 0) {
        std::cout << "Buffer is empty, no data to calculate average." << std::endl;
        return;
    }

    T sum = 0;
    size_t current_count = count;
    size_t index = head;

    // 遍历缓冲区，计算总和
    for (size_t i = 0; i < current_count; ++i) {
        sum += buffer[index];
        index = (index + 1) % cap;
    }

    double average = static_cast<double>(sum) / current_count; // 计算平均值
    std::cout << "Average: " << average << " (based on " << current_count << " items)" << std::endl;
}

// 显式实例化模板类，以便在链接时生成代码
template class StreamingCycleBuffer<int>;    // 实例化 int 类型的缓冲区
template class StreamingCycleBuffer<float>;  // 实例化 float 类型的缓冲区
template class StreamingCycleBuffer<double>; // 实例化 double 类型的缓冲区