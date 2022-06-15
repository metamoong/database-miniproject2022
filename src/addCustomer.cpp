#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#include <string.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void addCustomer() {


	int sto_id;
	char tel[21],name[21],address[21],buyer[21];


	static SQLCHAR query[100];
	SQLHSTMT hStmt;


	printf("==========손님을 리스트에 추가하기 위한 메뉴입니다.==========\n");
	
	printf("추가할 손님의 전화번호를 입력해주세요 : ");
	scanf("%s", tel);
	printf("추가할 손님의 이름을 입력해주세요: ");
	scanf("%s", name);
	printf("추가할 손님의 주소지를 입력해주세요 : ");
	scanf("%s", address);
	printf("전용 거래자가 있으면 거래자의 번호를, 없다면 x 를 입력해주세요 : ");
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
				printf("손님 추가가 완료되었습니다.\n");
			}

		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}
}