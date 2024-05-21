#include <iostream>
#include <string>
#include <sstream>
#include<windows.h>
#include "TCP.h"
#include "MYSQLTCP.h"
int main() {
    init_Socket();					//打开socket连接
    SOCKET serfd = createServerSocket();

    int num = 1;

    while (true)
    {

        std::cout << "Wait SignUP Client Conncnt......     NO."<< num << std::endl;
        num++;
        //如果有客户端请求连接，那么
        listen(serfd, 10);
        SOCKET clifd =	accept(serfd, NULL, NULL);

        if (INVALID_SOCKET == clifd)
        {
            err("accept");
        }

        char buf[BUFSIZ];
        memset(buf, 0, sizeof(buf));

        //接收数据
        if (0 < recv(clifd, buf, BUFSIZ, 0))
        {
            std::cout << "RECV:" << buf << std::endl;
        }

        std::string input = buf;                                    //将一个字符串分成两个，以空格隔开
        std::string str1;
        int str2;
        std::istringstream iss(input);
        iss >> str1 >> str2;

        memset(buf, 0, sizeof(buf));                //清空buf里的数据

        /*Sign UP部分
        char source[13] = "注册成功";
        char error[13] = "注册失败";
        Login_aaa stu = {str1,str2};

        if (MYSQLTCP::GetInstance()->signup(stu))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
        }*/


        //Sign IN部分
        char source[13] = "登录成功";
        char error[13] = "登录失败";

        if (MYSQLTCP::GetInstance()->signin(str1,str2))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
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

    closesocket(serfd); //关闭socket连接
    close_Socket();
}
