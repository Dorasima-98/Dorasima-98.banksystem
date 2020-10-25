#include "userfunc.h"

int strToInquiry(char* str, char* accNum, const eAccType type)
{
	assert(str != NULL && accNum != NULL && "str or accNum points NULL");

	char* piter = str;
	char* attributes[6] = { NULL,0 };
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;

	//계좌 내역 뽑기
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
	if (strcmp(accNum, attributes[2]) != 0 && type != T1) // 계좌 골라서 출력
	{
		goto ESCAPE;
	}
	// 타입체크
	switch (type)
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
		if (attributes[4][0] == 'i')
		{
			wprintf(L"< %s >/ %16s: %s/ 금액: %s (입금)/ 잔액: %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
		}
		else if (attributes[4][0] == 'o')
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
		wprintf(L"< %s >/ %16s: %s/ 최대 월 납입액: %s/ 현재 금액: %s\n",
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
	char*** autoTemp1 = NULL;
	char** autoTemp2 = NULL;
	wchar_t* wtemps[6] = { NULL, };
	wchar_t** wATInfo = NULL;

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
			//autoTemp1 = (char***)realloc(autoTransferInfo, sizeof(char**) * autoNums);
			autoTemp1 = (char***)malloc(sizeof(char**) * autoNums);
			assert(autoTransferInfo != NULL && "\nautoTransferInfo memory 're'allocation failed\n");
			memcpy(autoTemp1, autoTransferInfo, sizeof(char**) * autoNums - 1);
			autoTransferInfo = autoTemp1;
			autoTemp1 = NULL;
			for (int d = 0; d < autoNums - 1; d++)
			{
				autoTemp2 = (char**)malloc(sizeof(char*) * 4);
				memcpy(autoTemp2, autoTransferInfo[d], sizeof(char*) * 4);
				autoTransferInfo[d] = autoTemp2;
				autoTemp2 = NULL;
				//autoTemp2 = (char**)realloc(autoTransferInfo,sizeof(char*) * 4);
				//autoTransferInfo[d] = autoTemp2;
				//autoTemp2 = NULL;
			}
			autoTransferInfo[autoNums - 1] = (char**)malloc(sizeof(char*) * 4);
			assert(autoTransferInfo[l] != NULL && "\nautoTransferInfo[l] memory allocation failed\n");
		}
		autoTransferInfo[l][0] = ++piter;
		i = 0;
		while (1)
		{
			if (i % 4 != 0 || i == 0)
			{
				piter++;
				if (*piter == '|')
				{
					*piter = '\0';
					if (i % 4 != 0 || i == 0)
					{
						autoTransferInfo[l][++i] = piter + 1;
					}
				}
			}
			else
			{
				autoNums++;
				break;
			}
		}
		if (*(piter + 1) == '\n')
		{
			break;
		}
	}
ESCAPE:

	for (int i = 0; i < 6; i++)
	{
		wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
		for (int j = 0; j < strlen(attributes[i]) + 1; j++)
		{
			mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
		}
	}
	wprintf(L"< 입출금 계좌 >/ %16s: %s/ 잔액: %s 이체한도 %s(일)/%s(월)\n",
		wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5]);
	if (autoNums != 0)
	{
		wATInfo = (wchar_t**)malloc(sizeof(wchar_t*) * 4);

		for (int u = 0; u < autoNums - 1; u++)
		{
			for (int y = 0; y < 4; y++)
			{
				wATInfo[y] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(autoTransferInfo[u][y]) + 1));
				for (int t = 0; t < strlen(autoTransferInfo[u][y]) + 1; t++)
				{
					mbtowc(wATInfo[y] + t, autoTransferInfo[u][y] + t, MB_CUR_MAX);
				}
			}
			wprintf(L"[자동이체 정보]: 매월 %s일 %s (만)원을 %s 계좌에 %s 만큼 보냅니다.\n",
				wATInfo[0], wATInfo[1], wATInfo[2], wATInfo[3]);
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
	for (int c = 0; c < 4; c++)
	{
		free(wATInfo[c]);
		wATInfo[c] = NULL;
	}
	free(wATInfo);
	wATInfo = NULL;
	for (int f1 = 0; f1 < autoNums - 2; f1++)
	{
		free(autoTransferInfo[f1]);
	}

	free(autoTransferInfo);
	autoTransferInfo = NULL;

	return autoNums;
}
int strToFSInfo(char* str, char* accNum, const eAccType type)
{
	assert(str != NULL && accNum != NULL && "str or accNum points NULL");


	char* piter = str;
	char* attributes[7] = { NULL, };
	wchar_t* wtemps[7] = { NULL, };

	int k = 0;
	int flags = 0;

	//계좌 정보 뽑기
	attributes[k++] = piter;
	while (*piter != '\n')
	{
		piter++;
		if (*piter == '|')
		{
			*piter = '\0';
			if (k <7)
			{
				attributes[k++] = piter + k;
			}
			else
			{
				if (strcmp(attributes[1], accNum) == 0)
				{
					flags = 1;
					break;
				}
				else
				{
					k = 0;
					attributes[k++] = ++piter;
					continue;
				}
			}
		}
	}
	if (flags == 1)
	{
		for (int i = 0; i < 7; i++)
		{
			wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(attributes[i]) + 1));
			for (int j = 0; j < strlen(attributes[i]) + 1; j++)
			{
				mbtowc(wtemps[i] + j, attributes[i] + j, MB_CUR_MAX);
			}
		}
		if (type == T2)
		{
			wprintf(L"< 예금 계좌 >/ %16s: %s/ 잔액: %s 남은 신청기간 %s(일) 이자율: %s 해지시 금액 %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5], wtemps[6]);
		}
		else
		{
			wprintf(L"< 적금 계좌 >/ %16s: %s/ 잔액: %s 남은 신청기간 %s(일) 이자율: %s 해지시 금액 %s\n",
				wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5], wtemps[6]);
		}
		for (int f = 0; f < 7; f++)
		{
			free(wtemps[f]);
		}
		return 1;
	}
	return 0;
}
