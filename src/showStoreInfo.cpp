#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void showStoreInfo(char* store_name_input) {
	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT * FROM STORE WHERE STONAME = '%s'", store_name_input);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT store_id, floor, building_num;
		SQLCHAR store_name[20], tel[20];



		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &store_id, 5, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, store_name, 20, NULL);
		SQLBindCol(hStmt, 2, SQL_C_SSHORT, &building_num, 5, NULL);
		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &floor, 5, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, tel, 20, NULL);



		printf("===========\"%s\" 에 대한 정보 검색 결과입니다 ========== = \n", store_name_input);

		
		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("상점 번호 : %d\n", store_id);
			printf("상점 이름 : %s\n", store_name);
			printf("위치 : %d번 건물 %d 층\n", building_num, floor);
			printf("연락처 : %s\n", tel);
			printf("------------------------\n");
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}