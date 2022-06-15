#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void addProduct() {


	int sto_id;
	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	printf("��ǰ�� �߰��� ���� ��ȣ�� �Է����ּ��� : ");
	scanf("%d",&sto_id);
	getchar();

	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		SQLSMALLINT prodid, stock;
		SQLINTEGER price;
		SQLCHAR prodname[20];


		sprintf((char*)query, "SELECT PRODID, PRODNAME, PRICE, STOCK FROM PRODUCT WHERE STOID = %d", sto_id);
		SQLExecDirect(hStmt, query, SQL_NTS);

		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &prodid, 7, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, prodname ,20,NULL);
		SQLBindCol(hStmt, 3, SQL_C_SLONG, &price, 7, NULL);
		SQLBindCol(hStmt, 4, SQL_C_SSHORT, &stock, 5, NULL);


		printf("===========%d �� ������ ��ǰ ����Դϴ�. �ߺ����� �ʵ��� ������ �Է����ּ���.===========\n", sto_id);
		printf("%-7s %-20s %-7s %-5s\n", "prod_id", "name", "price", "stock");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("%-7d %-20s %-7d %-5d\n", prodid, prodname, price, stock);
		}

	
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}



	
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {

		int prodid, price, stock;
		char prodname[21];

		printf("==========�߰��� ��ǰ�� ���� ������ �Է��ϼ���==========\n");

		printf("��ǰ ��ȣ�� �Է����ּ��� : ");
		scanf("%d", &prodid);
		getchar();
		printf("��ǰ �̸��� �Է����ּ��� : ");
		scanf("%s", prodname);
		printf("��ǰ ������ �Է����ּ��� : ");
		scanf("%d", &price);
		printf("��� �Է����ּ��� : ");
		scanf("%d", &stock);


		sprintf((char*)query, "INSERT INTO PRODUCT VALUES(%d,'%s',%d,%d,%d)", prodid, prodname, sto_id, price, stock);


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
			printf("��ǰ �߰��� �Ϸ�Ǿ����ϴ�.\n");
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}
}