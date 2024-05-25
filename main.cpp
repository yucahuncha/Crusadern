#include <iostream>
#include <pthread.h>
#include "MysqlTCP.h"
#include "TCP.h"
#include <time.h>

void * thread_function(void *arg) {                      //���߳�ִ�к���
    int cfd = *(int*)arg;
    char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));

    //��������
    if (0 < recv(cfd, buf, BUFSIZ, 0))
    {
        time_t timep;
        time(&timep);               //���㵱ǰʱ��
        std::cout << "RECV:" << buf << "      Time:"<< ctime(&timep)<< std::endl;
    }
    std::string input = buf;                                    //��һ���ַ����ֳ��������Կո����
    std::string str1;
    int str2;
    std::istringstream iss(input);
    iss >> str1 >> str2;


    char source[13] = "yes";
    char error[13] = "no";

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
    pthread_exit(NULL);
}


int main() {

    pthread_t thread;      //�߳�

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
        //���ӽ����ɹ�����ӡ�ͻ��˵�IP�Ͷ˿���Ϣ
        char ip[32];
        std::cout<<"�ͻ��˵�IP:"<< inet_ntop(AF_INET,&caddr.sin_addr.s_addr, ip, sizeof(ip)) <<"�˿�:"<< ntohs(caddr.sin_port)<<std::endl;
        if (cfd == -1)
        {
            ERROR("accept");
            return -1;
        }

        //�����̺߳���pthread_create,
        if (pthread_create(&thread, NULL, thread_function, (void*)&cfd) != 0) {
            printf("Error creating thread.\n");
            return 1;
        }
    }
    close(fd);
    return 0;
}
