#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void updatePrice();
void updateStock();
void updateDate();
void updateStoreInfo();

void Update() {
	char cmd;

	printf("(a) ���� �����ϱ�\n");
	printf("(b) ��ǰ ��� �����ϱ�\n");
	printf("(c) �԰� �������� ���� ������ ����\n");
	printf("(d) ���� �����ϱ�\n");

	printf("���ϴ� �޴��� �Է��ϼ��� : ");
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
		printf("�߸��� ���� �Է��߽��ϴ�. ó������ �ٽ� �õ����ּ���.\n");
		break;
	}



}