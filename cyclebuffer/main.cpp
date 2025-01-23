#include <iostream>
#include <thread>
#include <random>
#include "StreamingCycleBuffer.h"

int main() {
    StreamingCycleBuffer<int> buffer(100, std::chrono::seconds(1)); // 创建一个容量为 100 的缓冲区，计算间隔为 1 秒
    buffer.start(); // 启动定时器线程

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // 模拟流式数据
    for (int i = 0; i < 1000; ++i) {
        int value = dis(gen); // 生成随机数
        buffer.push(value);   // 将数据推入缓冲区
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 模拟数据流延迟
    }

    buffer.stop(); // 停止定时器线程
    return 0;
}