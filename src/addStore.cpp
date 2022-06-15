#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void addStore() {

	int id,bui_num,floor;
	char stoname[21];
	char tel[21];

	printf("==========입점할 상점에 대한 정보를 입력해주세요==========\n");

	printf("상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);

	printf("건물 번호를 입력해주세요 :");
	scanf("%d", &bui_num);


	while (1) {
		printf("입점할 층수를 입력해주세요 :");
		scanf("%d", &floor);

		if (floor == 1 || floor == 2 || floor == 3) {
			break;
		}

		printf("층 수는 1/2/3 중 하나의 값으로 입력되어야 합니다.\n");
	}


	getchar();
	printf("상점 연락처를 입력해주세요 : ");
	scanf("%s", tel);


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "INSERT INTO STORE VALUES(%d,'%s','%s',%d)",bui_num,stoname,tel,floor);
		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


		printf("상점 추가가 완료되었습니다.\n");

	}
}