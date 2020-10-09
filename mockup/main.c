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
	fprintf(stdout, "terminate this program... bye!\n");
	system("pause");
	return 0;
}

void setting()
{
	system("mode con: cols=100 lines=20");
}

