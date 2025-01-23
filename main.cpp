#include "logger.h"

void function1() {
    auto logger = Logger::get_logger();
    logger->info("This is a log message from file1.cpp");
}

void function2() {
    auto logger = Logger::get_logger();
    logger->warn("This is a warning message from file2.cpp");
}

int main() {
    Logger::init("global_logger", ".logs/global.log"); // 初始化日志器

    function1();
    function2();

    spdlog::shutdown(); // 关闭日志器
    return 0;
}