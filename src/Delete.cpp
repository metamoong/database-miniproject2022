#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void deleteProduct();
void deleteStore();
void deleteSellConf();
void deleteCustomer();

void Delete() {
	char cmd;

	printf("(a) 재고가 0인 물품 삭제하기\n");
	printf("(b) 폐업한 상점 없에기\n");
	printf("(c) 주문 취소가 생긴 경우 주문서 삭제하기\n");
	printf("(d) 손님 정보 삭제하기\n");


	printf("원하는 메뉴를 입력하세요 : ");
	scanf("%c", &cmd);
	getchar();

	switch (cmd) {
	case ('a'):
		deleteProduct();
		break;
	case ('b'):
		deleteStore();
		break;
	case ('c'):
		deleteSellConf();
		break;
	case ('d'):
		deleteCustomer();
		break;
	default:
		printf("잘못된 값을 입력했습니다. 처음부터 다시 시도해주세요.\n");
		break;
	}



}