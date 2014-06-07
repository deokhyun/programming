#ifndef __MEMBER_MANAGEMENT_H
#define __MEMBER_MANAGEMENT_H





typedef struct{		// 회원 정보를 기록할 구조체 선언
	char id[10];
	char name[20];
	char address[50];
	char phoneNum[20];
} DATA;


int countMemberNum(void);
int countMaxId(DATA *pmember, int memberNum);
int validName(DATA *pmember, int memberNum);
int validAddress(DATA *pmember, int memberNum);
int validPhoneNum(DATA *pmember, int memberNum);
void addMember(DATA *pmember, int memberNum);
void loadDataFile(DATA *pmember, int memberNum);
void printMemberInfo(DATA *pmember, int memberNum);
void saveDataFile(DATA *pmember, int memberNum);
void deleteMember(DATA *pmember, int memberNum);
void modifyMember(DATA *pmember, int memberNum);
void findMember(DATA *pmember, int memberNum);
void printMainMenu(void);
void startInterface(void);




#endif


