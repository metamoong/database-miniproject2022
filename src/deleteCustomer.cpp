#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>

extern SQLHENV hEnv; // 환경설정에 대한 현재값
extern SQLHDBC hDbc;// 연결설정에 대한 현재값


void deleteCustomer() {

	char tel[21];

	printf("===========손님 정보를 삭제하기 위한 메뉴입니다=========\n");
	printf("손님의 전화번호를 입력해주세요 : ");
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


		printf("===========입력한 손님에 대한 정보입니다===========\n");

		while (SQLFetch(hStmt) != SQL_NO_DATA) {
			printf("전화번호 : %s\n", tel);
			printf("이름 : %s\n", name);
			printf("주소지 : %s\n", address);
		}

		char cmd;
		printf("위의 손님에 대한 정보를 삭제하시겠습니까? Y / N : ");
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

				printf("삭제가 완료되었습니다.\n");


			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		}
		else {
			printf("메인 화면으로 되돌아갑니다.");
		}




		SQLCloseCursor(hStmt);
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	}


	

	


}