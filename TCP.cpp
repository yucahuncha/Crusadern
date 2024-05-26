//
// Created by ���ӽ� on 2024/5/20.
//

#include "TCP.h"

bool init_Socket()
{
    //wsa windows socket async		windows�첽�׽���
    //parm1�������socket�汾 2.2 2.1 2.0       parm ��������
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
    //1.�����յ�socket
    //parm1:af ��ַЭ���� IPV4 IPV6
    //parm2:type ����Э������ ��ʽ�׽��� ���ݱ�
    //parm3:protocl ʹ�þ����ĳ������Э��

    SOCKET fd  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //AF_INET����IPV4��SOC_STREAM����ʾ��������IPPROTO_TCP��ʾtcpЭ��

    if (fd == INVALID_SOCKET)
    {
        err("socket");
        return INVALID_SOCKET;
    }

    //2.��socket��IP��ַ�Ͷ˿ں�
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;			//�ʹ���socketʱ�ı���һ��
    addr.sin_port = htons(PORT);				//��˴洢��С�˴洢
    addr.sin_addr.S_un.S_addr = ADDR_ANY;					//inet_addr("127.0.0.1");

    if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
    {
        err("bind");
        return false;
    }

    //3.�����绰
    return fd;
}

//���̺߳�������
void threadFunction(SOCKET clifd) {
    char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));

    //��������
    if (0 < recv(clifd, buf, BUFSIZ, 0))
    {
        std::cout << "RECV:" << buf <<std::endl;
    }

    std::string input = buf;
    //��һ���ַ����ֳ��������Կո����
    int SUM;
    std::string str1;
    int str2;

    std::istringstream iss(input);
    iss >> SUM >>str1>>str2;
    //NUM=1����¼ģ��    NUM = 2:ע��ģ��
    memset(buf, 0, sizeof(buf));                //���buf�������


    char source[13] = "ע��ɹ�";
    char error[13] = "ע��ʧ��";

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

    //������Ϣ
    if (SOCKET_ERROR == send(clifd, buf, strlen(buf), 0))
    {
        err("SEND");
    };
    memset(buf, 0, sizeof(buf));

    //�ر��������»ص��ȴ����ӽ׶�
    closesocket(clifd);
}

