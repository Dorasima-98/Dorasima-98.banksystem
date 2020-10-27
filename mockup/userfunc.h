#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:6328)
#pragma warning(disable:4477)
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
#define BUFF_SIZE (128)
#define FILE_BUFF (1024)
// �ܼ� ��� ����
#define PRINTCEN(str) wprintf(L"%*s\n",72+wcslen(str)/2,str) 
// �ܼ� ������ ����
#define PRINTRIGHT(str) wprintf(L"%75s\n",str) 
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

// ���¹�ȣ�� �۷ι� ��ι��� ����
//#define SET_G_PATH(input) 

// �ڷΰ��� üũ
#define Q_CHECK(returnvalue) if (*g_buffer == ':')\
{	if (*(g_buffer + 1) == 'q')\
	{	wprintf(L"�ڷΰ��� :q\n");\
		system("pause");\
		return returnvalue;	\
	}\
}\

#define TEST_ON (1)
#define TEST_OFF (0)

typedef enum { T1 = 0, T2, T3 }eAccType; // �̸����� ����...
char g_buffer[BUFF_SIZE]; // �۷ι� �Է� ����
char g_filebuff[FILE_BUFF]; // ���������
char g_userID[17];
wchar_t g_wpath[MAX_PATH]; // �۷ι� ��� �Է� ����
wchar_t* tempwcp; // Ȥ�� ���߿� ���� ���� �����ͷ� ��������ϴ�.


char** g_userAccountsList;
char*** g_allAccountsListAndName; // ó�� �Ế�ϴ� ��������
extern int g_userBank;
extern int g_userALNums;
extern int g_allALANNums;
extern FILE* f_MemberFile; // ȸ������ ���Ͻ�Ʈ��
extern FILE* f_AccountList; // ���¸���Ʈ ���Ͻ�Ʈ��

int startMenu();
void registerMenu();
int loginMenu();

int checkDigit(const char* ap_string);
int checkAlnum(const char* ap_string);
int checkID(const char* ap_string);
int checkName(const char* ap_string);
int checkPW(const char* ap_string);
int checkSpace(const char* ap_string); // ���ڿ� �߰� ���� üũ (������ 1 ��ȯ, ������ 0 ��ȯ)
void EraseSpace(char* ap_string); 
char* trim_malloc(char* des, const char* src); // ���ڿ� �¿� ���� ��� ���� �Լ�
char* ltrim_malloc(char* des, const  char* src); // ���ڿ� ���� ���� ���� �Լ�
char* rtrim_malloc(char* des, const  char* src); // ���ڿ� ���� ���� ���� �Լ�

int serviceMenu();
void makeAccountMenu();
void fixedDepositAndSavingsMenu();
void fixedDeposit();
void Savings();
void inquiryAndCancel();
void transferMenu();
void atmMenu();
void historyInquiry();

int strToInquiry(char* str, char* accNum,const eAccType type);
int strToAccInfo(char* str, char* accNum, const eAccType type);
int strToFSInfo(char* str, char* accNum, const eAccType type);

int setError(FILE* f_accList);
int checkAcc(FILE* f_target);
int checkFix(FILE* f_target);
int checkSav(FILE* f_setSav);
int setInterest(FILE* f_target);

int checkDupID(const char* ID);
int checkDupPW(const char* PW);
int setBankByID(const char* ID);
int checkDupAN(const char* input);
int setAccListByID_malloc(const char* ID);