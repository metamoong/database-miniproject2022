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

	printf("(a) ���ο� ���� �����ϱ�\n");
	printf("(b) ��ǰ �߰��ϱ�\n");
	printf("(c) ��ǰ �Ǹ��ϱ�\n");
	printf("(d) ���ο� �մ� ����Ʈ�� �߰��ϱ�\n");

	printf("���ϴ� �޴��� �Է��ϼ��� : ");
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
		printf("�߸��� ���� �Է��߽��ϴ�. ó������ �ٽ� �õ����ּ���.\n");
		break;
	}



}