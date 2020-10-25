#include "userfunc.h"

int strToInquiry(char* str,char* accNum,const eAccType type)
{
	assert(str != NULL && accNum != NULL && "str or accNum points NULL");
	
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
	if (strcmp(accNum, attributes[2]) != 0 && type!=T1) // 계좌 골라서 출력
	{
		goto ESCAPE;
	}
	// 타입체크
	switch(type)
	{
		case T1:
			for (int i = 0; i < 6; i++)
			{
				wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
				for (int j = 0; j < strlen(attributes[i]) + 1; j++)
				{
					mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
				}
			}
			if (attributes[4] == 'i')
			{
				wprintf(L"< %s >/ %16s: %s/ 금액: %s (입금)/ 잔액: %s\n",
					wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
			}
			else if (attributes[4] == 'o')
			{
				wprintf(L"< %s >/ %16s: %s/ 금액: %s (출금)/ 잔액: %s\n",
					wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
			}
			else
			{
				fprintf(stderr, "In and Out account wrong in printing history\n");
				system("pause");
				break;
			}
			break;
		case T2:
			for (int i = 0; i < 5; i++)
			{
				wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
				for (int j = 0; j < strlen(attributes[i]) + 1; j++)
				{
					mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
				}
			}
			wprintf(L"< %s >/ %16s: %s/ 만기해지시 금액: %s / 현재 금액: %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
			break;
		case T3:
			for (int i = 0; i < 5; i++)
			{
				wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
				for (int j = 0; j < strlen(attributes[i]) + 1; j++)
				{
					mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
				}
			}
			wprintf(L"< %s >/ %16s: %s/ 최대 월 납입액: %s / 현재 금액: %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
			break;
		default:
			fprintf(stderr, "Something wrong in printing history.\n");
			system("pause");
			break;

	}

	for (int k = 0; k < 5; k++)
	{
		free(wtemps[k]);
		wtemps[k] = NULL;
	}
	if (type == T1)
	{
		free(wtemps[5]);
wtemps[5] = NULL;
	}
	return 1;
ESCAPE:
	return 0;
}
int strToAccInfo(char* str, char* accNum, const eAccType type)
{
	assert(str != NULL && accNum != NULL && "str or accNum points NULL");

	char* piter = str;
	char* attributes[6] = { NULL, };
	char*** autoTransferInfo = NULL;
	char*** autoTemp = NULL;
	wchar_t* wtemps[6] = { NULL, 0 };
	wchar_t*** wATInfo = NULL;

	int i = 0;
	size_t l = 0;
	int autoFlags = 0;
	size_t autoNums = 0;



	//계좌 정보 뽑기
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
				autoFlags = 1;
				autoNums = 1;
				break;
			}
		}
	}
	//자동이체 정보 뽑기
	l = autoNums - 1;
	while (autoFlags == 1 && *piter != '\n')
	{
		if (autoTransferInfo == NULL)
		{
			autoTransferInfo = (char***)malloc(sizeof(char**) * autoNums);
			assert(autoTransferInfo != NULL && "\nautoTransferInfo memory allocation failed\n");
			autoTransferInfo[0] = (char**)malloc(sizeof(char*) * 4);
			assert(autoTransferInfo[0] != NULL && "\nautoTransferInfo[0] memory allocation failed\n");
		}
		else if (l == autoNums - 2)
		{
			l++;
			autoTemp = (char***)realloc(autoTransferInfo, sizeof(char**) * autoNums);
			assert(autoTransferInfo != NULL && "\nautoTransferInfo memory 're'allocation failed\n");
			autoTransferInfo = autoTemp;
			autoTemp = NULL;
			autoTransferInfo[l] = (char**)malloc(sizeof(char*) * 4);
			assert(autoTransferInfo[l] != NULL && "\nautoTransferInfo[l] memory allocation failed\n");
		}
		autoTransferInfo[l][0] = piter;
		i = 0;
		while (*piter != '\n')
		{
			piter++;
			if (*piter == '|')
			{
				*piter = '\0';
				if (i % 4 != 0)
				{
					autoTransferInfo[l][i++] = piter + 1;
				}
				else
				{
					autoNums++;
					break;
				}
			}
		}
	}
ESCAPE:

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
	for (int j = 0; j < strlen(attributes[i]) + 1; j++)
	{
		mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
	}
	wprintf(L"< 입출금 계좌 >/ %16s: %s/ 잔액: %s 이체한도 %s(일)/%s(월)\n",
		wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5]);
	if (autoNums != 0)
	{
		wATInfo = (wchar_t***)malloc(sizeof(wchar_t**) * autoNums);
		for (int u = 0; u < autoNums; u++)
		{
			wATInfo[u] = (wchar_t**)malloc(sizeof(wchar_t*) * 4);
			for (int y = 0; y < 4; y++){
				wATInfo[u][y] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(autoTransferInfo[u][y]) + 1));
				for (int t = 0; t < strlen(autoTransferInfo[u][y]) + 1; t++)
				{
					mbtowc(wATInfo[u][y] + t, autoTransferInfo[u][y] + t, MB_CUR_MAX);
				}
			}
			wprintf(L"[자동이체 정보]: 매월 %s일 %s (만)원을 %s 계좌에 %s 만큼 보냅니다.\n",
				wATInfo[u][0], wATInfo[u][1], wATInfo[u][2], wATInfo[u][3]);
		}
	}


	for (int k = 0; k < 5; k++)
	{
		free(wtemps[k]);
		wtemps[k] = NULL;
	}
	if (type == T1)
	{
		free(wtemps[5]);
		wtemps[5] = NULL;
	}
	for (int f1 = 0; f1 < autoNums; f1++)
	{
		for (int f2 = 0; f2 < 4; f2++)
		{
			free(wATInfo[f1][f2]);
			free(autoTransferInfo[f1][f2]);
			wATInfo[f1][f2] = NULL;
			autoTransferInfo[f1][f2] = NULL;
		}
		free(wATInfo[f1]);
		free(autoTransferInfo[f1]);
		wATInfo[f1] = NULL;
		autoTransferInfo[f1] = NULL;
	}
	wATInfo = NULL;
	autoTransferInfo = NULL;

	return autoNums;
}
void strToFSInfo(char* str, char* accNum, const eAccType type)
{

}
