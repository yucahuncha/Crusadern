//
// Created by 橘子酱 on 2024/5/20.
//
#include<WinSock2.h>							//Windows网络库头文件
#pragma comment(lib,"ws2_32.lib")	//库文件
#define err(errMsg) std::cout << "[line:"<< __LINE__ <<"]" <<errMsg <<" failed code:" << WSAGetLastError()<<std::endl;
//定义报错宏函数      LINE获取行数，errmsg获取报错位置
#include<iostream>
#define PORT 10000//[0,65535    0~1024 是保留端口]
#include <thread>
#include "MYSQLTCP.h"
#include <sstream>

//打开网络库
bool init_Socket();
//关闭网络库
bool close_Socket();

//创建服务器socket
SOCKET createServerSocket();

//子线程执行的部分
void threadFunction(SOCKET clifd);
