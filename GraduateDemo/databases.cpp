#include "databases.h"

QSqlDatabase m_DB;

//初始化数据库
void initDatabases()
{
    m_DB = QSqlDatabase::addDatabase("QMYSQL"); //加载驱动
    m_DB.setHostName("112.74.45.81");//数据库地址
    m_DB.setDatabaseName("GraduateData"); //数据库名字
    m_DB.setUserName("root"); //用户名
    m_DB.setPassword("Root@123"); //密码
}

