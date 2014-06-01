/*
�ۼ��� : 141076 ������
�ۼ��� : 2014.06.01
��  �� :	���α׷��� ���� �⸻����(2��)
ȸ�������������α׷��� ȸ������, ȸ���߰�, ���� ��� ����
*/


#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "member management.h"
#define MAX_SIZE	(1000)

DATA member[MAX_SIZE];


int countMemberNum(void)		// ��ϵ� ȸ������ üũ�ϴ� �Լ�(�� �� �������� �׸� ����)
{		

	int memberNum = 1;
	char str[100];

	FILE *f = fopen("data.txt", "rt");
	if (f == NULL){
		puts("���Ͽ��� ����!");
		return -1;
	}

	while (fgets(str, 100, f) != NULL)
	{
		if (feof(f) != 0)
			break;
		memberNum++;
	}
	fclose(f);
	return memberNum;
}


int countMaxId(DATA *pmember, int memberNum)		// �ű�ȸ���� ���̵� �����ϱ� ���� ���� ���̵� �� ���� ū ���� �˻��ϴ� �Լ�
{
	int maxId = 0;
	int i;
	int transferId[MAX_SIZE];

	for (i = 0; i < memberNum; i++)
		transferId[i] = atoi(pmember[i].id);
	for (i = 0; i < memberNum; i++)
	{
		if (maxId < transferId[i])
			maxId = transferId[i];
	}
	return maxId;
}


int validName(DATA *pmember, int memberNum)		// ����ϰ��� �ϴ� �̸��� ��ȿ���� Ȯ��
{
	int len = strlen(pmember[memberNum].name);
	int chkName = atoi(pmember[memberNum].name);		// ���ڰ� ���Ե� ��� ��ȿ���� ���� �̸�

	if (len == 0)
		return 0;
	if (chkName > 0)
		return 0;
	return 1;
}


int validAddress(DATA *pmember, int memberNum)		// ����ϰ��� �ϴ� �ּҰ� ��ȿ���� Ȯ��
{
	int len = strlen(pmember[memberNum].address);

	if (len == 0)
		return 0;
	else
		return 1;
}


int validPhoneNum(DATA *pmember, int memberNum)		// ����ϰ��� �ϴ� �ڵ��� ��ȣ�� ��ȿ���� Ȯ��
{
	int len = strlen(pmember[memberNum].phoneNum);
	int i;
	if (len == 0)
		return 0;
	if (pmember[memberNum].phoneNum[3] != '-')		// �׹�° ��ġ�� �������� ���ԵǴ��� Ȯ��
		return 0;
	if (!(pmember[memberNum].phoneNum[7] == '-' || pmember[memberNum].phoneNum[8] == '-'))		// 8��° ��ġ �Ǵ� 9��° ��ġ�� �������� ���ԵǴ��� Ȯ��
		return 0;
	return 1;
}


void addMember(DATA *pmember, int memberNum)		// ���ο� ȸ�� �߰� ���
{
	printf("�߰��� ȸ���� ������ ������ �Է��ϼ��� \n");
	itoa(countMaxId(pmember, memberNum) + 1, member[memberNum].id, 10);
	printf("���̵�(�ڵ�����): %d \n", countMaxId(pmember, memberNum) + 1);		// ���̵�� �ڵ� ����
	while (1)
	{
		printf("�̸�: ");
		fflush(stdin);
		gets(pmember[memberNum].name);

		if (validName(pmember, memberNum) == 0)
			printf("��ȿ���� ���� �̸��Դϴ�. \n");
		else
			break;
	}

	while (1)
	{
		printf("�ּ�: ");
		fflush(stdin);
		gets(pmember[memberNum].address);
		if (validAddress(pmember, memberNum) == 0)
			printf("��ȿ���� ���� �ּ��Դϴ�. \n");
		else
			break;
	}

	while (1)
	{
		printf("�ڵ��� ��ȣ: ");
		fflush(stdin);
		gets(pmember[memberNum].phoneNum);
		if (validPhoneNum(pmember, memberNum) == 0)
			printf("��ȿ���� ���� �ڵ��� ��ȣ�Դϴ�. \n");
		else
			break;
	}
}






