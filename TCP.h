//
// Created by ���ӽ� on 2024/5/20.
//
#include<WinSock2.h>							//Windows�����ͷ�ļ�
#pragma comment(lib,"ws2_32.lib")	//���ļ�
#define err(errMsg) std::cout << "[line:"<< __LINE__ <<"]" <<errMsg <<" failed code:" << WSAGetLastError()<<std::endl;
//���屨��꺯��      LINE��ȡ������errmsg��ȡ����λ��
#include<iostream>
#define PORT 10000//[0,65535    0~1024 �Ǳ����˿�]
#include <thread>
#include "MYSQLTCP.h"
#include <sstream>

//�������
bool init_Socket();
//�ر������
bool close_Socket();

//����������socket
SOCKET createServerSocket();

//���߳�ִ�еĲ���
void threadFunction(SOCKET clifd);
