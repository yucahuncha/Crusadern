#include <iostream>
#include <string>
#include <sstream>
#include<windows.h>
#include "TCP.h"
#include "MYSQLTCP.h"
int main() {
    init_Socket();					//��socket����
    SOCKET serfd = createServerSocket();

    int num = 1;

    while (true)
    {

        std::cout << "Wait SignUP Client Conncnt......     NO."<< num << std::endl;
        num++;
        //����пͻ����������ӣ���ô
        listen(serfd, 10);
        SOCKET clifd =	accept(serfd, NULL, NULL);

        if (INVALID_SOCKET == clifd)
        {
            err("accept");
        }

        char buf[BUFSIZ];
        memset(buf, 0, sizeof(buf));

        //��������
        if (0 < recv(clifd, buf, BUFSIZ, 0))
        {
            std::cout << "RECV:" << buf << std::endl;
        }

        std::string input = buf;                                    //��һ���ַ����ֳ��������Կո����
        std::string str1;
        int str2;
        std::istringstream iss(input);
        iss >> str1 >> str2;

        memset(buf, 0, sizeof(buf));                //���buf�������

        /*Sign UP����
        char source[13] = "ע��ɹ�";
        char error[13] = "ע��ʧ��";
        Login_aaa stu = {str1,str2};

        if (MYSQLTCP::GetInstance()->signup(stu))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
        }*/


        //Sign IN����
        char source[13] = "��¼�ɹ�";
        char error[13] = "��¼ʧ��";

        if (MYSQLTCP::GetInstance()->signin(str1,str2))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
        }


        //������Ϣ
        if (SOCKET_ERROR == send(clifd, buf, strlen(buf), 0))
        {
            err("SEND");
        };
        memset(buf, 0, sizeof(buf));

        //�ر��������»ص��ȴ����ӽ׶�
        closesocket(clifd);
    }

    closesocket(serfd); //�ر�socket����
    close_Socket();
}
