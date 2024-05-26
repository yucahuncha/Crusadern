#include <iostream>
#include <string>
#include <sstream>
#include "TCP.h"
#include "MYSQLTCP.h"
int main() {
    init_Socket();					//打开socket连接
    SOCKET serfd = createServerSocket();

    int num = 1;

    while (true) {

        std::cout << "Wait SignUP Client Conncnt......     NO." << num << std::endl;
        num++;
        //如果有客户端请求连接，那么
        listen(serfd, 10);
        SOCKET clifd = accept(serfd, NULL, NULL);

        if (INVALID_SOCKET == clifd) {
            err("accept");
        }
        std::thread t(threadFunction,clifd);            //每当有一个连接就创建一个子线程
        t.detach();                                                              //设置线程分离，主线程不会阻塞
    }
    closesocket(serfd); //关闭socket连接
    close_Socket();
}
