//
// Created by 橘子酱 on 2024/5/20.
//

#include "TCP.h"

bool init_Socket()
{
    //wsa windows socket async		windows异步套接字
    //parm1：请求的socket版本 2.2 2.1 2.0       parm 传出参数
    WSADATA wsadata;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
    {
        err("WSAStartup");
        return false;
    }
    return true;
}

bool close_Socket()
{
    if (0 != WSACleanup())
    {
        err(WSACleanup);
        return false;
    }
    return true;
}

SOCKET createServerSocket()
{
    //1.创建空的socket
    //parm1:af 地址协议族 IPV4 IPV6
    //parm2:type 传输协议类型 流式套接字 数据报
    //parm3:protocl 使用具体的某个传输协议

    SOCKET fd  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //AF_INET代表IPV4，SOC_STREAM，表示数据流，IPPROTO_TCP表示tcp协议

    if (fd == INVALID_SOCKET)
    {
        err("socket");
        return INVALID_SOCKET;
    }

    //2.给socket绑定IP地址和端口号
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;			//和创建socket时的必须一样
    addr.sin_port = htons(PORT);				//大端存储和小端存储
    addr.sin_addr.S_un.S_addr = ADDR_ANY;					//inet_addr("127.0.0.1");

    if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
    {
        err("bind");
        return false;
    }

    //3.监听电话
    return fd;
}