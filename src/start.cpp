#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <Windows.h>

void selectByStore();
void Select();

void start() {

	int cmd;
	printf("-------------------���ڻ� ��� �ý���-------------------\n");
	printf("1 : ��ȸ�ϱ� / 2 : �����ϱ� / 3 : �����ϱ� / 4 : �����ϱ� / 5: ���α׷� ����\n");
	printf("���ϴ� �޴��� ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &cmd);
	getchar();

	switch (cmd) {
	case 1:
		Select();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4 : 
		break;
	case 5 :
		exit(0);
	}

}