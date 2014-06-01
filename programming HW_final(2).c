/*
�ۼ��� : 141076 ������
�ۼ��� : 2014.06.01
��  �� :	���α׷��� ���� �⸻����(2��)
ȸ�������������α׷��� ȸ������, ȸ���߰�, ���� ��� ����
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <windows.h>
#include "programming final.h"
#define MAX_SIZE	(1000)

DATA member[MAX_SIZE];


int countMemberNum(void){		// ��ϵ� ȸ������ üũ�ϴ� �Լ�(�� �� �������� �׸� ����)

	int memberNum = 0;
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



void addMember(DATA *pmember, int memberNum)
{
	printf("�߰��� ȸ���� ������ ������ �Է��ϼ��� \n");
	printf("���̵�: ");
	fflush(stdin);
	gets(pmember[memberNum].id);
	printf("�̸�: ");
	fflush(stdin);
	gets(pmember[memberNum].name);
	printf("�ּ�: ");
	fflush(stdin);
	gets(pmember[memberNum].address);
	printf("����ó: ");
	fflush(stdin);
	gets(pmember[memberNum].phoneNum);
}


void loadDataFile(DATA *pmember, int memberNum)
{
	int i;

	FILE *f = fopen("data.txt", "rt");
	if (f == NULL){
		puts("���Ͽ��� ����!");
	}
	
	for (i = 0; i < memberNum; i++)		// tab ������ ȸ�� ������ �б�
		fscanf(f, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

	fclose(f);
}



 



void printMemberInfo(DATA *pmember, int memberNum)		// ��� ȸ�� ��ü�� ����ϴ� �Լ�(��� ȸ�� ���� �Ű������� ����)
{		
	int i;
	int goMain = 0;

	for (i = 0; i < memberNum; i++)		// �о�� ȸ�� ������ ���
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


saveDataFile(DATA *pmember, int memberNum)
{
	int i; 

	FILE *f = fopen("data.txt", "wt");
	if (f == NULL){
		puts("���Ͽ��� ����!");
	}

	for (i = 0; i < memberNum; i++)		// tab ������ ȸ�� ������ �б�
		fprintf(f, "%s\t%s\t%s\t%s\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

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



void startInterface()// ����ȭ�� ���� ���
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
			printMemberInfo(pmember, memberNum);		// ��� ȸ�� ���� �Ű������� �޴� ȸ�� ���� �Լ� 
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
				if (offChoice == 'y')
				{
					saveDataFile(pmember, memberNum);
					printf("�����Ͱ� ����Ǿ����ϴ�. \n");
					break;
				}
				else if (offChoice == 'n')
					break;
				else
					printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���. \n");
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
