cmake_minimum_required(VERSION 3.27)
project(Crusadern)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)

# 收集源文件
file(GLOB SRC_FILES
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.c"
        "${PROJECT_SOURCE_DIR}/*.cc"
)

# 设置包含目录
include_directories(${PROJECT_SOURCE_DIR}/Mysql_Connect/)

# 设置库目录
set(DLL_DIR "D:/CLIONE/Crusadern/Mysql_Connect/lib")
link_directories(${DLL_DIR})

# 添加可执行文件
add_executable(Crusadern ${SRC_FILES}
        TCP.cpp
        TCP.h
        MYSQLTCP.cpp
        MYSQLTCP.h)

# 链接库
target_link_libraries(Crusadern libmysql.lib ws2_32.lib)
