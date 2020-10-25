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



// 버퍼사이즈 정의
#define BUFF_SIZE (128)
// 콘솔 가운데 정렬
#define PRINTCEN(str) wprintf(L"%*s\n",48+wcslen(str)/2,str) 
// 콘솔 오른쪽 정렬
#define PRINTRIGHT(str) wprintf(L"%75s\n",str) 
// 콘솔 왼쪽 정렬
#define PRINTLEFT(str) wprintf(L"%-s\n",str) 
// 캐릭터로 선(?)긋기
#define DRAWLINE(ch) for(int i=0;i<100;i++)printf("%c",ch); printf("\n") 

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
char g_buffer[BUFF_SIZE]; // 글로벌 입력 버퍼
wchar_t g_wpath[MAX_PATH]; // 글로벌 경로 입력 버퍼
FILE* f_MemberFile; // 회원정보 파일스트림
FILE* f_AccountList; // 계좌리스트 파일스트림
wchar_t* tempwcp; // 혹시 나중에 쓸지 몰라서 포인터로 만들었습니다.

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

