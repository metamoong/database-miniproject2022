#define _CRT_SECURE_NO_WARNINGS

//Hearder files for the use of SQL
#include<stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>


void start();

// SQL Environment Variables
SQLHENV hEnv = NULL; // 환경설정에 대한 현재값
SQLHDBC hDbc = NULL;// 연결설정에 대한 현재값

bool DBConnect()
{
	SQLRETURN Ret;

	// Allocate the Environment Handle (hEnv)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
	{
		return false;
	}

	// Set attributes of the Environment Handle (hEnv)
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}

	// Allocate the Connection Handle (hDbc)
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
	{
		return false;
	}

	// Connect to the SQL Sever with ODBC name, ID, and PW
	Ret = SQLConnect(hDbc, (SQLCHAR*)"DB01_SERVER", SQL_NTS, (SQLCHAR*)"KIM", SQL_NTS, (SQLCHAR*)"1234", SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		return false;
	}

	return true;
}

void DBDisconnect()
{
	SQLDisconnect(hDbc);					// Disconnect from the SQL Server
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);	// Free the Connection Handle
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);	// Free the Environment Handle
}

int main(int argc, char* argv[])
{
	if (DBConnect() == true) {
		printf("Connection Success!!\n");

		start();
			
		DBDisconnect();
	}
	else {
		printf("Fail to Connect!!\n");
	}
	return 0;
}