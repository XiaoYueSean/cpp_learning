#include <iostream>
#include <thread>
#include <mutex>

int shared_value = 0;

std::mutex mtx;

// thread function
void increment() {
    for (int i = 0; i < 10000; ++i) {
        // 在构造时加锁
        std::lock_guard<std::mutex> lock(mtx);
        ++shared_value;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final value: " << shared_value << std::endl;
    return 0;
}