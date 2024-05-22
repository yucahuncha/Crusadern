#include <iostream>
#include "MysqlTCP.h"
#include "TCP.h"
int main() {

    // 1.�����������׽���
    int fd = socket(AF_INET, SOCK_STREAM,0);
    if (fd == -1)//�ж��Ƿ�ɹ�
    {
        ERROR("socket");
        exit(-1);
        /* code */
    }

    //�󶨱��ص�IP�˿�
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;             //IP��ַЭ��
    saddr.sin_port = htons(10000);           //�˿�
    saddr.sin_addr.s_addr = INADDR_ANY;     //������IP��ַ   = 0.0.0.0
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
        //���ü���
        ret = listen(fd,128);
        if (ret == -1)
        {
            ERROR("listen");
            /* code */
        }

        //�����������ȴ�����
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

        //��������
        if (0 < recv(cfd, buf, BUFSIZ, 0))
        {
            std::cout << "RECV:" << buf << std::endl;
        }
        std::string input = buf;                                    //��һ���ַ����ֳ��������Կո����
        std::string str1;
        int str2;
        std::istringstream iss(input);
        iss >> str1 >> str2;


        char source[13] = "��¼�ɹ�";
        char error[13] = "��¼ʧ��";

        if (MysqlTCP::GetInstance()->signin(str1,str2))
        {
            strcpy(buf, source);
        }
        else
        {
            strcpy(buf, error);
        }

            //��������
        send(cfd,buf,strlen(buf)+1,0);

        //�ر�����
        close(cfd);
    }
    close(fd);
    return 0;
}
