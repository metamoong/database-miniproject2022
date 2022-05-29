#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void showHistory(int id) {
	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT BC.BCONFID,C.CUSTNAME,C.TEL, BC.PRODNAME, BC.QUANTITY, BC.DATE FROM BUYCONFIRMATION AS BC, CUSTOMER AS C WHERE BC.CUSTTEL = C.TEL AND STOID = %d", id);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT store_id, floor;
		SQLCHAR store_name[20], tel[20];


		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &floor, 5, NULL);
		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &store_id, 5, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, store_name, 20, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, tel, 20, NULL);


		printf("===========%d번 건물에 입점한 상점 목록입니다===========\n", building_num);
		printf("%-5s %-5s %-20s %-20s\n", "FLOOR", "ID", "NAME", "TEL");
		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-5d %-20s %-20s\n", floor, store_id, store_name, tel);
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

}