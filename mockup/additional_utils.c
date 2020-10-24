#include "userfunc.h"

void strToInquiry(char* str,AccType_t type)
{
	char* piter = str;
	char* attributes[6] = { NULL,0 };
	wchar_t* wtemps[6] = { NULL, 0};
	int i = 0;

	//나누기
	attributes[i++] = piter;
	while (*piter != '\n')
	{
		piter++;
		if (*piter == '|')
		{
			*piter = '\0';
			if (i < 6)
			{
				attributes[i++] = piter + 1;
			}
			else
			{
				break;
			}
		}
		
	}

	for (int i = 0; i < 6; i++)
	{
		wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
		for (int j = 0; j < strlen(attributes[i]) + 1; j++)
		{
			mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
		}
	}
	// 타입체크
	switch(type)
	{
		case T1:
			wprintf(L"< %s >/ %16s: %s/ 금액: %s ( %s )/ 잔액: %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4], wtemps[5]);
			break;
		case T2:
			wprintf(L"< %s >/ %16s: %s/ 만기해지시금액: %s ( %s )/ 금액: %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4], wtemps[5]);
			break;
		case T3:
			wprintf(L"< %s >/ %16s: %s/ 최대 월 납입액: %s ( %s )/ 금액: %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4], wtemps[5]);
			break;
		default:
			fprintf(stderr, "Something wrong in printing history.\n");
			system("pause");
			break;

	}

	

	for (int k = 0; k < 6; k++)
	{
		free(wtemps[k]);
	}

	return;
}
