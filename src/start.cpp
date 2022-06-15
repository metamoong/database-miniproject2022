#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <Windows.h>

void Select();
void Insert();
void Delete();
void Update();
void Custom();

void start() {
	while (1) {
		int cmd;
		printf("-------------------전자상가 기록 시스템-------------------\n");
		printf("1 : 조회하기 / 2 : 삽입하기 / 3 : 수정하기 / 4 : 삭제하기 / 5: 커스텀 쿼리 / 6: 종료하기\n");
		printf("원하는 메뉴의 번호를 입력하세요 : ");
		scanf("%d", &cmd);
		getchar();

		switch (cmd) {
		case 1:
			Select();
			break;
		case 2:
			Insert();
			break;
		case 3:
			Update();
			break;
		case 4:
			Delete();
			break;
		case 5 :
			Custom();
			break;
		case 6:
			exit(0);
		}
	}

}