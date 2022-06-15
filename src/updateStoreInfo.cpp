#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "Windows.h"
#include "sql.h"
#include "sqlext.h"

extern SQLHENV hEnv; // ȯ�漳���� ���� ���簪
extern SQLHDBC hDbc;// ���ἳ���� ���� ���簪


void updateStoreInfo() {

	char stoname[21];
	printf("==========���� ���� �� ������ �����ϴ� �޴��Դϴ�. ==========\n");
	printf("���� �̸��� �Է����ּ��� : ");
	scanf("%s", stoname);


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "SELECT * FROM STORE WHERE STONAME = '%s'", stoname);
		SQLExecDirect(hStmt, query, SQL_NTS);


		SQLSMALLINT store_id, floor, building_num;
		SQLCHAR store_name[20], tel[20];

		SQLBindCol(hStmt, 1, SQL_C_SSHORT, &store_id, 5, NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, store_name, 20, NULL);
		SQLBindCol(hStmt, 2, SQL_C_SSHORT, &building_num, 5, NULL);
		SQLBindCol(hStmt, 5, SQL_C_SSHORT, &floor, 5, NULL);
		SQLBindCol(hStmt, 4, SQL_C_CHAR, tel, 20, NULL);


		printf("==========������ ���� �����Դϴ� ==========\n");


		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("���� ��ȣ : %d\n", store_id);
			printf("���� �̸� : %s\n", store_name);
			printf("��ġ : %d�� �ǹ� %d ��\n", building_num, floor);
			printf("����ó : %s\n", tel);
			printf("------------------------\n");
		}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	int bui;
	int floor;

	printf("������ �ǹ� ��ȣ�� �Է����ּ��� : ");
	scanf("%d", &bui);
	printf("������ ������ �Է����ּ��� : ");
	scanf("%d", &floor);


	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS) {
		sprintf((char*)query, "UPDATE STORE SET  BUINUM = %d, STFLOOR = %d", bui,floor);

		SQLExecDirect(hStmt, query, SQL_NTS);
		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		printf("������Ʈ�� �Ϸ�Ǿ����ϴ�.\n");

	}



}