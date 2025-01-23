#include <iostream>
#include <thread>

bool ready = false;
int data = 0;

void producer() {
    data = 42;       // 写操作
    ready = true;    // 写操作
}

void consumer() {
    while (!ready);  // 读操作
    std::cout << "Data: " << data << std::endl; // 读操作
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}