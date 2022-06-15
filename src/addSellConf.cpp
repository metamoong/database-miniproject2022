#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void addSellConf() {
	int sto_id;
	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	printf("물품을 판매한 상점 번호를 입력해주세요 : ");
	scanf("%d", &sto_id);
	getchar();

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		SQLSMALLINT prodid, stock;
		SQLINTEGER price;
		SQLCHAR prodname[20];


		sprintf((char*)query, "SELECT PRODID, PRODNAME, PRICE, STOCK FROM PRODUCT WHERE STOID = %d", sto_id);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &prodid, 7, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, prodname, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_SLONG, &price, 7, NULL);
		SQLBindCol(hStmt, 4, SQL_C_SSHORT, &stock, 5, NULL);


		printf("===========%d 번 상점의 물품 목록입니다.===========\n", sto_id);
		printf("%-7s %-20s %-7s %-5s\n", "prod_id", "name", "price", "stock");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-7d %-20s %-7d %-5d\n", prodid, prodname, price, stock);
		}


		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}




	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {

		int prodid,sconfid,cnt;
		char custtel[21];
		char orderdate[21];
		char expecteddate[21];

		printf("==========판매한 물품에 대한 정보를 입력하세요==========\n");


		printf("주문서 번호를 입력해주세요 : ");
		scanf("%d", &sconfid);
		printf("물품 번호를 입력해주세요 : ");
		scanf("%d", &prodid);
		printf("구매 수량을 입력해주세요 : ");
		scanf("%d", &cnt);

		getchar();
		printf("물품을 구매한 고객의 전화번호를 입력하세요 : ");
		scanf("%s", custtel);
		getchar();
		printf("주문일을 입력해주세요 : ");
		scanf("%s", orderdate);
		getchar();
		printf("수령 예상일을 입력해주세요 : ");
		scanf("%s", expecteddate);


		sprintf((char*)query, "INSERT INTO SELLCONFIRMATION VALUES(%d,%d,'%s',%d,%d,'%s','%s')", sconfid,sto_id,custtel,prodid,cnt,orderdate,expecteddate);
		if (SQLExecDirect(hStmt, query, SQL_NTS) == SQL_ERROR) {
			printf("Error\n");
			SQLCHAR buffer[SQL_MAX_MESSAGE_LENGTH];
			SQLCHAR sqlstate[SQL_SQLSTATE_SIZE];
			SQLINTEGER sqlcode;
			SQLSMALLINT length;

			SQLError(hEnv, hDbc, hStmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length);
			printf("SQLSTATE %s\n", sqlstate);
			printf("Native error code:%ld\n", sqlcode);
			printf("%s\n\n", buffer);

		}
		else {

		}


		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
			sprintf((char*)query, "UPDATE PRODUCT SET STOCK = STOCK - %d WHERE PRODID = %d AND STOID = %d", cnt, prodid, sto_id);

			SQLExecDirect(hStmt, query, SQL_NTS);
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		}
		
		printf("추가가 완료되었습니다.\n");

		


	}
}