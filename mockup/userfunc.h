#pragma once
#pragma warning(disable:4996)
//#pragma warning(disable:4477) // ���������� * �Ҷ� int �� �Ѱܾߵ�
//#pragma warning(disable:6031) // ��ȯ�� ����
//#pragma warning(disable:4267) // ĳ���� ������ �ҽ�
// warning ������ ���߿� ū�ϳ� ���� �����ϱ� �־ ������� warning �������ϴ�.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <Windows.h>
#include <time.h>
#include <ctype.h>	//isalpha ���


// ���ۻ����� ����
#define BUFF_SIZE (256)
#define FILE_BUFF (1024)
// �ܼ� ��� ����
#define PRINTCEN(str) wprintf(L"%*s\n",72+(int)wcslen(str)/2,str) 
// �ܼ� ������ ����
#define PRINTRIGHT(str) wprintf(L"% 90s\n",str) 
// �ܼ� ���� ����
#define PRINTLEFT(str) wprintf(L"%-s\n",str) 
// ĳ���ͷ� ��(?)�߱�
#define DRAWLINE(ch) for(int i=0;i<150;i++)printf("%c",ch); printf("\n") 

// �۷ι� ���ۿ� �Է� �ޱ�
#define GET_G_INPUT if (fgets(g_buffer, BUFF_SIZE, stdin) == NULL)	\
{	perror("fgetws() failed");\
	fprintf(stderr, "file: %s,line %d", __FILE__, __LINE__);\
	system("pause");	exit(1);\
}\

/* �ڷΰ��� üũ
#define Q_CHECK(returnvalue) if (*g_buffer == ':')\
{	if (*(g_buffer + 1) == 'q')\
	{	wprintf(L"�ڷΰ��� :q\n");\
		system("pause");\
		return returnvalue;	\
	}\
}\

*/

#define TEST_ON (1)
#define TEST_OFF (0)

typedef enum { T1 = 0, T2, T3 }eAccType; // �̸����� ����...

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
	char FS_money[13]; // ������ ���� ����� ���ɾ�, ������ ���� �� �ִ� ���Ծ� �Դϴ�.
	char FS_Passwords[5];
	char FS_remainService[3];
	char FS_interest[4];
	char FS_balance[13];
}FSattributes_t;

char g_buffer[BUFF_SIZE]; // �۷ι� �Է� ����
char g_filebuff[FILE_BUFF]; // ���������
char g_filebuff2[FILE_BUFF];
char g_tempbuff[FILE_BUFF];
char g_userID[17];
wchar_t g_wpath[MAX_PATH]; // �۷ι� ��� �Է� ����
wchar_t* g_tempwcp; // Ȥ�� ���߿� ���� ���� �����ͷ� ��������ϴ�.


extern int g_userBank; // �α����� ����� �����ڵ� �Դϴ�.

char** g_userAccountsList; // �α����� ����ڰ� ������ �ִ� ����(��ȣ) �����Դϴ�.
char*** g_allAccountsListAndName; // ���α׷��� ������ �ִ� ����(��ȣ, �̸�) �� ������ �ִ� �����Դϴ�. 

extern int g_userALNums; // �α����� ����� ������ �ִ� ������ �����Դϴ�.
extern int g_allALANNums; // ���α׷��� �ִ� ������ �����Դϴ�.

extern FILE* f_MemberFile; // ȸ������ ���Ͻ�Ʈ��
extern FILE* f_AccountList; // ���¸���Ʈ ���Ͻ�Ʈ��

//�۷ι� �ð� �����Դϴ�. ���� 24�ð� ���� �ѳ����� �ʰ���.
extern int g_year;
extern int g_month;
extern int g_day;
extern time_t g_time;

int startMenu();
void registerMenu();
int loginMenu();

/* ��Ģ üũ */
int checkDigit(const char* ap_string);
int checkAlnum(const char* ap_string); 
int checkID(const char* ap_string);
int checkName(const char* ap_string); 
int checkPW(const char* ap_string); 
int checkSpace(const char* ap_string); 
int checkATMorTransfer(char* AccNum, char** items, int delnums);

/* �ߺ� üũ*/
int checkDupID(const char* ID);
int checkDupPW(const char* ID, const char* PW);
int setBankByID(const char* ID);
int checkDupAN(const char* input);
char* getAccountName(const char* AccNum, char* AccName);
int checkExistAcc(const char* AccNum);

/* ��Ÿ ��� */
void EraseSpace(char* ap_string); 
char* trim_malloc(char* des, const char* src); 
char* ltrim_malloc(char* des, const  char* src);
char* rtrim_malloc(char* des, const  char* src); 
int eraseAuto(const char* accNum, const char* toerase, int num);

/* ���� ��� */
int serviceMenu();
void makeAccountMenu();
void fixedDepositAndSavingsMenu();
void fixedDepositAndSavings(int intype);
void inquiryAndCancel();
void transferMenu();
void atmMenu();
void historyInquiry();

/* ���� ��� */
int moneyInIO(const char* desNum, const char* srcNum, long money);
int moneyOutIO(const char* desNum, const char* srcNum, long money,int flag);
int moneyInFS(const char* accNum, long money, int service);

/* ���� ��� */
void printIOinquiry(const IOinqury_t* ioacc);
int printFSinquiry(const FSinqury_t* fsacc);
void printIOatt(const IOattributes_malloc_t* ioacc);
void printFSatt(const FSattributes_t* fsacc);

/*������ ����*/
int strToIOiq(const char* str, IOinqury_t* ioacc);
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum);
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc); 
int strToFSatt(const char* str, FSattributes_t* fsacc, const char* accNum);
void freeIOattriutes(IOattributes_malloc_t* ioacc);
eAccType getAccType(const char* AccNum);

/*���� üũ*/
int setError();
int checkIO(FILE* f_target);
int checkFix(FILE* f_target);
int checkSav(FILE* f_setSav);
void setInterest();
int setFSInterest(FILE* f_accfile, const char* AccNum);
int setAutoTransfer();
int setAutoIOTransfer(FILE* f_io);

/*���� �����*/
int setAccListByID_malloc(const char* ID);
int setAccListOfAll_malloc(); 
