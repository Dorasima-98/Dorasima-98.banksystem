#pragma warning(disable:4996)

#include "menus.h"

int main(void)
{
	
	initConsole();
	startMenu();
	while(1)
	{
		mainMenu();
	}

	
   
	return 0;
}

void initConsole()
{
	system("mode con: cols=100 lines=20");
	condition_t.condition = 0;
	condition_t.bits.fileclosed = 1;
}

