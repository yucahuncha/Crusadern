#include <iostream>
#include <string>
#include <sstream>
#include "TCP.h"
#include "MYSQLTCP.h"

int main() {
    init_Socket();					//打开socket连接

    SOCKET serfd = createServerSocket();
    while (true)
    {
        std::cout << "wait client connecnt......" << std::endl;
        //如果有客户端请求连接，那么
        listen(serfd, 10);
        SOCKET clifd =	accept(serfd, NULL, NULL);
        if (INVALID_SOCKET == clifd)
        {
            err("accept");
        }


        char buf[BUFSIZ];
        memset(buf, 0, sizeof(buf));

        if (0 < recv(clifd, buf, BUFSIZ, 0))											//接收数据
        {
            std::cout << "recv:" << buf << std::endl;
        }

        std::string input = buf;
        std::string str1;
        int str2;

        std::istringstream iss(input);
        iss >> str1 >> str2;

        std::cout << "String 1: " << str1 << std::endl;
        std::cout << "String 2: " << str2 << std::endl;
        memset(buf, 0, sizeof(buf));
        char source[512] = "登录成功";
        char source2[512] = "ERROR";
        if (MYSQLTCP::GetInstance()->DengLu(str1,str2))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, source2);
        }
        //发送消息
        std::cout << "send>"<<buf<<std::endl;
        if (SOCKET_ERROR == send(clifd, buf, strlen(buf), 0))
        {
            err("SEND");
        };
        memset(buf, 0, sizeof(buf));
        closesocket(clifd);
    }

    closesocket(serfd);


    close_Socket();				//关闭socket连接



}
