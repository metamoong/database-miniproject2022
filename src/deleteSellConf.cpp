#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "Windows.h"
#include "sql.h"
#include "sqlext.h"

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void deleteSellConf() {

	char stoname[21];


	printf("==========주문서를 삭제하기 위한 메뉴입니다==========\n");
	printf("상점 이름을 입력해주세요 : ");
	scanf("%s", stoname);
	getchar();


	static SQLCHAR query[100];
	SQLHSTMT hStmt;

	int id;
	printf("삭제할 주문서의 id를 입력해주세요 : ");
	scanf("%d", &id);

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "DELETE FROM SELLCONFIRMATION WHERE SCONFID = %d AND STOID = (SELECT STOID FROM STORE WHERE STONAME = '%s')", id, stoname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("삭제가 완료되었습니다.\n");

	}


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {

		SQLSMALLINT confid, quantity;
		SQLCHAR  cust_name[20], tel[20], prod_name[20];
		SQLCHAR orderdate[15], expdate[15];

		sprintf((char*)query, "SELECT SCONFID,C.CUSTNAME,C.TEL, P.PRODNAME, SC.QUANTITY, SC.ORDERDATE,SC.EXPECTEDDATE FROM SELLCONFIRMATION AS SC, CUSTOMER AS C, STORE AS S, PRODUCT AS P WHERE SC.CUSTTEL = C.TEL AND S.STOID = SC.STOID AND P.STOID = S.STOID AND P.PRODID = SC.PRODID AND S.STONAME = '%s'", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);

	
		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &confid, 5, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, cust_name, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, tel, 20, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, prod_name, 20, NULL);
		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &quantity, 5, NULL);
		SQLBindCol(hStmt, 6, SQL_C_CHAR, orderdate, 15, NULL);
		SQLBindCol(hStmt, 7, SQL_C_CHAR, expdate, 15, NULL);



		printf("==========%s 상점의 주문서 목록입니다. 삭제가 잘 되었는지 확인하세요.==========\n", stoname);
		printf("%-5s %-10s %-15s %-20s %-10s %-15s %-15s\n", "id", "name", "tel", "product", "quantity", "order-date", "expect-date");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-10s %-15s %-20s %-10d %-15s %-15s\n", confid, cust_name, tel, prod_name, quantity, orderdate, expdate);
		}

	
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}







}