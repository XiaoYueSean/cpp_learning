#include "logger.h"
#include "spdlog/sinks/basic_file_sink.h"

std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::init(const std::string& name, const std::string& filename) {
    logger = spdlog::basic_logger_mt(name, filename);
    logger->set_level(spdlog::level::debug);
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%n] %v");
}

std::shared_ptr<spdlog::logger> Logger::get_logger() {
    return logger;
}