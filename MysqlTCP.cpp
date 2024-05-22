//
// Created by ���ӽ� on 2024/5/22.
//

#include "MysqlTCP.h"


MysqlTCP::MysqlTCP()
{
    mysql_options(connect, MYSQL_SET_CHARSET_NAME, "GBK");
    if (!mysql_real_connect(connect, host, name, pw, database_name, port, NULL, 0))
    {
        cout << "fialid to connect:ERROR:" << mysql_error(connect);
        exit(1);
    }
}

MysqlTCP::~MysqlTCP()
{

    mysql_close(connect);
}

bool MysqlTCP::signup(Login_aaa& stu)
{
    string sql = "INSERT INTO Login_user VALUES ('" + stu.Login_ID + "'," + to_string(stu.Login_pw) + ");";
    const char* str = sql.c_str();
    if (mysql_query(connect, str))
    {
        cout << "falied zhuche :ERROR:" << mysql_error(connect);
        return false;
    }
    else
    {
        //cout << "ע��ɹ�" << endl;
        return true;
    }
}

bool MysqlTCP::signin(std::string Login_ID, int Login_pw) {
    string sql = "SELECT * FROM Login_user WHERE Login_id = '" + Login_ID + "';";
    const char* str = sql.c_str();
    if (mysql_query(connect, str))																							//�ж��Ƿ��������ӡ������Ϣ
    {
        fprintf(stderr, "failed to select data: Error:%s\n", mysql_error(connect));
        return false;
    }
    MYSQL_RES* res = mysql_store_result(connect);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    Login_aaa stu;
    if (row != NULL)                    //�ж��Ƿ�Ϊ�ռ�
    {
        stu.Login_ID = row[0];
        stu.Login_pw = atoi(row[1]);
        if (stu.Login_pw == Login_pw)                           //��������˺�����ȶ�
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}