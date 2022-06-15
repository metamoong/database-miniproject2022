#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void deleteProduct() {

	char stoname[21];

	printf("===========상점 이름을 입력하시면 재고가 없는 물품을 삭제할 수 있습니다.=========\n");
	printf("상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);
	getchar();


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		SQLSMALLINT prodid, stock;
		SQLINTEGER price;
		SQLCHAR prodname[20];


		sprintf((char*)query, "SELECT PRODID, PRODNAME,PRICE,STOCK FROM PRODUCT, STORE WHERE STONAME = '%s' AND PRODUCT.STOID = STORE.STOID AND PRODUCT.STOCK = 0", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &prodid, 5, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, prodname, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_SLONG, &price, 7, NULL);
		SQLBindCol(hStmt, 4, SQL_C_SSHORT, &stock, 5, NULL);



		printf("===========상점 \"%s\" 의 재고가 0인 물품 목록입니다.===========\n", stoname);
		printf("%-5s %-20s %-7s %-5s\n", "id", "name", "price", "stock");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-20s %-7d %-5d\n", prodid, prodname, price, stock);
		}


		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}


	char cmd;
	printf("위의 물품들을 삭제하시겠습니까? Y / N : ");
	scanf("%c", &cmd);

	if (cmd == 'Y') {
		

		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
			sprintf((char*)query, "DELETE FROM PRODUCT WHERE STOID = (SELECT STOID FROM STORE WHERE STONAME = '%s') AND PRODUCT.STOCK = 0",stoname);

			SQLExecDirect(hStmt, query, SQL_NTS);
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			printf("삭제가 완료되었습니다.\n");

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		

	}
	else {
		printf("프로그램을 종료합니다.");
	}

	
}