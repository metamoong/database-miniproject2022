#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void deleteStore() {


	static SQLCHAR query[100];
	SQLHSTMT hStmt;

	char stoname[21];

	printf("===========����� ������ �����ϴ� �޴��Դϴ�=========\n");
	printf("�����Ϳ��� ������ ���� �̸��� �Է����ּ��� : ");
	scanf("%s", stoname);



	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "DELETE FROM STORE WHERE STONAME = '%s'", stoname);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("������ �Ϸ�Ǿ����ϴ�.\n");

	}



}