#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void deleteCustomer() {

	char tel[21];

	printf("===========�մ� ������ �����ϱ� ���� �޴��Դϴ�=========\n");
	printf("�մ��� ��ȭ��ȣ�� �Է����ּ��� : ");
	scanf("%s", tel);
	getchar();


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		SQLCHAR name[21],address[21];


		sprintf((char*)query, "SELECT CUSTNAME,CUSTADDRESS FROM CUSTOMER WHERE TEL = '%s'", tel);
		SQLExecDirect(hStmt, query, SQL_NTS);


	
		SQLBindCol(hStmt, 1, SQL_C_CHAR, name, 20, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, address, 20, NULL);


		printf("===========�Է��� �մԿ� ���� �����Դϴ�===========\n");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("��ȭ��ȣ : %s\n", tel);
			printf("�̸� : %s\n", name);
			printf("�ּ��� : %s\n", address);
		}

		char cmd;
		printf("���� �մԿ� ���� ������ �����Ͻðڽ��ϱ�? Y / N : ");
		scanf("%c", &cmd);


		if (cmd == 'Y') {
			if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
				sprintf((char*)query, "UPDATE CUSTOMER SET BUYER = NULL WHERE BUYER = '%s'",tel );

				SQLExecDirect(hStmt, query, SQL_NTS);
				SQLCloseCursor(hStmt);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
				sprintf((char*)query, "DELETE FROM CUSTOMER WHERE TEL = '%s'", tel);

				SQLExecDirect(hStmt, query, SQL_NTS);
				SQLCloseCursor(hStmt);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

				printf("������ �Ϸ�Ǿ����ϴ�.\n");


			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		}
		else {
			printf("���� ȭ������ �ǵ��ư��ϴ�.");
		}




		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}


	

	


}