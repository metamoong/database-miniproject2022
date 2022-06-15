#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#include <string.h>

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void addCustomer() {


	int sto_id;
	char tel[21],name[21],address[21],buyer[21];


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	printf("==========�մ��� ����Ʈ�� �߰��ϱ� ���� �޴��Դϴ�.==========\n");
	
	printf("�߰��� �մ��� ��ȭ��ȣ�� �Է����ּ��� : ");
	scanf("%s", tel);
	printf("�߰��� �մ��� �̸��� �Է����ּ���: ");
	scanf("%s", name);
	printf("�߰��� �մ��� �ּ����� �Է����ּ��� : ");
	scanf("%s", address);
	printf("���� �ŷ��ڰ� ������ �ŷ����� ��ȣ��, ���ٸ� x �� �Է����ּ��� : ");
	scanf("%s", buyer);



	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		if (strcmp(buyer, "x") == 0) {
			sprintf((char*)query, "INSERT INTO CUSTOMER VALUES('%s','%s','%s',NULL)", tel, name, address);
		}
		else {

			sprintf((char*)query, "INSERT INTO CUSTOMER VALUES('%s','%s','%s','%s')", tel, name, address, buyer);
		}
		
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
				printf("�մ� �߰��� �Ϸ�Ǿ����ϴ�.\n");
			}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}
}