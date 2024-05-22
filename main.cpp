#include <iostream>
#include "MysqlTCP.h"
#include "TCP.h"
int main() {

    // 1.创建监听的套接字
    int fd = socket(AF_INET, SOCK_STREAM,0);
    if (fd == -1)//判断是否成功
    {
        ERROR("socket");
        exit(-1);
        /* code */
    }

    //绑定本地的IP端口
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;             //IP地址协议
    saddr.sin_port = htons(10000);           //端口
    saddr.sin_addr.s_addr = INADDR_ANY;     //绑定任意IP地址   = 0.0.0.0
    int ret = bind(fd, (struct sockaddr*)&saddr,sizeof(saddr));
    if (ret == -1)
    {
        ERROR("bind");
        std::cout<<"bind"<<"-1";
        /* code */
        return -1;
    }
    int num = 1;
    while (true)
    {
        //设置监听
        ret = listen(fd,128);
        if (ret == -1)
        {
            ERROR("listen");
            /* code */
        }

        //设置阻塞，等待连接
        std::cout << "Wait SignUP Client Conncnt......     NO."<< num << std::endl;
        num++;
        struct sockaddr_in caddr;
        int addrlen = sizeof(caddr);
        int cfd = accept(fd,NULL,NULL);
        if (cfd == -1)
        {
            ERROR("accept");
            return -1;
        }



        char buf[BUFSIZ];
        memset(buf, 0, sizeof(buf));

        //接收数据
        if (0 < recv(cfd, buf, BUFSIZ, 0))
        {
            std::cout << "RECV:" << buf << std::endl;
        }
        std::string input = buf;                                    //将一个字符串分成两个，以空格隔开
        std::string str1;
        int str2;
        std::istringstream iss(input);
        iss >> str1 >> str2;


        char source[13] = "登录成功";
        char error[13] = "登录失败";

        if (MysqlTCP::GetInstance()->signin(str1,str2))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
        }

            //发送数据
        send(cfd,buf,strlen(buf)+1,0);

        //关闭连接
        close(cfd);
    }
    close(fd);
    return 0;
}
