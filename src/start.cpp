#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <Windows.h>

void selectByStore();
void Select();

void start() {

	int cmd;
	printf("-------------------전자상가 기록 시스템-------------------\n");
	printf("1 : 조회하기 / 2 : 삽입하기 / 3 : 수정하기 / 4 : 삭제하기 / 5: 프로그램 종료\n");
	printf("원하는 메뉴의 번호를 입력하세요 : ");
	scanf("%d", &cmd);
	getchar();

	switch (cmd) {
	case 1:
		Select();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4 : 
		break;
	case 5 :
		exit(0);
	}

}