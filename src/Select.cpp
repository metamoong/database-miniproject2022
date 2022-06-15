#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void selectByStore(int);
void showStoreInfo(char*);
void showHistory(char *);
void showPrice();
void showCustomerInfo();
void showCustomerHistory();

void Select() {
	char cmd;
	int building_num;
	char name[21];

	printf("(a) �ǹ��� ������ ���� ��� ��ȸ�ϱ�\n");
	printf("(b) ���� ���� �˻��ϱ�\n");
	printf("(c) ������ �ŷ����� ��ȸ�ϱ�\n");
	printf("(d) �մ��� �ŷ����� ��ȸ�ϱ�\n");
	printf("(e) ��ǰ ���� ���ϱ�\n");
	printf("(f) �մ� ���� �˻��ϱ�\n");

	printf("���ϴ� �޴��� �Է��ϼ��� : ");
	scanf("%c", &cmd);
	getchar();


	switch (cmd) {
	case ('a'):
		printf("�ǹ� ��ȣ�� �Է��ϼ���(1, 2, 3) : ");
		scanf("%d", &building_num);
		selectByStore(building_num);
		break;
	case ('b'):
		printf("�˻��ϰ��� �ϴ� ������ �̸��� �Է��ϼ��� : ");
		scanf("%s", name);
		showStoreInfo(name);
		break;
	case ('c'):
		char stoname[20];
		printf("��ȸ�� ���ϴ� ������ �̸��� �Է��ϼ��� : ");
		scanf("%s", stoname);
		getchar();
		showHistory(stoname);
		break;
	case ('d'):
		showCustomerHistory();
		break;
	case ('e'):
		showPrice();
		break;
	case ('f'):
		showCustomerInfo();
		break;
	default:
		printf("�߸��� ���� �Է��߽��ϴ�. ó������ �ٽ� �õ����ּ���.\n");
	}
	

}