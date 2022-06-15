#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void showCustomerHistory() {
	static SQLCHAR query[100];
	SQLHSTMT hStmt;
	char tel[21];

	printf("===========���� �ŷ����� ��ȸ�� ���� �޴��Դϴ�. ===========\n");
	printf("�˻��ϰ��� �ϴ� ���� ��ȭ��ȣ�� �Է��ϼ��� : ");
	scanf("%s", tel);
	getchar();

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT S.STONAME, BC.PRODNAME, BC.QUANTITY, BC.DATE  FROM BUYCONFIRMATION AS BC, CUSTOMER AS C, STORE AS S WHERE BC.CUSTTEL = C.TEL AND BC.STOID = S.STOID AND BC.CUSTTEL = '%s'", tel);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT quantity;
		SQLCHAR store_name[20], prod_name[20], date[15];


		SQLBindCol(hStmt, 1, SQL_C_CHAR, store_name, 20, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, prod_name, 20, NULL);
		SQLBindCol(hStmt, 3, SQL_C_SSHORT, &quantity, 5, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, date, 15, NULL);



		printf("<�Ǹ� ����>\n");
		printf("%-20s %-20s %-10s %-15s\n", "store", "product", "quantity", "date");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-20s %-20s %-10d %-15s\n", store_name, prod_name, quantity, date);
		}

		printf("\n\n");

	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT S.STONAME,P.PRODNAME, SC.QUANTITY, SC.ORDERDATE,SC.EXPECTEDDATE FROM SELLCONFIRMATION AS SC, CUSTOMER AS C, STORE AS S, PRODUCT AS P WHERE SC.CUSTTEL = C.TEL AND S.STOID = SC.STOID AND P.STOID = S.STOID AND P.PRODID = SC.PRODID AND c.TEL = '%s'",tel);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLSMALLINT quantity;
		SQLCHAR store_name[20],  prod_name[20];
		SQLCHAR orderdate[15], expdate[15];


		SQLBindCol(hStmt, 1, SQL_C_CHAR, &store_name, 21, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, prod_name, 20, NULL);
		SQLBindCol(hStmt, 3,SQL_C_SSHORT, &quantity, 5, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, orderdate, 15, NULL);
		SQLBindCol(hStmt, 5, SQL_C_CHAR, expdate, 15, NULL);



		printf("<���� ����>\n");
		printf("%-20s %-20s %-10s %-15s %-15s\n", "store", "product", "quantity", "order-date", "expect-date");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-20s %-20s  %-10d %-15s %-15s\n", store_name, prod_name, quantity, orderdate, expdate);
		}

		printf("\n\n");

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
}