#include <iostream>
#include <string>
#include <sstream>
#include "TCP.h"
#include "MYSQLTCP.h"
int main() {
    init_Socket();					//��socket����
    SOCKET serfd = createServerSocket();

    int num = 1;

    while (true) {

        std::cout << "Wait SignUP Client Conncnt......     NO." << num << std::endl;
        num++;
        //����пͻ����������ӣ���ô
        listen(serfd, 10);
        SOCKET clifd = accept(serfd, NULL, NULL);

        if (INVALID_SOCKET == clifd) {
            err("accept");
        }
        std::thread t(threadFunction,clifd);            //ÿ����һ�����Ӿʹ���һ�����߳�
        t.detach();                                                              //�����̷߳��룬���̲߳�������
    }
    closesocket(serfd); //�ر�socket����
    close_Socket();
}
