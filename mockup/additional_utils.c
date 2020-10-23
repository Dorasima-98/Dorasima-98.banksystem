#include "userfunc.h"

void strToInquiry(char* str)
{
	char* piter = str;
	char* attributes[6] = { NULL,0 };
	wchar_t* wtemps[6] = { NULL, 0};
	int i = 0;

	attributes[i++] = piter;
	while (*piter != '\n')
	{
		piter++;
		if (*piter == '|')
		{
			*piter = '\0';
			if (i < 5)
			{
				attributes[i++] = piter + 1;
			}
			else
			{
				attributes[i] = piter + 1;
			}
		}
		
	}
	*piter = '\0';

	for (int i = 0; i < 6; i++)
	{
		wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
		for (int j = 0; j < strlen(attributes[i]) + 1; j++)
		{
			mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
		}
	}
	wprintf(L"< %s >/ %s: %s/ ฑÝพื: %s ( %s )/ ภÜพื: %s\n",
		wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4], wtemps[5]);

	for (int k = 0; k < 6; k++)
	{
		free(wtemps[k]);
	}

	return;
}
