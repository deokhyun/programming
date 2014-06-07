/*
�ۼ��� : 141076 ������
�ۼ��� : 2014.06.07
��  �� :	���α׷��� ���� �⸻����(3��)
ȸ�������������α׷��� ȸ������, ȸ���߰�, ����, ȸ���˻�, ȸ������, ȸ������ ��� ����
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

	for (i = 0; i < memberNum; i++)		// char ���� ������ ���̵� int �� ������ �ٲ���
		transferId[i] = atoi(pmember[i].id);
	for (i = 0; i < memberNum; i++)		// ���̵��� �ִ밪 ã��
	{
		if (maxId < transferId[i])
			maxId = transferId[i];
	}
	return maxId;		// ���̵� �� �ִ밪 ��ȯ
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
	if (len == 0)
		return 0;
	if (pmember[memberNum].phoneNum[3] != '-')		// �׹�° ��ġ�� �������� ���ԵǴ��� Ȯ��
		return 0;
	if (!(pmember[memberNum].phoneNum[7] == '-' || pmember[memberNum].phoneNum[8] == '-'))		// 8��° ��ġ �Ǵ� 9��° ��ġ�� �������� ���ԵǴ��� Ȯ��
		return 0;
	if (!(pmember[memberNum].phoneNum[12] == '\0' || pmember[memberNum].phoneNum[13] == '\0'))		// 13��° ��ġ �Ǵ� 14��° ��ġ�� �Էµ� ���� ������ Ȯ��
		return 0;
	return 1;
}


void addMember(DATA *pmember, int memberNum)		// ���ο� ȸ�� �߰� ���
{
	int goMain = 0;
	printf("�߰��� ȸ���� ������ ������ �Է��ϼ��� \n");
	itoa(countMaxId(pmember, memberNum) + 1, member[memberNum].id, 10);		// ���̵��� �ִ밪���� 1 ū ���� �űԾ��̵� �ڵ� ����
	printf("���̵�(�ڵ�����): %d \n", countMaxId(pmember, memberNum) + 1);		
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

	printf("%s\t%s\t%s\t%s\n", pmember[memberNum].id, pmember[memberNum].name, pmember[memberNum].address, pmember[memberNum].phoneNum);
	printf("\t ���ο� ȸ�� ������ ��� �Ǿ����ϴ�. \n");

	while (1)
	{
		printf("���� ȭ������ �̵��Ͻ÷��� (1)�� �Է��ϼ���: ");		// ����ȭ������ �̵��ϴ� ���
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
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


void saveDataFile(DATA *pmember, int memberNum)		// txt ���Ͽ� ������
{
	int i;

	FILE *f = fopen("data.txt", "wt");
	if (f == NULL){
		puts("���Ͽ��� ����!");
	}

	for (i = 1; i < memberNum; i++)		// tab ������ ȸ�� ������ �б�
		fprintf(f, "%s\t%s\t%s\t%s\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

	fclose(f);
}


void deleteMember(DATA *pmember, int memberNum)		// ȸ�� ���� ��� �Լ�
{
	int delChoice;		// ������� ������ �Է¹޴� ����
	int delMemberNum = -1;		// ������ ȸ���� �����ϴ��� �����ϴ� ����
	int i = 0;
	int goMain = 0;
	char delStr[20];		// ������ ȸ�� �˻� �� ȸ�������� �Է¹޴� ���ڿ�
	while (1)
	{
		printf("\t ������ ȸ���� � ������ ã���ðڽ��ϱ�? \n");
		printf("\n\n");
		printf("\t 1. ���̵� \n");
		printf("\t 2. �̸� \n");
		printf("\t 3. ��ȭ��ȣ \n");
		printf("\t 4. ��� \n");
		printf("\t    : ");
		scanf_s("%d", &delChoice);
		if (!(delChoice >= 1 && delChoice <= 4))
		{
			printf("\t �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���. \n");
			fflush(stdin);
		}
		switch (delChoice)
		{
		case 1:		// ���̵�� ������ ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� ���̵� : ");
				fflush(stdin);
				gets(delStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].id, delStr))		// �Է¹��� ���ڿ��� ���� ȸ�� ������ ��
						delMemberNum = i;
					i++;
				}
				if (delMemberNum == -1)
					printf("\t ã���ô� ���̵� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[delMemberNum].id, pmember[delMemberNum].name, pmember[delMemberNum].address, pmember[delMemberNum].phoneNum);
					printf("\t �����Ͻ� ȸ���� ��������� �����Ǿ����ϴ�. \n");
					break;
				}
			}
			for (i = delMemberNum; i < memberNum; i++)		// ȸ�� ���� �� ���� �� ���� �� �پ� �÷��� ��迭
				pmember[i] = pmember[i + 1];
			break;
		case 2:		// �̸����� ������ ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� �̸� : ");
				fflush(stdin);
				gets(delStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].name, delStr))
						delMemberNum = i;
					i++;
				}
				if (delMemberNum == -1)
					printf("\t ã���ô� �̸��� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[delMemberNum].id, pmember[delMemberNum].name, pmember[delMemberNum].address, pmember[delMemberNum].phoneNum);
					printf("\t �����Ͻ� ȸ���� ��������� �����Ǿ����ϴ�. \n");
					break;
				}
			}
			for (i = delMemberNum; i < memberNum; i++)
				pmember[i] = pmember[i + 1];
			break;
		case 3:		// �ڵ��� ��ȣ�� ������ ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� �ڵ��� ��ȣ : ");
				fflush(stdin);
				gets(delStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].phoneNum, delStr))
						delMemberNum = i;
					i++;
				}
				if (delMemberNum == -1)
					printf("\t ã���ô� �ڵ��� ��ȣ�� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[delMemberNum].id, pmember[delMemberNum].name, pmember[delMemberNum].address, pmember[delMemberNum].phoneNum);
					printf("\t �����Ͻ� ȸ���� ��������� �����Ǿ����ϴ�. \n");
					break;
				}
			}
			for (i = delMemberNum; i < memberNum; i++)
				pmember[i] = pmember[i + 1];
			break;
		case 4:
			break;
		}
		if (delChoice >= 1 && delChoice <= 4)
			break;
	}
	while (1)
	{
		printf("���� ȭ������ �̵��Ͻ÷��� (1)�� �Է��ϼ���: ");		// ����ȭ������ �̵��ϴ� ���
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
}


void modifyMember(DATA *pmember, int memberNum)		// Ư�� ȸ�� �˻� �� ȸ�������� �����ϴ� �Լ�
{
	int modifyChoice;
	int modifyMemberNum = -1;
	int i = 0;
	int goMain = 0;
	char modifyStr[50];
	while (1)
	{
		printf("\t ��ȸ�� ȸ���� � ������ ã���ðڽ��ϱ�? \n");
		printf("\n\n");
		printf("\t 1. ���̵� \n");
		printf("\t 2. �̸� \n");
		printf("\t 3. ��ȭ��ȣ \n");
		printf("\t 4. ��� \n");
		printf("\t    : ");
		scanf_s("%d", &modifyChoice);
		if (!(modifyChoice >= 1 && modifyChoice <= 4))
		{
			printf("\t �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���. \n");
			fflush(stdin);
		}
		switch (modifyChoice)
		{
		case 1:		// ���̵�� ��ȸ�� ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� ���̵� : ");
				fflush(stdin);
				gets(modifyStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].id, modifyStr))		// �Է¹��� ȸ�� ������ ���� ȸ�� ������ ��
						modifyMemberNum = i;
					i++;
				}
				if (modifyMemberNum == -1)
					printf("\t ã���ô� ���̵� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 2:		// �̸����� ��ȸ�� ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� �̸� : ");
				fflush(stdin);
				gets(modifyStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].name, modifyStr))
						modifyMemberNum = i;
					i++;
				}
				if (modifyMemberNum == -1)
					printf("\t ã���ô� �̸��� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 3:		// �ڵ��� ��ȣ�� ��ȸ�� ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� �ڵ��� ��ȣ : ");
				fflush(stdin);
				gets(modifyStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].phoneNum, modifyStr))
						modifyMemberNum = i;
					i++;
				}
				if (modifyMemberNum == -1)
					printf("\t ã���ô� �ڵ��� ��ȣ�� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 4:
			break;
		}
		if (modifyChoice >= 1 && modifyChoice <= 4)
			break;
	}

	modifyChoice = -1;
	while (1)
	{
		printf("\t � �����͸� �����Ͻðڽ��ϱ�? \n");
		printf("\n\n");
		printf("\t 1. �̸� \n");
		printf("\t 2. �ּ� \n");
		printf("\t 3. �ڵ��� ��ȣ \n");
		printf("\t 4. ��� \n");
		printf("\t    : ");
		scanf_s("%d", &modifyChoice);
		if (!(modifyChoice >= 1 && modifyChoice <= 4))
		{
			printf("\t �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���. \n");
			fflush(stdin);
		}
		switch (modifyChoice)
		{
		case 1:		// ȸ�� �̸� ����
			printf("\t '%s'��/�� �������� �����Ͻðڽ��ϱ�? : ", pmember[modifyMemberNum].name);
			fflush(stdin);
			gets(modifyStr);
			for (i = 0; i < 50;i++)
				pmember[modifyMemberNum].name[i] = modifyStr[i];		// ���� ȸ�� ������ �Է¹��� ȸ�� ������ ���� 
			printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
			printf("\n���� �Ϸ�Ǿ����ϴ�. \n");
			break;
		case 2:		// ȸ�� �ּ� ����
			printf("\t '%s'��/�� �������� �����Ͻðڽ��ϱ�? : ", pmember[modifyMemberNum].address);
			fflush(stdin);
			gets(modifyStr);
			for (i = 0; i < 50; i++)
				pmember[modifyMemberNum].address[i] = modifyStr[i];
			printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
			printf("\n���� �Ϸ�Ǿ����ϴ�. \n");
			break;
		case 3:		// ȸ�� �ڵ��� ��ȣ ����
			printf("\t '%s'��/�� �������� �����Ͻðڽ��ϱ�? : ", pmember[modifyMemberNum].phoneNum);
			fflush(stdin);
			gets(modifyStr);
			for (i = 0; i < 50; i++)
				pmember[modifyMemberNum].phoneNum[i] = modifyStr[i];
			printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
			printf("\n���� �Ϸ�Ǿ����ϴ�. \n");
			break;
		case 4:
			break;
		}
		if (modifyChoice >= 1 && modifyChoice <= 4)
			break;
	}
	while (1)
	{
		printf("���� ȭ������ �̵��Ͻ÷��� (1)�� �Է��ϼ���: ");		// ����ȭ������ �̵��ϴ� ���
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
}




void findMember(DATA *pmember, int memberNum)		// ȸ���� �˻��ϴ� �Լ�
{
	int findChoice;
	int findMemberNum = -1;
	int i = 0;
	int goMain = 0;
	char findStr[20];
	while (1)
	{
		printf("\t ��ȸ�� ȸ���� � ������ ã���ðڽ��ϱ�? \n");
		printf("\n\n");
		printf("\t 1. ���̵� \n");
		printf("\t 2. �̸� \n");
		printf("\t 3. ��ȭ��ȣ \n");
		printf("\t 4. ��� \n");
		printf("\t    : ");
		scanf_s("%d", &findChoice);
		if (!(findChoice >= 1 && findChoice <= 4))
		{
			printf("\t �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���. \n");
			fflush(stdin);
		}
		switch (findChoice)
		{
		case 1:		// ���̵�� ��ȸ�� ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� ���̵� : ");
				fflush(stdin);
				gets(findStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].id, findStr))
						findMemberNum = i;
					i++;
				}
				if (findMemberNum == -1)
					printf("\t ã���ô� ���̵� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("\n%s\t%s\t%s\t%s\n", pmember[findMemberNum].id, pmember[findMemberNum].name, pmember[findMemberNum].address, pmember[findMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 2:		// �̸����� ��ȸ�� ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� �̸� : ");
				fflush(stdin);
				gets(findStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].name, findStr))
						findMemberNum = i;
					i++;
				}
				if (findMemberNum == -1)
					printf("\t ã���ô� �̸��� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("\n%s\t%s\t%s\t%s\n", pmember[findMemberNum].id, pmember[findMemberNum].name, pmember[findMemberNum].address, pmember[findMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 3:		// �ڵ��� ��ȣ�� ��ȸ�� ȸ�� �˻�
			while (1)
			{
				printf("\t ã���� �ڵ��� ��ȣ : ");
				fflush(stdin);
				gets(findStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].phoneNum, findStr))
						findMemberNum = i;
					i++;
				}
				if (findMemberNum == -1)
					printf("\t ã���ô� �ڵ��� ��ȣ�� �����ϴ�. �ٽ� �Է��� �ּ���. \n");
				else
				{
					printf("\n%s\t%s\t%s\t%s\n", pmember[findMemberNum].id, pmember[findMemberNum].name, pmember[findMemberNum].address, pmember[findMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 4:
			break;
		}
		if (findChoice >= 1 && findChoice <= 4)
			break;
	}
	while (1)
	{
		printf("\n���� ȭ������ �̵��Ͻ÷��� (1)�� �Է��ϼ���: ");		// ����ȭ������ �̵��ϴ� ���
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
}



void printMainMenu(void)		// ���� �޴��� ����ϴ� �Լ�
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
			deleteMember(pmember, memberNum);
			memberNum--;
			break;
		case 4:		// ȸ������ �����ϱ�
			modifyMember(pmember, memberNum);
			break;
		case 5:		// ȸ�� �˻��ϱ�
			findMember(pmember, memberNum);
			break;
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
