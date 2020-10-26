#pragma warning(disable:4996)

#include "userfunc.h"

void setting();
int Bank = 0;

int main(void)
{
	
	setting();
	while (startMenu())
	{
		while (serviceMenu());
	}
	fwprintf(stdout, L"프로그램 종료합니다. 프바\n");
	system("pause");

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
	f_MemberFile = _wfopen(L"C:\\banksystemlog\\members.txt", L"a+");
	f_AccountList = _wfopen(L"C:\\banksystemlog\\accounts.txt", L"a+");
	assert(f_MemberFile != NULL && f_AccountList != NULL&&"\nfile opening is failed.");

	if (setError(f_AccountList) == 1)
	{
		fclose(f_MemberFile);
		fclose(f_AccountList);
		f_MemberFile = NULL;
		f_AccountList = NULL;

		system("pause");
		exit(0);
	}
}

