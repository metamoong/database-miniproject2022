#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void deleteStore() {


	static SQLCHAR query[100];
	SQLHSTMT hStmt;

	char stoname[21];

	printf("===========폐업한 상점을 제거하는 메뉴입니다=========\n");
	printf("데이터에서 삭제할 상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);



	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "DELETE FROM STORE WHERE STONAME = '%s'", stoname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("삭제가 완료되었습니다.\n");

	}



}