#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void showHistory(char * stoname) {
	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT BCONFID,C.CUSTNAME,C.TEL, BC.PRODNAME, BC.QUANTITY, BC.DATE FROM BUYCONFIRMATION AS BC, CUSTOMER AS C, STORE AS S WHERE BC.CUSTTEL = C.TEL AND S.STOID = (SELECT STOID FROM STORE WHERE STONAME = '%s') AND BC.STOID = S.STOID", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT confid,quantity;
		SQLCHAR store_name[20], cust_name[20],tel[20],prod_name[20],date[15];

		
		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &confid, 5, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, cust_name, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, tel, 20, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, prod_name, 20, NULL);
		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &quantity, 5, NULL);
		SQLBindCol(hStmt, 6, SQL_C_CHAR, date, 15, NULL);



		printf("<매입 내역>\n");
		printf("%-5s %-15s %-15s %-15s %-10s %-15s\n", "num","name", "tel","product","quantity","date");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-15s %-15s %-15s %-10d %-15s\n", confid,cust_name,tel,prod_name,quantity,date);
		}



		printf("\n\n");


		
	}

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



		printf("<판매 내역>\n");
		printf("%-5s %-10s %-15s %-20s %-10s %-15s %-15s\n", "num", "name", "tel", "product", "quantity", "order-date", "expect-date");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-10s %-15s %-20s %-10d %-15s %-15s\n", confid, cust_name, tel, prod_name, quantity, orderdate, expdate);
		}



		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}