/*
작성자 : 141076 정덕현
작성일 : 2014.06.07
제  목 :	프로그래밍 연습 기말과제(3차)
회원정보관리프로그램의 회원보기, 회원추가, 저장, 회원검색, 회원수정, 회원삭제 기능 구현
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

	for (i = 0; i < memberNum; i++)		// char 변수 형태의 아이디를 int 형 변수로 바꿔줌
		transferId[i] = atoi(pmember[i].id);
	for (i = 0; i < memberNum; i++)		// 아이디의 최대값 찾기
	{
		if (maxId < transferId[i])
			maxId = transferId[i];
	}
	return maxId;		// 아이디 중 최대값 반환
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
	if (len == 0)
		return 0;
	if (pmember[memberNum].phoneNum[3] != '-')		// 네번째 위치에 하이픈이 포함되는지 확인
		return 0;
	if (!(pmember[memberNum].phoneNum[7] == '-' || pmember[memberNum].phoneNum[8] == '-'))		// 8번째 위치 또는 9번째 위치에 하이픈이 포함되는지 확인
		return 0;
	if (!(pmember[memberNum].phoneNum[12] == '\0' || pmember[memberNum].phoneNum[13] == '\0'))		// 13번째 위치 또는 14번째 위치에 입력된 값이 없는지 확인
		return 0;
	return 1;
}


void addMember(DATA *pmember, int memberNum)		// 새로운 회원 추가 기능
{
	int goMain = 0;
	printf("추가할 회원의 데이터 정보를 입력하세요 \n");
	itoa(countMaxId(pmember, memberNum) + 1, member[memberNum].id, 10);		// 아이디의 최대값보다 1 큰 수로 신규아이디 자동 생성
	printf("아이디(자동생성): %d \n", countMaxId(pmember, memberNum) + 1);		
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

	printf("%s\t%s\t%s\t%s\n", pmember[memberNum].id, pmember[memberNum].name, pmember[memberNum].address, pmember[memberNum].phoneNum);
	printf("\t 새로운 회원 정보가 등록 되었습니다. \n");

	while (1)
	{
		printf("메인 화면으로 이동하시려면 (1)을 입력하세요: ");		// 메인화면으로 이동하는 기능
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
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


void saveDataFile(DATA *pmember, int memberNum)		// txt 파일에 저장기능
{
	int i;

	FILE *f = fopen("data.txt", "wt");
	if (f == NULL){
		puts("파일오픈 실패!");
	}

	for (i = 1; i < memberNum; i++)		// tab 단위로 회원 정보를 읽기
		fprintf(f, "%s\t%s\t%s\t%s\n", pmember[i].id, pmember[i].name, pmember[i].address, pmember[i].phoneNum);

	fclose(f);
}


void deleteMember(DATA *pmember, int memberNum)		// 회원 삭제 기능 함수
{
	int delChoice;		// 사용자의 선택을 입력받는 변수
	int delMemberNum = -1;		// 삭제할 회원이 존재하는지 점검하는 변수
	int i = 0;
	int goMain = 0;
	char delStr[20];		// 삭제할 회원 검색 시 회원정보를 입력받는 문자열
	while (1)
	{
		printf("\t 삭제할 회원을 어떤 정보로 찾으시겠습니까? \n");
		printf("\n\n");
		printf("\t 1. 아이디 \n");
		printf("\t 2. 이름 \n");
		printf("\t 3. 전화번호 \n");
		printf("\t 4. 취소 \n");
		printf("\t    : ");
		scanf_s("%d", &delChoice);
		if (!(delChoice >= 1 && delChoice <= 4))
		{
			printf("\t 잘못 입력하셨습니다. 다시 입력해 주세요. \n");
			fflush(stdin);
		}
		switch (delChoice)
		{
		case 1:		// 아이디로 삭제할 회원 검색
			while (1)
			{
				printf("\t 찾으실 아이디 : ");
				fflush(stdin);
				gets(delStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].id, delStr))		// 입력받은 문자열과 기존 회원 데이터 비교
						delMemberNum = i;
					i++;
				}
				if (delMemberNum == -1)
					printf("\t 찾으시는 아이디가 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[delMemberNum].id, pmember[delMemberNum].name, pmember[delMemberNum].address, pmember[delMemberNum].phoneNum);
					printf("\t 선택하신 회원의 등록정보가 삭제되었습니다. \n");
					break;
				}
			}
			for (i = delMemberNum; i < memberNum; i++)		// 회원 삭제 후 다음 줄 부터 한 줄씩 올려서 재배열
				pmember[i] = pmember[i + 1];
			break;
		case 2:		// 이름으로 삭제할 회원 검색
			while (1)
			{
				printf("\t 찾으실 이름 : ");
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
					printf("\t 찾으시는 이름이 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[delMemberNum].id, pmember[delMemberNum].name, pmember[delMemberNum].address, pmember[delMemberNum].phoneNum);
					printf("\t 선택하신 회원의 등록정보가 삭제되었습니다. \n");
					break;
				}
			}
			for (i = delMemberNum; i < memberNum; i++)
				pmember[i] = pmember[i + 1];
			break;
		case 3:		// 핸드폰 번호로 삭제할 회원 검색
			while (1)
			{
				printf("\t 찾으실 핸드폰 번호 : ");
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
					printf("\t 찾으시는 핸드폰 번호가 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[delMemberNum].id, pmember[delMemberNum].name, pmember[delMemberNum].address, pmember[delMemberNum].phoneNum);
					printf("\t 선택하신 회원의 등록정보가 삭제되었습니다. \n");
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
		printf("메인 화면으로 이동하시려면 (1)을 입력하세요: ");		// 메인화면으로 이동하는 기능
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
}


void modifyMember(DATA *pmember, int memberNum)		// 특정 회원 검색 후 회원정보를 수정하는 함수
{
	int modifyChoice;
	int modifyMemberNum = -1;
	int i = 0;
	int goMain = 0;
	char modifyStr[50];
	while (1)
	{
		printf("\t 조회할 회원을 어떤 정보로 찾으시겠습니까? \n");
		printf("\n\n");
		printf("\t 1. 아이디 \n");
		printf("\t 2. 이름 \n");
		printf("\t 3. 전화번호 \n");
		printf("\t 4. 취소 \n");
		printf("\t    : ");
		scanf_s("%d", &modifyChoice);
		if (!(modifyChoice >= 1 && modifyChoice <= 4))
		{
			printf("\t 잘못 입력하셨습니다. 다시 입력해 주세요. \n");
			fflush(stdin);
		}
		switch (modifyChoice)
		{
		case 1:		// 아이디로 조회할 회원 검색
			while (1)
			{
				printf("\t 찾으실 아이디 : ");
				fflush(stdin);
				gets(modifyStr);
				i = 0;
				while (i < memberNum)
				{
					if (!strcmp(pmember[i].id, modifyStr))		// 입력받은 회원 정보와 기존 회원 정보를 비교
						modifyMemberNum = i;
					i++;
				}
				if (modifyMemberNum == -1)
					printf("\t 찾으시는 아이디가 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 2:		// 이름으로 조회할 회원 검색
			while (1)
			{
				printf("\t 찾으실 이름 : ");
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
					printf("\t 찾으시는 이름이 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 3:		// 핸드폰 번호로 조회할 회원 검색
			while (1)
			{
				printf("\t 찾으실 핸드폰 번호 : ");
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
					printf("\t 찾으시는 핸드폰 번호가 없습니다. 다시 입력해 주세요. \n");
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
		printf("\t 어떤 데이터를 수정하시겠습니까? \n");
		printf("\n\n");
		printf("\t 1. 이름 \n");
		printf("\t 2. 주소 \n");
		printf("\t 3. 핸드폰 번호 \n");
		printf("\t 4. 취소 \n");
		printf("\t    : ");
		scanf_s("%d", &modifyChoice);
		if (!(modifyChoice >= 1 && modifyChoice <= 4))
		{
			printf("\t 잘못 입력하셨습니다. 다시 입력해 주세요. \n");
			fflush(stdin);
		}
		switch (modifyChoice)
		{
		case 1:		// 회원 이름 수정
			printf("\t '%s'을/를 무엇으로 수정하시겠습니까? : ", pmember[modifyMemberNum].name);
			fflush(stdin);
			gets(modifyStr);
			for (i = 0; i < 50;i++)
				pmember[modifyMemberNum].name[i] = modifyStr[i];		// 기존 회원 정보를 입력받은 회원 정보로 수정 
			printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
			printf("\n수정 완료되었습니다. \n");
			break;
		case 2:		// 회원 주소 수정
			printf("\t '%s'을/를 무엇으로 수정하시겠습니까? : ", pmember[modifyMemberNum].address);
			fflush(stdin);
			gets(modifyStr);
			for (i = 0; i < 50; i++)
				pmember[modifyMemberNum].address[i] = modifyStr[i];
			printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
			printf("\n수정 완료되었습니다. \n");
			break;
		case 3:		// 회원 핸드폰 번호 수정
			printf("\t '%s'을/를 무엇으로 수정하시겠습니까? : ", pmember[modifyMemberNum].phoneNum);
			fflush(stdin);
			gets(modifyStr);
			for (i = 0; i < 50; i++)
				pmember[modifyMemberNum].phoneNum[i] = modifyStr[i];
			printf("%s\t%s\t%s\t%s\n", pmember[modifyMemberNum].id, pmember[modifyMemberNum].name, pmember[modifyMemberNum].address, pmember[modifyMemberNum].phoneNum);
			printf("\n수정 완료되었습니다. \n");
			break;
		case 4:
			break;
		}
		if (modifyChoice >= 1 && modifyChoice <= 4)
			break;
	}
	while (1)
	{
		printf("메인 화면으로 이동하시려면 (1)을 입력하세요: ");		// 메인화면으로 이동하는 기능
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
}




void findMember(DATA *pmember, int memberNum)		// 회원을 검색하는 함수
{
	int findChoice;
	int findMemberNum = -1;
	int i = 0;
	int goMain = 0;
	char findStr[20];
	while (1)
	{
		printf("\t 조회할 회원을 어떤 정보로 찾으시겠습니까? \n");
		printf("\n\n");
		printf("\t 1. 아이디 \n");
		printf("\t 2. 이름 \n");
		printf("\t 3. 전화번호 \n");
		printf("\t 4. 취소 \n");
		printf("\t    : ");
		scanf_s("%d", &findChoice);
		if (!(findChoice >= 1 && findChoice <= 4))
		{
			printf("\t 잘못 입력하셨습니다. 다시 입력해 주세요. \n");
			fflush(stdin);
		}
		switch (findChoice)
		{
		case 1:		// 아이디로 조회할 회원 검색
			while (1)
			{
				printf("\t 찾으실 아이디 : ");
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
					printf("\t 찾으시는 아이디가 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("\n%s\t%s\t%s\t%s\n", pmember[findMemberNum].id, pmember[findMemberNum].name, pmember[findMemberNum].address, pmember[findMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 2:		// 이름으로 조회할 회원 검색
			while (1)
			{
				printf("\t 찾으실 이름 : ");
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
					printf("\t 찾으시는 이름이 없습니다. 다시 입력해 주세요. \n");
				else
				{
					printf("\n%s\t%s\t%s\t%s\n", pmember[findMemberNum].id, pmember[findMemberNum].name, pmember[findMemberNum].address, pmember[findMemberNum].phoneNum);
					break;
				}
			}
			break;
		case 3:		// 핸드폰 번호로 조회할 회원 검색
			while (1)
			{
				printf("\t 찾으실 핸드폰 번호 : ");
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
					printf("\t 찾으시는 핸드폰 번호가 없습니다. 다시 입력해 주세요. \n");
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
		printf("\n메인 화면으로 이동하시려면 (1)을 입력하세요: ");		// 메인화면으로 이동하는 기능
		scanf_s("%d", &goMain);
		if (goMain == 1)
			break;
	}
	system("cls");
}



void printMainMenu(void)		// 메인 메뉴를 출력하는 함수
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
			deleteMember(pmember, memberNum);
			memberNum--;
			break;
		case 4:		// 회원정보 수정하기
			modifyMember(pmember, memberNum);
			break;
		case 5:		// 회원 검색하기
			findMember(pmember, memberNum);
			break;
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
