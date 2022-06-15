#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void showPrice() {
	static SQLCHAR query[100];
	SQLHSTMT hStmt;

	char prodname[20];


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		printf("===========상품 가격 비교를 위한 메뉴입니다 ===========\n");
		printf("찾고자 하는 상품 이름을 입력해주세요 : ");
		scanf("%s", prodname);
		getchar();


		sprintf((char*)query, "SELECT S.STONAME, S.TEL, P.PRICE, P.STOCK FROM PRODUCT AS P, STORE AS S WHERE P.PRODNAME = '%s' AND P.STOID = S.STOID ORDER BY PRICE",prodname);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT stock;
		SQLINTEGER price;
		SQLCHAR store_name[20], tel[20];


		SQLBindCol(hStmt, 1, SQL_C_CHAR, store_name, 20, NULL); 
		SQLBindCol(hStmt, 2, SQL_C_CHAR, tel, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_SLONG, &price, 7, NULL);
		SQLBindCol(hStmt, 4, SQL_C_SSHORT, &stock, 5, NULL);


		printf("\n");
		printf("==========낮은 가격 순 목록입니다==========\n");

		printf("%-20s %-20s %-7s %-5s\n", "STORE", "TEL", "PRICE", "STOCK");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-20s %-20s %-7d %-5d\n", store_name, tel, price, stock);
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}