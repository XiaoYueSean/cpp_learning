#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"
#include <memory>
#include <string>

class Logger {
public:
    static void init(const std::string& name, const std::string& filename);
    static std::shared_ptr<spdlog::logger> get_logger();

private:
    static std::shared_ptr<spdlog::logger> logger;
};

#endif // LOGGER_H