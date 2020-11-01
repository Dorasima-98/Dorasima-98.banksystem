#pragma warning(disable:4996)

#include "userfunc.h"
int Bank;

int g_year;
int g_month;
int g_day;
time_t g_time;

FILE* f_MemberFile; // 회원정보 파일스트림
FILE* f_AccountList; // 계좌리스트 파일스트림

void setting();

int main(void)
{
	
	setting();
	//while (startMenu())
	{
		while (serviceMenu());
	}
	fwprintf(stdout, L"프로그램 종료합니다. 프바\n");
	system("pause");


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0;j < g_allALANNums; j++)
		{
			free(g_allAccountsListAndName[i][j]);
			g_allAccountsListAndName[i][j] = NULL;

		}
		free(g_allAccountsListAndName[i]);
		g_allAccountsListAndName[i] = NULL;
	}
	free(g_allAccountsListAndName);
	g_allAccountsListAndName = NULL;

	fclose(f_MemberFile);
	fclose(f_AccountList);
	f_MemberFile = NULL;
	f_AccountList = NULL;
	return 0;
}

void setting()
{
	system("mode con: cols=150 lines=30");
	setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");

	//시간 입력
	struct tm* pTS;
	g_time = time(NULL);
	pTS = localtime(&g_time);

	g_year = (pTS->tm_year) + 1900;
	g_month = (pTS->tm_mon);
	g_day = pTS->tm_mday;
	//g_day = 31;

	//printf("%d / %d / %d\n", g_year, g_month, g_day);
	//system("pause");

	//윈도우 제공 함수
	//폴더만들기...(아래 은행별로 나눈것은 필요할지 모르겠습니다.)
	CreateDirectory(L"C:\\banksystemlog", NULL); 

	CreateDirectory(L"C:\\banksystemlog\\01", NULL);
	CreateDirectory(L"C:\\banksystemlog\\02", NULL);
	CreateDirectory(L"C:\\banksystemlog\\03", NULL);
	CreateDirectory(L"C:\\banksystemlog\\04", NULL);
	CreateDirectory(L"C:\\banksystemlog\\05", NULL);

	assert(ERROR_PATH_NOT_FOUND != GetLastError() && "\ndirectory cannot be created.");
	
	// 회원정보랑 계좌리스트는 그냥 열어두는걸로...
	f_MemberFile = _wfopen(L"C:\\banksystemlog\\members.txt", L"r+");
	f_AccountList = _wfopen(L"C:\\banksystemlog\\accounts.txt", L"r+");
	assert(f_MemberFile != NULL && f_AccountList != NULL&&"\nfile opening is failed.");

	//에러확인하는거긴한데...흠흠
	if (setError() == 1)
	{
		fclose(f_MemberFile);
		fclose(f_AccountList);
		f_MemberFile = NULL;
		f_AccountList = NULL;

		PRINTCEN(L"File open failed");

		system("pause");
		exit(0);
	}

	//글로벌 변수 초기화
	g_userBank = 0;
	g_userAccountsList = NULL;

	// 이자 붙일지 정하기
	time_t tempTime;
	int tempmonth;
	struct tm* tempTS;

	if (g_day == 31)
	{
		setInterest();
	}
	else if ((g_month == 2 && (g_day == 28 || g_day == 29)))
	{
		setInterest();
	}
	else if (g_day == 30)
	{
		tempTime = g_time + 86400; // 하루지나면
		//printf("%lld and %lld\n", g_time, tempTime);
		tempTS = localtime(&tempTime); 

		tempmonth = (tempTS->tm_mon)+1;
		if (tempmonth != g_month) // 달이변하는지 확인
		{
			setInterest();
		}
	}

	setAutoTransfer();
}

