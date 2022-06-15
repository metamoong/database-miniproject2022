#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void showCustomerInfo() {
	static SQLCHAR query[100];
	SQLHSTMT hStmt;

	char tel[21];


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		printf("=========== 고객의 정보를 검색하기 위한 메뉴입니다 ===========\n");
		printf("검색하고자 하는 고객의 전화번호를 입력하세요 : ");
		scanf("%s", tel);
		getchar();


		sprintf((char*)query, "SELECT * FROM CUSTOMER WHERE TEL = '%s'", tel);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLCHAR custname[21], tel[21],address[21],buyer[21];
		SQLLEN lenor;

		SQLBindCol(hStmt, 1, SQL_C_CHAR, tel, 20, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, custname, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, address, 20, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, buyer, 20, &lenor);
	


		printf("\n");
		printf("==========검색한 고객의 정보입니다.==========\n");

		printf("%-20s %-20s %-20s %-20s\n", "TEL", "NAME", "ADDRESS", "BUYER");


		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-20s %-20s %-20s ", tel,custname,address);
			if (lenor == SQL_NULL_DATA) {
				printf("%-20s\n","none");
			}
			else {
				printf("%-20s\n", buyer);
			}
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}