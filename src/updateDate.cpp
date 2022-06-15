#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "Windows.h"
#include "sql.h"
#include "sqlext.h"

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void updateDate() {

	char stoname[21];


	printf("==========수령 예정일을 수정하는 메뉴입니다. ==========\n");
	printf("상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT SCONFID,C.CUSTNAME,C.TEL, P.PRODNAME, SC.QUANTITY, SC.ORDERDATE,SC.EXPECTEDDATE FROM SELLCONFIRMATION AS SC, CUSTOMER AS C, STORE AS S, PRODUCT AS P WHERE SC.CUSTTEL = C.TEL AND S.STOID = SC.STOID AND P.STOID = S.STOID AND P.PRODID = SC.PRODID AND S.STONAME = '%s'", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLSMALLINT confid, quantity;
		SQLCHAR store_name[20], cust_name[20], tel[20], prod_name[20];
		SQLCHAR orderdate[15], expdate[15];


		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &confid, 5, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, cust_name, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, tel, 20, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, prod_name, 20, NULL);
		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &quantity, 5, NULL);
		SQLBindCol(hStmt, 6, SQL_C_CHAR, orderdate, 15, NULL);
		SQLBindCol(hStmt, 7, SQL_C_CHAR, expdate, 15, NULL);



		printf("==========%s 상점의 판매 내역입니다.==========\n",stoname);
		printf("%-5s %-10s %-15s %-20s %-10s %-15s %-15s\n", "id", "name", "tel", "product", "quantity", "order-date", "expect-date");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-10s %-15s %-20s %-10d %-15s %-15s\n", confid, cust_name, tel, prod_name, quantity, orderdate, expdate);
		}


	}

	int id;
	char date[21];
	printf("주문서의 id를 입력해주세요 : ");
	scanf("%d", &id);
	printf("연기된 예정일을 입력해주세요 : ");
	scanf("%s", date);


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "UPDATE SELLCONFIRMATION SET EXPECTEDDATE = '%s' WHERE  SCONFID = %d", date,id);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("업데이트가 완료되었습니다.\n");

	}



}