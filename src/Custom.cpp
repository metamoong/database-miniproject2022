#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#include <string.h>
#include <cctype>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪

void Custom() {

	static SQLCHAR query[100];
	SQLHSTMT hStmt;

	char input[101];
	char tmp[7];

	printf("�������� �Է����ּ��� : ");
	scanf("%[^\n]s", input);


	int i;
	for (i = 0; i < 6; i++) {
		if (islower(input[i])) {
			tmp[i] = toupper(input[i]);
		}
		else {
			tmp[i] = input[i];
		}
		
	}
	tmp[i] = '\0';

	if (strcmp(tmp, "SELECT") == 0) {
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
			sprintf((char*)query, input);
			SQLExecDirect(hStmt, query, SQL_NTS);
			printf("���� �������� �ʴ� ����Դϴ�.\n");


			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
	}
	else {
		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
			sprintf((char*)query,input);

			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			printf("ó���Ǿ����ϴ�.\n");
		}

	}


	
}