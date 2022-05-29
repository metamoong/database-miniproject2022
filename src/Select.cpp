#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void selectByStore(int);
void showStoreInfo(char*);
void showHistory(int);

void Select() {
	char cmd;
	int building_num;
	char name[21];

	printf("(a) 건물에 입점한 상점 목록 조회하기\n");
	printf("(b) 상점 정보 검색하기\n");
	printf("(c) 상점의 거래내역 조회하기\n");
	printf("(d) 손님의 거래내역 조회하기\n");
	printf("(e) 상품 가격 비교하기\n");

	printf("원하는 메뉴를 입력하세요 : ");
	scanf("%c", &cmd);
	getchar();

	
	printf("%c\n", cmd);
	switch (cmd) {
	case ('a'):
		printf("건물 번호를 입력하세요(1, 2, 3) : ");
		scanf("%d", &building_num);
		selectByStore(building_num);
		break;
	case ('b'):
		printf("검색하고자 하는 상점의 이름을 입력하세요 : ");
		scanf("%s", name);
		showStoreInfo(name);
		break;
	case ('c'):
		int id;
		printf("조회를 원하는 상점의 id 를 입력하세요 : ");
		scanf("%d", &id);
		showHistory(id);
		break;
	case ('d'):
		break;
	case ('e'):
		break;
	case ('f'):
		break;
	default:
		break;
	}
	

}