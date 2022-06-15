#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "Windows.h"
#include "sql.h"
#include "sqlext.h"

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void updateStoreInfo() {

	char stoname[21];
	printf("==========상점 이전 시 정보를 수정하는 메뉴입니다. ==========\n");
	printf("상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT * FROM STORE WHERE STONAME = '%s'", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT store_id, floor, building_num;
		SQLCHAR store_name[20], tel[20];

		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &store_id, 5, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, store_name, 20, NULL);
		SQLBindCol(hStmt, 2, SQL_C_SSHORT, &building_num, 5, NULL);
		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &floor, 5, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, tel, 20, NULL);


		printf("==========상점에 대한 정보입니다 ==========\n");


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

	int bui;
	int floor;

	printf("이전한 건물 번호를 입력해주세요 : ");
	scanf("%d", &bui);
	printf("이전한 층수를 입력해주세요 : ");
	scanf("%d", &floor);


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "UPDATE STORE SET  BUINUM = %d, STFLOOR = %d", bui,floor);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("업데이트가 완료되었습니다.\n");

	}



}