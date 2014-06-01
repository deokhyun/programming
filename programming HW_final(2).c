/*
작성자 : 141076 정덕현
작성일 : 2014.06.01
제  목 :	프로그래밍 연습 기말과제(2차)
회원정보관리프로그램의 회원보기, 회원추가, 저장 기능 구현
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <windows.h>
#include "programming final.h"
#define MAX_SIZE	(1000)

DATA member[MAX_SIZE];


int countMemberNum(void){		// 등록된 회원수를 체크하는 함수(맨 위 인적정보 항목 포함)

	int memberNum = 0;
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



void addMember(DATA *pmember, int memberNum)
{
	printf("추가할 회원의 데이터 정보를 입력하세요 \n");
	printf("아이디: ");
	fflush(stdin);
	gets(pmember[memberNum].id);
	printf("이름: ");
	fflush(stdin);
	gets(pmember[memberNum].name);
	printf("주소: ");
	fflush(stdin);
	gets(pmember[memberNum].address);
	printf("연락처: ");
	fflush(stdin);
	gets(pmember[memberNum].phoneNum);
}


void loadDataFile(DATA *pmember, int memberNum)
{
	int i;

	FILE *f = fopen("data.txt", "rt");
	if (f == NULL){
		puts("파일오픈 실패!");
	}
	
	for (i = 0; i < memberNum; i++)		// tab 단위로 회원 정보를 읽기
		fscanf(f, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

	fclose(f);
}



 



void printMemberInfo(DATA *pmember, int memberNum)		// 등록 회원 전체를 출력하는 함수(등록 회원 수를 매개변수로 전달)
{		
	int i;
	int goMain = 0;

	for (i = 0; i < memberNum; i++)		// 읽어온 회원 정보를 출력
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


saveDataFile(DATA *pmember, int memberNum)
{
	int i; 

	FILE *f = fopen("data.txt", "wt");
	if (f == NULL){
		puts("파일오픈 실패!");
	}

	for (i = 0; i < memberNum; i++)		// tab 단위로 회원 정보를 읽기
		fprintf(f, "%s\t%s\t%s\t%s\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

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



void startInterface()// 메인화면 제공 기능
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
			printMemberInfo(pmember, memberNum);		// 등록 회원 수를 매개변수로 받는 회원 보기 함수 
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
				if (offChoice == 'y')
				{
					saveDataFile(pmember, memberNum);
					printf("데이터가 저장되었습니다. \n");
					break;
				}
				else if (offChoice == 'n')
					break;
				else
					printf("잘못된 값을 입력하였습니다. 다시 입력하세요. \n");
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
