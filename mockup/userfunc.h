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



// ���ۻ����� ����
#define BUFF_SIZE (128)
// �ܼ� ��� ����
#define PRINTCEN(str) wprintf(L"%*s\n",48+wcslen(str)/2,str) 
// �ܼ� ������ ����
#define PRINTRIGHT(str) wprintf(L"%75s\n",str) 
// �ܼ� ���� ����
#define PRINTLEFT(str) wprintf(L"%-s\n",str) 
// ĳ���ͷ� ��(?)�߱�
#define DRAWLINE(ch) for(int i=0;i<100;i++)printf("%c",ch); printf("\n") 

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
wchar_t g_wpath[MAX_PATH]; // �۷ι� ��� �Է� ����
FILE* f_MemberFile; // ȸ������ ���Ͻ�Ʈ��
FILE* f_AccountList; // ���¸���Ʈ ���Ͻ�Ʈ��
wchar_t* tempwcp; // Ȥ�� ���߿� ���� ���� �����ͷ� ��������ϴ�.

int startMenu();
void registerMenu();
int loginMenu();

int serviceMenu();
void makeAccountMenu();
void fixedDepositAndSavingsMenu();
void fixedDeposit();
void Savings();
void inquiryAndCancel();
void transferMenu();
void atmMenu();
void historyInquiry();
void registerMenu();
int loginMenu();
void EraseSpace(char* []);
int strToInquiry(char* str, char* accNum,const eAccType type);
int strToAccInfo(char* str, char* accNum, const eAccType type);
//void strToFSInfo(char* str, char* accNum, const eAccType type);

