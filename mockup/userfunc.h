#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:6328)
#pragma warning(disable:4477)
// warning ������ ���߿� ū�ϳ� ���� �����ϱ� �־ ������� warning �������ϴ�.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <Windows.h>
#include <locale.h>

#define BUFF_SIZE (128)
wchar_t g_buffer[BUFF_SIZE];

// �ܼ� ��� ����
#define PRINTCEN(str) wprintf(L"%*s\n",48+wcslen(str)/2,str) 
// �ܼ� ������ ����
#define PRINTRIGHT(str) wprintf(L"%100s\n",str) 
// �ܼ� ���� ����
#define PRINTLEFT(str) wprintf(L"%-s\n",str) 
// ĳ���ͷ� ��(?)�߱�
#define DRAWLINE(ch) for(int i=0;i<100;i++)printf("%c",ch); printf("\n") 

// �۷ι� ���ۿ� �Է� �ޱ�
#define GET_G_INPUT if (fgetws(g_buffer, BUFF_SIZE, stdin) == NULL)	\
{	perror("fgetws() failed");\
	fprintf(stderr, "file: %s,line %d", __FILE__, __LINE__);\
	system("pause");	exit(1);\
}\

// �ڷΰ��� üũ
#define Q_CHECK(returnvalue) if (*g_buffer == ':')\
{	if (*(g_buffer + 1) == 'q')\
	{	wprintf(L"�ڷΰ��� :q\n");\
		system("pause");\
		return returnvalue;	\
	}\
}\

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

