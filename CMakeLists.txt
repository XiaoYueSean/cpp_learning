# 1. 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 项目描述，项目版本，编程语言，项目描述
project(VHOrin VERSION 3.0.0 LANGUAGES C CXX)
set(PROJECT_DESCRIPTION "该程序是自学cpp用的工程")
set(PROJECT_DEVELOPER "xx")  # 替换为你的名字或团队名称

# 3. 设置 C 和 C++ 标准
set(CMAKE_C_STANDARD 99)                # 设置 C 标准为 C99
set(CMAKE_C_STANDARD_REQUIRED ON)       # 强制要求 C99
set(CMAKE_CXX_STANDARD 17)              # 设置 C++ 标准为 C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # 强制要求 C++14

# 4. 输出项目信息（可选，用于调试）
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "Project Description: ${PROJECT_DESCRIPTION}")
message(STATUS "Project Developer: ${PROJECT_DEVELOPER}")

# 5. 设置默认构建类型（如果没有指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# 6. 配置 Debug 和 Release 模式的编译选项
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -g")          # C 的 Debug 选项
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG") # C 的 Release 选项
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")     # C++ 的 Debug 选项
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG") # C++ 的 Release 选项

# 7. 添加源文件（包括 C 和 C++ 文件）
set(SOURCES

main.cpp
utils/logger.cpp

)

# 8. 添加可执行文件目标
add_executable(VHOrin_main ${SOURCES})

# 9. 添加头文件目录
target_include_directories(VHOrin_main PUBLIC include)

# 10. 添加依赖库（例如链接一个库）
find_package(Threads REQUIRED)  # 查找线程库
find_package(spdlog REQUIRED) # 查找日志库

target_link_libraries(VHOrin_main PRIVATE Threads::Threads spdlog::spdlog)  # 链接线程库