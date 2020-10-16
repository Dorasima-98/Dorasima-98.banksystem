#pragma warning(disable:4996)

#include "userfunc.h"

void setting();

int main(void)
{
	
	setting();
	while (startMenu())
	{
		while (serviceMenu());
	}
	fwprintf(stdout, L"프로그램 종료합니다. 프바\n");
	system("pause");
	return 0;
}

void setting()
{
	system("mode con: cols=100 lines=20");
	setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");
}

