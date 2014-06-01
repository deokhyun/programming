/*
작성자 : 141076 정덕현
작성일 : 2014.06.01
제  목 :	프로그래밍 연습 기말과제(2차)
회원정보관리프로그램의 회원보기, 회원추가, 저장 기능 구현
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


int countMemberNum(void)		// 등록된 회원수를 체크하는 함수(맨 위 인적정보 항목 포함)
{		

	int memberNum = 1;
	char str[100];

	FILE *f = fopen("data.txt", "rt");
	if (f == NULL){
		puts("파일오픈 실패!");
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


int countMaxId(DATA *pmember, int memberNum)		// 신규회원의 아이디를 생성하기 위해 기등록 아이디 중 가장 큰 수를 검색하는 함수
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


int validName(DATA *pmember, int memberNum)		// 등록하고자 하는 이름이 유효한지 확인
{
	int len = strlen(pmember[memberNum].name);
	int chkName = atoi(pmember[memberNum].name);		// 숫자가 포함될 경우 유효하지 않은 이름

	if (len == 0)
		return 0;
	if (chkName > 0)
		return 0;
	return 1;
}


int validAddress(DATA *pmember, int memberNum)		// 등록하고자 하는 주소가 유효한지 확인
{
	int len = strlen(pmember[memberNum].address);

	if (len == 0)
		return 0;
	else
		return 1;
}


int validPhoneNum(DATA *pmember, int memberNum)		// 등록하고자 하는 핸드폰 번호가 유효한지 확인
{
	int len = strlen(pmember[memberNum].phoneNum);
	int i;
	if (len == 0)
		return 0;
	if (pmember[memberNum].phoneNum[3] != '-')		// 네번째 위치에 하이픈이 포함되는지 확인
		return 0;
	if (!(pmember[memberNum].phoneNum[7] == '-' || pmember[memberNum].phoneNum[8] == '-'))		// 8번째 위치 또는 9번째 위치에 하이픈이 포함되는지 확인
		return 0;
	return 1;
}


void addMember(DATA *pmember, int memberNum)		// 새로운 회원 추가 기능
{
	printf("추가할 회원의 데이터 정보를 입력하세요 \n");
	itoa(countMaxId(pmember, memberNum) + 1, member[memberNum].id, 10);
	printf("아이디(자동생성): %d \n", countMaxId(pmember, memberNum) + 1);		// 아이디는 자동 생성
	while (1)
	{
		printf("이름: ");
		fflush(stdin);
		gets(pmember[memberNum].name);

		if (validName(pmember, memberNum) == 0)
			printf("유효하지 않은 이름입니다. \n");
		else
			break;
	}

	while (1)
	{
		printf("주소: ");
		fflush(stdin);
		gets(pmember[memberNum].address);
		if (validAddress(pmember, memberNum) == 0)
			printf("유효하지 않은 주소입니다. \n");
		else
			break;
	}

	while (1)
	{
		printf("핸드폰 번호: ");
		fflush(stdin);
		gets(pmember[memberNum].phoneNum);
		if (validPhoneNum(pmember, memberNum) == 0)
			printf("유효하지 않은 핸드폰 번호입니다. \n");
		else
			break;
	}
}






void loadDataFile(DATA *pmember, int memberNum)		// txt파일에서 데이터를 로드함
{
	int i;

	FILE *f = fopen("data.txt", "rt");
	if (f == NULL){
		puts("파일오픈 실패!");
	}

	for (i = 0; i <= memberNum; i++)		// tab 단위로 회원 정보를 읽기
	if (i == 0)
		continue;
	else
		fscanf(f, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);
	fclose(f);
}







void printMemberInfo(DATA *pmember, int memberNum)		// 등록 회원 전체를 출력하는 함수(구조체 포인터와 등록 회원 수를 매개변수로 전달)
{
	int i;
	int goMain = 0;

	//printf("    아이디\t회원이름\t\t회원주소\t\t 핸드폰번호\n");
	for (i = 1; i < memberNum; i++)		// 읽어온 회원 정보를 출력
		printf("%10s\t%7s\t\t%8s\t\t%7s \n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);
	printf("\n\n");
	while (1)
	{
		printf("메인 화면으로 이동하시려면 (1)을 입력하세요: ");		// 메인화면으로 이동하는 기능
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
		puts("파일오픈 실패!");
	}

	for (i = 1; i < memberNum; i++)		// tab 단위로 회원 정보를 읽기
		fprintf(f, "%s\t%s\t%s\t%s\n", &pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

	fclose(f);
}





void printMainMenu(void)
{
	printf("================================================\n");
	printf("============ 회원정보 관리 프로그램 ============\n");
	printf("================================================\n");
	printf("		1. 회원 보기 \n");
	printf("		2. 회원 등록하기 \n");
	printf("		3. 회원 삭제하기 \n");
	printf("		4. 회원정보 수정하기 \n");
	printf("		5. 회원 검색하기 \n");
	printf("		6. 저장하기 \n");
	printf("		7. 종료하기 \n");
	printf("================================================\n");
	printf("================================================\n");
}



void startInterface(void)		// 메인화면 제공 기능
{
	DATA *pmember = member;
	int userChoice = 0;		// 사용자가 기능 선택을 하는 변수 
	char offChoice;
	int memberNum = countMemberNum();
	loadDataFile(pmember, memberNum);

	while (1)
	{
		printMainMenu();

		do
		{
			printf("\n\n");
			printf("	원하는 기능을 선택해주세요: ");
			scanf_s("%d", &userChoice);
			fflush(stdin);

			if (userChoice<1 || userChoice > 7)
			{
				printf("\n");
				printf("	잘못된 번호를 입력하셨습니다! 다시 선택해주세요. \n");
			}
		} while (userChoice < 1 || userChoice > 7);
		system("cls");

		switch (userChoice)
		{
		case 1:		// 회원 보기
			printMemberInfo(pmember, memberNum);		
			break;
		case 2:		// 회원 등록하기
			addMember(pmember, memberNum);
			memberNum++;
			break;
		case 3:		// 회원 삭제하기
		case 4:		// 회원정보 수정하기
		case 5:		// 회원 검색하기
		case 6:		// 저장하기
			saveDataFile(pmember, memberNum);
			printf("데이터가 저장되었습니다. \n\n\n");
			break;
		case 7:		// 종료하기
			while (1)
			{
				printf("데이터를 저장하시겠습니까?(y,n) \n");
				scanf("%c", &offChoice);
				if (offChoice == 'y' || offChoice == 'Y')
				{
					saveDataFile(pmember, memberNum);
					printf("데이터가 저장되었습니다. \n");
					break;
				}
				else if (offChoice == 'n' || offChoice == 'N')
					break;
				else
					printf("잘못된 값을 입력하였습니다. 다시 입력하세요. \n");
				fflush(stdin);
			}
			printf("프로그램을 종료합니다. \n");
			break;		//	switch문 종료
		}
		if (userChoice == 7)
			break;		// while문 종료
	}

}


int main(void)
{
	startInterface();	// 메인화면 불러오기
	return 0;
}
