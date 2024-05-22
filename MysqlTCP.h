//
// Created by éÙ×Ó½´ on 2024/5/22.
//
#pragma once
#include <mysql.h>
#include <iostream>
#include<vector>
#include <string>
using namespace std;

struct  Login_aaa
{
    string Login_ID;
    int Login_pw;
};

class MysqlTCP
{
    MysqlTCP();
    ~MysqlTCP();

public:
    static MysqlTCP* GetInstance()									//????????
    {
        static MysqlTCP	TcpMysql;
        return &TcpMysql;
    }

public:
    bool signup(Login_aaa& t);
    bool signin(string Login_ID, int Login_pw);

private:
    MYSQL* connect = mysql_init(NULL);
    const char* host = "localhost";
    const char* name = "root";
    const char* pw = "root";
    const char* database_name = "Login";
    const int port = 3306;
};


