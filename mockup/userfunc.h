#pragma once
#pragma warning(disable:4996)
//#pragma warning(disable:4477) // 서식지정자 * 할때 int 로 넘겨야됨
//#pragma warning(disable:6031) // 반환값 무시
//#pragma warning(disable:4267) // 캐스팅 데이터 소실
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
#define BUFF_SIZE (256)
#define FILE_BUFF (1024)
// 콘솔 가운데 정렬
#define PRINTCEN(str) wprintf(L"%*s\n",72+(int)wcslen(str)/2,str) 
// 콘솔 오른쪽 정렬
#define PRINTRIGHT(str) wprintf(L"% 90s\n",str) 
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

/* 뒤로가기 체크
#define Q_CHECK(returnvalue) if (*g_buffer == ':')\
{	if (*(g_buffer + 1) == 'q')\
	{	wprintf(L"뒤로가기 :q\n");\
		system("pause");\
		return returnvalue;	\
	}\
}\

*/

#define TEST_ON (1)
#define TEST_OFF (0)

typedef enum { T1 = 0, T2, T3 }eAccType; // 이름짓기 힘들어서...

typedef struct
{
	char IO_date[11];
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
	char IO_dateLimits[7];

	char*** autoattributes;
	int autoNums;
}IOattributes_malloc_t;
typedef struct
{
	eAccType FS_type;
	char FS_date[11];
	char FS_name[17];
	char FS_mynum[8];
	char FS_income[10];
	char FS_balance[13];
}FSinqury_t;
typedef struct
{
	eAccType type;
	char FS_name[17];
	char FS_mynum[8];
	char FS_money[13]; // 예금의 경우는 만기시 수령액, 적금은 남은 월 최대 납입액 입니다.
	char FS_Passwords[5];
	char FS_remainService[3];
	char FS_interest[4];
	char FS_balance[13];
}FSattributes_t;

char g_buffer[BUFF_SIZE]; // 글로벌 입력 버퍼
char g_filebuff[FILE_BUFF]; // 끼워쓰기용
char g_filebuff2[FILE_BUFF];
char g_tempbuff[FILE_BUFF];
char g_userID[17];
wchar_t g_wpath[MAX_PATH]; // 글로벌 경로 입력 버퍼
wchar_t* g_tempwcp; // 혹시 나중에 쓸지 몰라서 포인터로 만들었습니다.


extern int g_userBank; // 로그인한 사용자 은행코드 입니다.

char** g_userAccountsList; // 로그인한 사용자가 가지고 있는 계좌(번호) 버퍼입니다.
char*** g_allAccountsListAndName; // 프로그램이 가지고 있는 계좌(번호, 이름) 싹 가지고 있는 버퍼입니다. 

extern int g_userALNums; // 로그인한 사용자 가지고 있는 계좌의 갯수입니다.
extern int g_allALANNums; // 프로그램에 있는 계좌의 갯수입니다.

extern FILE* f_MemberFile; // 회원정보 파일스트림
extern FILE* f_AccountList; // 계좌리스트 파일스트림

//글로벌 시간 변수입니다. 설마 24시간 동안 켜놓지는 않겠죠.
extern int g_year;
extern int g_month;
extern int g_day;
extern time_t g_time;

int startMenu();
void registerMenu();
int loginMenu();

/* 규칙 체크 */
int checkDigit(const char* ap_string);
int checkAlnum(const char* ap_string); 
int checkID(const char* ap_string);
int checkName(const char* ap_string); 
int checkPW(const char* ap_string); 
int checkSpace(const char* ap_string); 
int checkATMorTransfer(char* AccNum, char** items, int delnums);

/* 중복 체크*/
int checkDupID(const char* ID);
int checkDupPW(const char* ID, const char* PW);
int setBankByID(const char* ID);
int checkDupAN(const char* input);
char* getAccountName(const char* AccNum, char* AccName);
int checkExistAcc(const char* AccNum);

/* 기타 기능 */
void EraseSpace(char* ap_string); 
char* trim_malloc(char* des, const char* src); 
char* ltrim_malloc(char* des, const  char* src);
char* rtrim_malloc(char* des, const  char* src); 
int eraseAuto(const char* accNum, const char* toerase, int num);

/* 메인 기능 */
int serviceMenu();
void makeAccountMenu();
void fixedDepositAndSavingsMenu();
void fixedDepositAndSavings(int intype);
void inquiryAndCancel();
void transferMenu();
void atmMenu();
void historyInquiry();

/* 하위 기능 */
int moneyInIO(const char* desNum, const char* srcNum, long money);
int moneyOutIO(const char* desNum, const char* srcNum, long money,int flag);
int moneyInFS(const char* accNum, long money, int service);

/* 내역 출력 */
void printIOinquiry(const IOinqury_t* ioacc);
int printFSinquiry(const FSinqury_t* fsacc);
void printIOatt(const IOattributes_malloc_t* ioacc);
void printFSatt(const FSattributes_t* fsacc);

/*데이터 가공*/
int strToIOiq(const char* str, IOinqury_t* ioacc);
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum);
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc); 
int strToFSatt(const char* str, FSattributes_t* fsacc, const char* accNum);
void freeIOattriutes(IOattributes_malloc_t* ioacc);
eAccType getAccType(const char* AccNum);

/*문법 체크*/
int setError();
int checkIO(FILE* f_target);
int checkFix(FILE* f_target);
int checkSav(FILE* f_setSav);
void setInterest();
int setFSInterest(FILE* f_accfile, const char* AccNum);
int setAutoTransfer();
int setAutoIOTransfer(FILE* f_io);

/*버퍼 만들기*/
int setAccListByID_malloc(const char* ID);
int setAccListOfAll_malloc(); 
