#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void deleteProduct() {

	char stoname[21];

	printf("===========���� �̸��� �Է��Ͻø� ��� ���� ��ǰ�� ������ �� �ֽ��ϴ�.=========\n");
	printf("���� �̸��� �Է����ּ��� : ");
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



		printf("===========���� \"%s\" �� ��� 0�� ��ǰ ����Դϴ�.===========\n", stoname);
		printf("%-5s %-20s %-7s %-5s\n", "id", "name", "price", "stock");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-5d %-20s %-7d %-5d\n", prodid, prodname, price, stock);
		}


		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}


	char cmd;
	printf("���� ��ǰ���� �����Ͻðڽ��ϱ�? Y / N : ");
	scanf("%c", &cmd);

	if (cmd == 'Y') {
		

		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
			sprintf((char*)query, "DELETE FROM PRODUCT WHERE STOID = (SELECT STOID FROM STORE WHERE STONAME = '%s') AND PRODUCT.STOCK = 0",stoname);

			SQLExecDirect(hStmt, query, SQL_NTS);
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			printf("������ �Ϸ�Ǿ����ϴ�.\n");

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		

	}
	else {
		printf("���α׷��� �����մϴ�.");
	}

	
}