void loadDataFile(DATA *pmember, int memberNum)		// txt���Ͽ��� �����͸� �ε���
{
	int i;

	FILE *f = fopen("data.txt", "rt");
	if (f == NULL){
		puts("���Ͽ��� ����!");
	}

	for (i = 0; i <= memberNum; i++)		// tab ������ ȸ�� ������ �б�
	if (i == 0)
		continue;
	else
		fscanf(f, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);
	fclose(f);
}







void printMemberInfo(DATA *pmember, int memberNum)		// ��� ȸ�� ��ü�� ����ϴ� �Լ�(����ü �����Ϳ� ��� ȸ�� ���� �Ű������� ����)
{
	int i;
	int goMain = 0;

	//printf("    ���̵�\tȸ���̸�\t\tȸ���ּ�\t\t �ڵ�����ȣ\n");
	for (i = 1; i < memberNum; i++)		// �о�� ȸ�� ������ ���
		printf("%10s\t%7s\t\t%8s\t\t%7s \n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);
	printf("\n\n");
	while (1)
	{
		printf("���� ȭ������ �̵��Ͻ÷��� (1)�� �Է��ϼ���: ");		// ����ȭ������ �̵��ϴ� ���
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");

}


void saveDataFile(DATA *pmember, int memberNum)
{
	int i;

	FILE *f = fopen("data.txt", "wt");
	if (f == NULL){
		puts("���Ͽ��� ����!");
	}

	for (i = 1; i < memberNum; i++)		// tab ������ ȸ�� ������ �б�
		fprintf(f, "%s\t%s\t%s\t%s\n", &pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

	fclose(f);
}





void printMainMenu(void)
{
	printf("================================================\n");
	printf("============ ȸ������ ���� ���α׷� ============\n");
	printf("================================================\n");
	printf("		1. ȸ�� ���� \n");
	printf("		2. ȸ�� ����ϱ� \n");
	printf("		3. ȸ�� �����ϱ� \n");
	printf("		4. ȸ������ �����ϱ� \n");
	printf("		5. ȸ�� �˻��ϱ� \n");
	printf("		6. �����ϱ� \n");
	printf("		7. �����ϱ� \n");
	printf("================================================\n");
	printf("================================================\n");
}



void startInterface(void)		// ����ȭ�� ���� ���
{
	DATA *pmember = member;
	int userChoice = 0;		// ����ڰ� ��� ������ �ϴ� ���� 
	char offChoice;
	int memberNum = countMemberNum();
	loadDataFile(pmember, memberNum);

	while (1)
	{
		printMainMenu();

		do
		{
			printf("\n\n");
			printf("	���ϴ� ����� �������ּ���: ");
			scanf_s("%d", &userChoice);
			fflush(stdin);

			if (userChoice<1 || userChoice > 7)
			{
				printf("\n");
				printf("	�߸��� ��ȣ�� �Է��ϼ̽��ϴ�! �ٽ� �������ּ���. \n");
			}
		} while (userChoice < 1 || userChoice > 7);
		system("cls");

		switch (userChoice)
		{
		case 1:		// ȸ�� ����
			printMemberInfo(pmember, memberNum);		
			break;
		case 2:		// ȸ�� ����ϱ�
			addMember(pmember, memberNum);
			memberNum++;
			break;
		case 3:		// ȸ�� �����ϱ�
		case 4:		// ȸ������ �����ϱ�
		case 5:		// ȸ�� �˻��ϱ�
		case 6:		// �����ϱ�
			saveDataFile(pmember, memberNum);
			printf("�����Ͱ� ����Ǿ����ϴ�. \n\n\n");
			break;
		case 7:		// �����ϱ�
			while (1)
			{
				printf("�����͸� �����Ͻðڽ��ϱ�?(y,n) \n");
				scanf("%c", &offChoice);
				if (offChoice == 'y' || offChoice == 'Y')
				{
					saveDataFile(pmember, memberNum);
					printf("�����Ͱ� ����Ǿ����ϴ�. \n");
					break;
				}
				else if (offChoice == 'n' || offChoice == 'N')
					break;
				else
					printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���. \n");
				fflush(stdin);
			}
			printf("���α׷��� �����մϴ�. \n");
			break;		//	switch�� ����
		}
		if (userChoice == 7)
			break;		// while�� ����
	}

}


int main(void)
{
	startInterface();	// ����ȭ�� �ҷ�����
	return 0;
}
