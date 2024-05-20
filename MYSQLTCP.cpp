#include "MYSQLTCP.h"


MYSQLTCP::MYSQLTCP()
{
    mysql_options(connect, MYSQL_SET_CHARSET_NAME, "GBK");
    if (!mysql_real_connect(connect, host, name, pw, database_name, port, NULL, 0))
    {
        cout << "fialid to connect:ERROR:" << mysql_error(connect);
        exit(1);
    }
}

MYSQLTCP::~MYSQLTCP()
{

    mysql_close(connect);
}

bool MYSQLTCP::ZhuChe(Login_aaa& stu)
{
    string sql = "INSERT INTO Login_1 VALUES ('" + stu.Login_ID + "'," + to_string(stu.Login_pw) + ");";
    const char* str = sql.c_str();
    if (mysql_query(connect, str))
    {
        cout << "falied zhuche :ERROR:" << mysql_error(connect);
        exit(1);
    }
    else
    {
        cout << "注册成功" << endl;
    }
    return false;
}

bool MYSQLTCP::DengLu(string Login_ID, int Login_pw)
{
    string sql = "SELECT * FROM Login_1 WHERE Login_id = '" + Login_ID + "';";
    const char* str = sql.c_str();
    if (mysql_query(connect, str))																							//判断是否出错，并打印错误信息
    {
        fprintf(stderr, "failed to select data: Error:%s\n", mysql_error(connect));
        return false;
    }
    MYSQL_RES* res = mysql_store_result(connect);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    Login_aaa stu;
    if (row != NULL)                    //判断是否为空集
    {
        stu.Login_ID = row[0];
        stu.Login_pw = atoi(row[1]);
    }
    else
    {
        return false;
    }
    if (stu.Login_pw == Login_pw)                           //与输入的账号密码比对
    {
        return true;
    }
    else
    {
        return false;
    }
}
