#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:6328)
#pragma warning(disable:4477)
// warning 많으면 나중에 큰일날 수도 있으니까 있어도 상관없는 warning 꺼놨습니다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <Windows.h>
#include <time.h>
#include <ctype.h>	//isalpha 사용


// 버퍼사이즈 정의
#define BUFF_SIZE (128)
#define FILE_BUFF (1024)
// 콘솔 가운데 정렬
#define PRINTCEN(str) wprintf(L"%*s\n",72+wcslen(str)/2,str) 
// 콘솔 오른쪽 정렬
#define PRINTRIGHT(str) wprintf(L"%75s\n",str) 
// 콘솔 왼쪽 정렬
#define PRINTLEFT(str) wprintf(L"%-s\n",str) 
// 캐릭터로 선(?)긋기
#define DRAWLINE(ch) for(int i=0;i<150;i++)printf("%c",ch); printf("\n") 

// 글로벌 버퍼에 입력 받기
#define GET_G_INPUT if (fgets(g_buffer, BUFF_SIZE, stdin) == NULL)	\
{	perror("fgetws() failed");\
	fprintf(stderr, "file: %s,line %d", __FILE__, __LINE__);\
	system("pause");	exit(1);\
}\

// 계좌번호로 글로벌 경로버퍼 설정
//#define SET_G_PATH(input) 

// 뒤로가기 체크
#define Q_CHECK(returnvalue) if (*g_buffer == ':')\
{	if (*(g_buffer + 1) == 'q')\
	{	wprintf(L"뒤로가기 :q\n");\
		system("pause");\
		return returnvalue;	\
	}\
}\

#define TEST_ON (1)
#define TEST_OFF (0)

typedef enum { T1 = 0, T2, T3 }eAccType; // 이름짓기 힘들어서...
typedef struct
{
	char IO_day[11];
	char IO_name[17];
	char IO_othernum[8];
	char IO_money[13];
	char IO_io[2];
	char IO_balance[13];
}IOinqury_t;
typedef struct
{
	char IO_name[17];
	char IO_mynum[8];
	char IO_balance[13];
	char IO_Passwords[5];
	char IO_dayLimits[7];
	char IO_monthLimits[8];

	char*** autoattributes;
	int autoNums;
}IOattributes_malloc_t;
typedef struct
{
	eAccType FS_type;
	char FS_day[11];
	char FS_name[17];
	char FS_mynum[8];
	char FS_money[10];
	char FS_balance[13];
}FSinqury_t;
typedef struct
{
	eAccType type;
	char FS_name[17];
	char FS_mynum[8];
	char FS_received[13];
	char FS_Passwords[5];
	char FS_remainService[3];
	char FS_interest[4];
	char FS_balance[13];
}FSattributes_t;
char g_buffer[BUFF_SIZE]; // 글로벌 입력 버퍼
char g_filebuff[FILE_BUFF]; // 끼워쓰기용
char g_userID[17];
wchar_t g_wpath[MAX_PATH]; // 글로벌 경로 입력 버퍼
wchar_t* tempwcp; // 혹시 나중에 쓸지 몰라서 포인터로 만들었습니다.


char** g_userAccountsList;
char*** g_allAccountsListAndName; // 처음 써봅니다 ㄷㄷㄷㄷ
extern int g_userBank;
extern int g_userALNums;
extern int g_allALANNums;
extern FILE* f_MemberFile; // 회원정보 파일스트림
extern FILE* f_AccountList; // 계좌리스트 파일스트림

int startMenu();
void registerMenu();
int loginMenu();

int checkDigit(const char* ap_string);
int checkAlnum(const char* ap_string);
int checkID(const char* ap_string);
int checkName(const char* ap_string);
int checkPW(const char* ap_string);
int checkSpace(const char* ap_string); // 문자열 중간 공백 체크 (있으면 1 반환, 없으면 0 반환)
void EraseSpace(char* ap_string); 
char* trim_malloc(char* des, const char* src); // 문자열 좌우 공백 모두 삭제 함수
char* ltrim_malloc(char* des, const  char* src); // 문자열 좌측 공백 제거 함수
char* rtrim_malloc(char* des, const  char* src); // 문자열 우측 공백 제거 함수

int serviceMenu();
void makeAccountMenu();
void fixedDepositAndSavingsMenu();
void fixedDeposit();
void Savings();
void inquiryAndCancel();
void transferMenu();
void atmMenu();
void historyInquiry();


/*요기있는거는...아마 될걸요?*/
int strToIOiq(const char* str, IOinqury_t* ioacc);
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum);
// 이친구는 자동이체 내역때문에 내부보셔야 합니다.
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc); 
int strToFSatt(const char* str, FSattributes_t* fsacc, const char* accNum);

/*요 4개는 쓰면 안됩니다.*/
void printIOinquiry(const IOinqury_t* ioacc);
void printFSinquiry(const FSinqury_t* fsacc);
void printIOatt(const IOattributes_malloc_t* ioacc);
void printFSatt(FSattributes_t* fsacc);

void freeIOattriutes(IOattributes_malloc_t* ioacc);


int setError();
int checkIO(FILE* f_target);
int checkFix(FILE* f_target);
int checkSav(FILE* f_setSav);
int setInterest(FILE* f_target);

int checkDupID(const char* ID);
int checkDupPW(const char* ID,const char* PW);
int setBankByID(const char* ID);
int checkDupAN(const char* input);
int setAccListByID_malloc(const char* ID);
int setAccListOfAll_malloc();
eAccType getAccType(const char* AccNum);