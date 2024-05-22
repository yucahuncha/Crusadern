cmake_minimum_required(VERSION 3.25)
project(Linux_Crusadern)

set(CMAKE_CXX_STANDARD 17)

# 显式设置MySQL头文件和库文件的路径
include_directories(/usr/include/mysql)
link_directories(/usr/lib)

# 添加可执行文件
add_executable(Linux_Crusadern main.cpp
        MysqlTCP.cpp
        MysqlTCP.h
        TCP.cpp
        TCP.h)

# 链接MySQL客户端库
target_link_libraries(Linux_Crusadern mysqlclient)
