#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void selectByStore(int);
void showStoreInfo(char*);
void showHistory(int);

void Select() {
	char cmd;
	int building_num;
	char name[21];

	printf("(a) �ǹ��� ������ ���� ��� ��ȸ�ϱ�\n");
	printf("(b) ���� ���� �˻��ϱ�\n");
	printf("(c) ������ �ŷ����� ��ȸ�ϱ�\n");
	printf("(d) �մ��� �ŷ����� ��ȸ�ϱ�\n");
	printf("(e) ��ǰ ���� ���ϱ�\n");

	printf("���ϴ� �޴��� �Է��ϼ��� : ");
	scanf("%c", &cmd);
	getchar();

	
	printf("%c\n", cmd);
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
		int id;
		printf("��ȸ�� ���ϴ� ������ id �� �Է��ϼ��� : ");
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