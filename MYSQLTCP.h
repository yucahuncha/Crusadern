#pragma once
#include<iostream>
#include"mysql.h"
#include<vector>
#include <string>
using namespace std;

struct  Login_aaa
{
    string Login_ID;
    int Login_pw;
};

class MYSQLTCP
{
    MYSQLTCP();
    ~MYSQLTCP();

public:
    static MYSQLTCP* GetInstance()									//单例函数
    {
        static MYSQLTCP	TcpMysql;
        return &TcpMysql;
    }

public:
    bool signup(Login_aaa& t);                                  //注册部分
    bool signin(string Login_ID, int Login_pw);      //登录部分

private:
    MYSQL* connect = mysql_init(NULL);
    const char* host = "localhost";
    const char* name = "root";
    const char* pw = "root";
    const char* database_name = "login";
    const int port = 3306;
};

