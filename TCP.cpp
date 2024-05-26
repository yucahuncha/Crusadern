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

//子线程函数部分
void threadFunction(SOCKET clifd) {
    char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));

    //接收数据
    if (0 < recv(clifd, buf, BUFSIZ, 0))
    {
        std::cout << "RECV:" << buf <<std::endl;
    }

    std::string input = buf;
    //将一个字符串分成两个，以空格隔开
    int SUM;
    std::string str1;
    int str2;

    std::istringstream iss(input);
    iss >> SUM >>str1>>str2;
    //NUM=1：登录模块    NUM = 2:注册模块
    memset(buf, 0, sizeof(buf));                //清空buf里的数据


    char source[13] = "注册成功";
    char error[13] = "注册失败";

    if (SUM == 1)
    {
        Login_aaa stu = {str1,str2};

        if (MYSQLTCP::GetInstance()->signup(stu))
        {
            strcpy(buf, source);
        }
        else {
            strcpy(buf, error);
        }
    }
    else if(SUM == 2)
    {
        if (MYSQLTCP::GetInstance()->signin(str1,str2))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
        }
    }

    //发送消息
    if (SOCKET_ERROR == send(clifd, buf, strlen(buf), 0))
    {
        err("SEND");
    };
    memset(buf, 0, sizeof(buf));

    //关闭链接重新回到等待连接阶段
    closesocket(clifd);
}

