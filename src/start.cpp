#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <Windows.h>

void Select();
void Insert();
void Delete();
void Update();
void Custom();

void start() {
	while (1) {
		int cmd;
		printf("-------------------���ڻ� ��� �ý���-------------------\n");
		printf("1 : ��ȸ�ϱ� / 2 : �����ϱ� / 3 : �����ϱ� / 4 : �����ϱ� / 5: Ŀ���� ���� / 6: �����ϱ�\n");
		printf("���ϴ� �޴��� ��ȣ�� �Է��ϼ��� : ");
		scanf("%d", &cmd);
		getchar();

		switch (cmd) {
		case 1:
			Select();
			break;
		case 2:
			Insert();
			break;
		case 3:
			Update();
			break;
		case 4:
			Delete();
			break;
		case 5 :
			Custom();
			break;
		case 6:
			exit(0);
		}
	}

}