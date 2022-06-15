#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void updatePrice();
void updateStock();
void updateDate();
void updateStoreInfo();

void Update() {
	char cmd;

	printf("(a) 가격 조정하기\n");
	printf("(b) 물품 재고 수정하기\n");
	printf("(c) 입고 지연으로 수령 예정일 연기\n");
	printf("(d) 상점 이전하기\n");

	printf("원하는 메뉴를 입력하세요 : ");
	scanf("%c", &cmd);
	getchar();

	switch (cmd) {
	case ('a'):
		updatePrice();
		break;
	case ('b'):
		updateStock();
		break;
	case ('c'):
		updateDate();
		break;
	case ('d'):
		updateStoreInfo();
		break;
	default:
		printf("잘못된 값을 입력했습니다. 처음부터 다시 시도해주세요.\n");
		break;
	}



}