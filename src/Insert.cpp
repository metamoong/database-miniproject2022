#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void addStore();
void addProduct();
void addSellConf();
void addCustomer();

void Insert() {
	char cmd;
	int building_num;
	char name[21];

	printf("(a) 새로운 상점 입점하기\n");
	printf("(b) 물품 추가하기\n");
	printf("(c) 물품 판매하기\n");
	printf("(d) 새로운 손님 리스트에 추가하기\n");

	printf("원하는 메뉴를 입력하세요 : ");
	scanf("%c", &cmd);
	getchar();

	switch (cmd) {
	case ('a'):
		addStore();
		break;
	case ('b'):
		addProduct();
		break;
	case ('c'):
		addSellConf();
		break;
	case ('d'):
		addCustomer();
		break;
	default:
		printf("잘못된 값을 입력했습니다. 처음부터 다시 시도해주세요.\n");
		break;
	}



}