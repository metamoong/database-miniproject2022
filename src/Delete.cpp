#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void deleteProduct();
void deleteStore();
void deleteSellConf();
void deleteCustomer();

void Delete() {
	char cmd;

	printf("(a) ��� 0�� ��ǰ �����ϱ�\n");
	printf("(b) ����� ���� ������\n");
	printf("(c) �ֹ� ��Ұ� ���� ��� �ֹ��� �����ϱ�\n");
	printf("(d) �մ� ���� �����ϱ�\n");


	printf("���ϴ� �޴��� �Է��ϼ��� : ");
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
		printf("�߸��� ���� �Է��߽��ϴ�. ó������ �ٽ� �õ����ּ���.\n");
		break;
	}



}