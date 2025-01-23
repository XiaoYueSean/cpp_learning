#include <iostream>
#include <thread>

int shared_value = 0;

void increment() {
    for (int i = 0; i < 10000000; ++i) {
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