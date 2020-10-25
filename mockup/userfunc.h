#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:6328)
#pragma warning(disable:4477)
// warning ¸¹À¸¸é ³ªÁß¿¡ Å«ÀÏ³¯ ¼öµµ ÀÖÀ¸´Ï±î ÀÖ¾îµµ »ó°ü¾ø´Â warning ²¨³ù½À´Ï´Ù.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <Windows.h>
#include <time.h>
<<<<<<< HEAD
#include <ctype.h>	//isalpha »ç¿ë

=======
>>>>>>> ì½”ë“œ ê²€?¬í•¨???‰ë‚´ë§??ˆìŠµ?ˆë‹¤.

// ¹öÆÛ»çÀÌÁî Á¤ÀÇ
#define BUFF_SIZE (128)
#define FILE_BUFF (1024)
// ÄÜ¼Ö °¡¿îµ¥ Á¤·Ä
#define PRINTCEN(str) wprintf(L"%*s\n",48+wcslen(str)/2,str) 
// ÄÜ¼Ö ¿À¸¥ÂÊ Á¤·Ä
#define PRINTRIGHT(str) wprintf(L"%75s\n",str) 
// ÄÜ¼Ö ¿ŞÂÊ Á¤·Ä
#define PRINTLEFT(str) wprintf(L"%-s\n",str) 
// Ä³¸¯ÅÍ·Î ¼±(?)±ß±â
#define DRAWLINE(ch) for(int i=0;i<100;i++)printf("%c",ch); printf("\n") 

// ±Û·Î¹ú ¹öÆÛ¿¡ ÀÔ·Â ¹Ş±â
#define GET_G_INPUT if (fgets(g_buffer, BUFF_SIZE, stdin) == NULL)	\
{	perror("fgetws() failed");\
	fprintf(stderr, "file: %s,line %d", __FILE__, __LINE__);\
	system("pause");	exit(1);\
}\

// °èÁÂ¹øÈ£·Î ±Û·Î¹ú °æ·Î¹öÆÛ ¼³Á¤
//#define SET_G_PATH(input) 

// µÚ·Î°¡±â Ã¼Å©
#define Q_CHECK(returnvalue) if (*g_buffer == ':')\
{	if (*(g_buffer + 1) == 'q')\
	{	wprintf(L"µÚ·Î°¡±â :q\n");\
		system("pause");\
		return returnvalue;	\
	}\
}\

#define TEST_ON (1)
#define TEST_OFF (0)

typedef enum { T1 = 0, T2, T3 }eAccType; // ÀÌ¸§Áş±â Èûµé¾î¼­...
char g_buffer[BUFF_SIZE]; // ±Û·Î¹ú ÀÔ·Â ¹öÆÛ
char g_filebuff[FILE_BUFF]; // ³¢¿ö¾²±â¿ë
wchar_t g_wpath[MAX_PATH]; // ±Û·Î¹ú °æ·Î ÀÔ·Â ¹öÆÛ
FILE* f_MemberFile; // È¸¿øÁ¤º¸ ÆÄÀÏ½ºÆ®¸²
FILE* f_AccountList; // °èÁÂ¸®½ºÆ® ÆÄÀÏ½ºÆ®¸²
wchar_t* tempwcp; // È¤½Ã ³ªÁß¿¡ ¾µÁö ¸ô¶ó¼­ Æ÷ÀÎÅÍ·Î ¸¸µé¾ú½À´Ï´Ù.

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
void EraseSpace(char* []);
int strToInquiry(char* str, char* accNum,const eAccType type);
int strToAccInfo(char* str, char* accNum, const eAccType type);
int strToFSInfo(char* str, char* accNum, const eAccType type);
int setError(FILE* f_accList);
int checkAcc(FILE* f_target);
int checkFix(FILE* f_target);
int checkSav(FILE* f_setSav);
int setInterest(FILE* f_target);

