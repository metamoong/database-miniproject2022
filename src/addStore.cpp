#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void addStore() {

	int id,bui_num,floor;
	char stoname[21];
	char tel[21];

	printf("==========������ ������ ���� ������ �Է����ּ���==========\n");

	printf("���� �̸��� �Է����ּ��� : ");
	scanf("%s", stoname);

	printf("�ǹ� ��ȣ�� �Է����ּ��� :");
	scanf("%d", &bui_num);


	while (1) {
		printf("������ ������ �Է����ּ��� :");
		scanf("%d", &floor);

		if (floor == 1 || floor == 2 || floor == 3) {
			break;
		}

		printf("�� ���� 1/2/3 �� �ϳ��� ������ �ԷµǾ�� �մϴ�.\n");
	}


	getchar();
	printf("���� ����ó�� �Է����ּ��� : ");
	scanf("%s", tel);


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "INSERT INTO STORE VALUES(%d,'%s','%s',%d)",bui_num,stoname,tel,floor);
		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


		printf("���� �߰��� �Ϸ�Ǿ����ϴ�.\n");

	}
}