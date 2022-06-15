#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void updatePrice() {

	char stoname[21];
	

	printf("==========물품의 가격을 수정하는 메뉴입니다==========\n");
	printf("상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		SQLSMALLINT prodid, stock;
		SQLINTEGER price;
		SQLCHAR prodname[20];


		sprintf((char*)query, "SELECT PRODID, PRODNAME,PRICE,STOCK FROM PRODUCT, STORE WHERE STONAME = '%s' AND PRODUCT.STOID = STORE.STOID", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &prodid, 5, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, prodname, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_SLONG, &price, 7, NULL);
		SQLBindCol(hStmt, 4, SQL_C_SSHORT, &stock, 5, NULL);



		printf("===========상점 \"%s\" 의 물품 목록입니다.===========\n", stoname);
		printf("%-5s %-20s %-7s %-5s\n", "id", "name", "price", "stock");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-20s %-7d %-5d\n", prodid, prodname, price, stock);
		}


		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}


	int id;
	double c;

	printf("가격을 조정할 물품의 id 를 입력하세요 : ");
	scanf("%d", &id);

	printf("가격 조정 비율을 입력하세요 : ");
	scanf("%lf", &c);
	

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "UPDATE PRODUCT SET PRICE = PRICE*%lf WHERE STOID = ( SELECT STOID FROM STORE WHERE STONAME = '%s') AND PRODID = %d",c, stoname,id);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("업데이트가 완료되었습니다.\n");

	}

	


}