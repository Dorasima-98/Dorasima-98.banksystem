#include "userfunc.h"

// 숫자 + 영문자가 아니면 1반환
int checkID(const char* ap_string)
{
	char* p_dest = ap_string;
	int IDcon[2] = { 0, };

	while (*p_dest != '\0')
	{
		if (isalnum(*p_dest) == 0)
		{
			return 1;
		}
		else if (isdigit(*p_dest) != 0)
		{
			IDcon[1] = 1;
		}
		else
		{
			IDcon[0] = 1;
		}
		p_dest++;
	}
	if (IDcon[0] && IDcon[1])
	{
		return 0;
	}
	return 1;
}
// 영문자 혹은 공백이 아니면 1반환
int checkName(const char* ap_string)
{
	char* p_dest = ap_string;

	while (*p_dest != '\0')
	{
		if (isalpha(*p_dest) == 0 && *p_dest !=' ')
		{
			return 1;
		}
		p_dest++;
	}
	return 0;
}
// 영어, 숫자, 특문 하나 씩 있어야함. 이상한거 들어오거나, 없으면 1반환
int checkPW(const char* ap_string)
{
	char* p_dest = ap_string;
	char SC[10] = {'!','@','#','$','%','^','&','*','(',')'};
	int PWcon[3] = { 0, };
	int i = 0;

	while (*p_dest != '\0')
	{
		if (isalpha(*p_dest) != 0)
		{
			PWcon[0] = 1;
		}
		else if(isdigit(*p_dest)!=0)
		{
			PWcon[1] = 1;
		}
		else
		{
			for (i = 0; i < 10; i++)
			{
				if (SC[i] == *p_dest)
				{
					PWcon[2] = 1;
					break;
				}
			}
		}
		p_dest++;
	}
	if (PWcon[0] && PWcon[1] && PWcon[2])
	{
		return 0;
	}
	return 1;
}
//중간 공백 체크하기
int checkSpace(const char* ap_string)
{
	char* p_dest = ap_string;

	while (*p_dest != '\0')
	{
		if (*p_dest++ == ' ')
		{
			return 1;
		}
	}
	return 0;	//맨 마지막에 null 저장
}
//중간 공백 지우기
void EraseSpace(char* ap_string)
{
	char* p_dest = ap_string;

	while (*ap_string != 0)
	{
		if (*ap_string != ' ')
		{
			*p_dest = *ap_string;
			p_dest++;
		}

		ap_string++;
	}
	*p_dest = 0;	//맨 마지막에 null 저장
}
// 문자열 우측 공백문자 삭제 함수
char* rtrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	des = (char*)malloc(sizeof(char) * strlen(src));//fgets 하면 개행문자도 같이들어갑니다.
	assert(des != NULL && "temp memory allocation is failed.");
	char* tdes = des;
	char* tsrc = src;

	while (*tsrc != '\0') 
	{
		*tdes++ = *tsrc++;
	}
		
	while (*tsrc == ' ')
	{
		tsrc--;
		tdes--;
	}
	*++tdes = '\0';

	return des;
}
// 문자열 좌측 공백문자 삭제 함수
char* ltrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	des = (char*)malloc(sizeof(char) * strlen(src));//fgets 하면 개행문자도 같이들어갑니다.
	assert(des != NULL && "temp memory allocation is failed.");
	char* end;
	int startFlags = 0;
	char* tdes = des;
	char* tsrc = src;

	while (*tsrc != '\0')
	{
		if (*tsrc == ' ' && startFlags == 0)
		{
			tsrc++;
		}
		else
		{
			startFlags = 1;
			*tdes++ = *tsrc++;
		}
	}
	*tdes = '\0';

	return des;
}
// 문자열 앞뒤 공백 모두 삭제 함수
char* trim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	des = (char*)malloc(sizeof(char) * strlen(src));//fgets 하면 개행문자도 같이들어갑니다.
	assert(des != NULL && "temp memory allocation is failed.");
	char* end;
	int startFlags = 0;
	char* tdes = des;
	char* tsrc = src;

	while (*tsrc != '\0')
	{
		if (*tsrc == ' ' && startFlags == 0)
		{
			tsrc++;
		}
		else
		{
			startFlags = 1;
			*tdes++ = *tsrc++;
		}
	}
	while (*tsrc == ' ')
	{
		tsrc--;
		tdes--;
	}
	*--tdes = '\0';


	return des;
}
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
		autoTransferInfo[f1] = NULL;
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
			if (k < 7)
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
			wtemps[f] = NULL;
		}
		return 1;
	}
	return 0;
}
int setError(FILE* f_accList)
{
	assert(f_accList != NULL && "accList is NULL");

	long CurrentFileOffset = 0;
	
	int i = 0;
	int accNumToCheck = 0;
	char* piter;
	char** accNums = NULL;
	eAccType type;
	FILE* f_setter;

	while (1)// 계좌 개수새기
	{
		fseek(f_accList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_accList);
		if (feof(f_accList))
		{
			break;
		}
		accNumToCheck++;
		CurrentFileOffset = ftell(f_accList);
	}
	i = 0;
	CurrentFileOffset = 0;

	accNums = (char**)malloc(sizeof(char*) * accNumToCheck);
	for (int j = 0; j < accNumToCheck; j++)
	{
		accNums[j] = (char*)malloc(sizeof(char) * 8);
	}
	while (i < accNumToCheck) // 계좌번호 버퍼에 담기
	{
		fseek(f_accList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_accList);
		if (feof(f_accList))
		{
			break;
		}
		strncpy(accNums[i], g_buffer, 7);
		accNums[i++][7] = '\0';
		CurrentFileOffset = ftell(f_accList);
	}
	int senseError = 0;
	for (int f = 0; f < accNumToCheck; f++) //루프돌면서
	{
		// 해당 파일찾아가기
		wchar_t waccNums[8];
		for (int i = 0; i < 8; i++)
		{
			mbtowc(waccNums+i, accNums[f]+i, MB_CUR_MAX);
		}
		switch (accNums[f][2]) // 타입체크
		{
		case '1': // 입출금
			type = T1;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", waccNums[1], waccNums);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkAcc(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		case '2': // 예금
			type = T2;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", waccNums[1], waccNums[0], waccNums[1], waccNums[2]);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkFix(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		case'3': // 적금
			type = T3;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", waccNums[1], waccNums[0], waccNums[1], waccNums[2]);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkSav(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		default:
			assert("Critical + fatal + horrendous error.... function: \"setInterset()\"" && 0);
		}
	}
	for (int k = 0; k < accNumToCheck; k++)
	{
		free(accNums[k]);
		accNums[k] = NULL;
	}
	free(accNums);
	accNums = NULL;
	return 0;
NEEDTOCORRECTFILE:
	return 1;
}
int checkAcc(FILE* f_target) // 읽으려고...이해하려고 시도하지마세요 ㅋㅋㅋㅋㅋㅋ
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume=6;
	char* piter = NULL;
	char* pFileOffset =NULL;
	while (1)
	{
		fseek(f_target, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_target);
		if (feof(f_target))
		{
			break;
		}
		piter = g_buffer;
		pFileOffset = g_buffer;
		if (line == 0) //첫번째줄
		{
			while ((*piter)!='|') // 계좌이름
			{
				if (isalnum(*piter) == 0)
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset+1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char),FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char),19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '\n') //나머지 걍 숫자
			{
				if (isdigit(*piter) == 0 && (*piter)!='|')
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
		}
		else//두번째 줄 ~ 
		{
			while ((*piter) != '|') // 날짜
			{
				if (isdigit(*piter) == 0 && *piter != '-')
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|') // 아이디
			{
				if (isalnum(*piter) == 0)
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//계좌번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//돈
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if ((*piter) != 'o' && (*piter) != 'i') // i or o
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//잔액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			
		}
		line++;
		CurrentFileOffset = ftell(f_target);
	}
	
	
	return 0;
}
int checkFix(FILE* f_target)
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	while (1)
	{
		fseek(f_target, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_target);
		if (feof(f_target))
		{
			break;
		}
		piter = g_buffer;
		pFileOffset = g_buffer;
		if (line == 0) //첫번째줄
		{
ANOTHER_ACCOUNT:
			while ((*piter) != '|') // 계좌이름
			{
				if (isalnum(*piter) == 0)
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//계좌번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.') //현재금액
				{
					while (*(++pFileOffset) != '\n' )
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//비밀번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)// 남은 기간
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 이자율
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 해지시 금액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			if (*piter++ == ' ')
			{
				goto ANOTHER_ACCOUNT;
			}
		}
		else //두번째 줄 ~ 
		{
			while ((*piter) != '|') // 날짜
			{
				if (isdigit(*piter) == 0 && *piter != '-')
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|') // 아이디
			{
				if (isalnum(*piter) == 0)
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//계좌번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')//만기시 해지 금액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0&&(*piter) != '.')//잔액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;

		}
		line++;
		CurrentFileOffset = ftell(f_target);
	}
	return 0;
}
int checkSav(FILE* f_target)
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	while (1)
	{
		fseek(f_target, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_target);
		if (feof(f_target))
		{
			break;
		}
		piter = g_buffer;
		pFileOffset = g_buffer;
ANOTHER:
		if (line == 0) //첫번째줄
		{

 			while ((*piter) != '|') // 계좌이름
			{
				if (isalnum(*piter) == 0)
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//계좌번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.') //현재금액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//비밀번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)// 남은 기간
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 이자율
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 해지시 금액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			if (*piter++ == ' ')
			{
				goto ANOTHER;
			}
		}
		else //두번째 줄 ~ 
		{
			while ((*piter) != '|') // 날짜
			{
				if (isdigit(*piter) == 0 && *piter != '-')
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|') // 아이디
			{
				if (isalnum(*piter) == 0)
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//계좌번호
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')//만기시 해지 금액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|' && (*piter) != '.')
			{
				if (isdigit(*piter) == 0)//잔액
				{
					while (*(++pFileOffset) != '\n')
					{
						CurrentFileOffset++;
					}
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					int numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					fwrite("<-- correct typos\n", sizeof(char), 19, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
		}
		line++;
		CurrentFileOffset = ftell(f_target);
	}
	return 0;
}
int setInterest(FILE* f_target)
{

	time_t curTime;
	struct tm* pTS;
	curTime = time(NULL);
	pTS = localtime(&curTime);

	int year;
	int month;
	int day;

	year = pTS->tm_year + 1900;
	month = pTS->tm_mon + 1;
	day = pTS->tm_mday;
}
int checkDupID(const char* ID)
{
	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;
	int bDulpicate = 0;

	char* IDs =NULL;
	int IDNums = 0;
	int i = 0;
	char* pbuf=NULL;
	char* pID = NULL;

	while (1)
	{
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_MemberFile);
		if (feof(f_MemberFile))
		{
			break;
		}
		IDNums++;
		IDs = (char*)malloc(sizeof(char) * 17);
		assert(IDs != NULL && "IDs memory allocation is error");
		pbuf = g_buffer;
		pID = IDs;

		while (*pbuf++ != '|');
		while(*pbuf != '|')
		{
			*pID++ = *pbuf++;
		}
		*pID = '\0';

		if (strcmp(ID, IDs) == 0)
		{
			free(IDs);
			return 1;
		}

		CurrentFileOffset = ftell(f_MemberFile);
	}
	if (IDs != NULL)
	{
		free(IDs);
	}
	return 0;
}
int checkDupPW(const char* PW)
{
	assert(PW != NULL && "PW is NULL");
	long CurrentFileOffset = 0;
	int bDulpicate = 0;

	char* PWs = NULL;
	int PWNums = 0;
	int i = 0;
	char* pbuf = NULL;
	char* pPW = NULL;

	while (1)
	{
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_MemberFile);
		if (feof(f_MemberFile))
		{
			break;
		}
		PWNums++;
		PWs = (char*)malloc(sizeof(char) * 17);
		assert(PWs != NULL && "PWs memory allocation is error");
		pbuf = g_buffer;
		pPW = PWs;

		while (*pbuf++ != '|');
		pbuf++;
		while (*pbuf++ != '|');
		while (*pbuf != '|')
		{
			*pPW++ = *pbuf++;
		}
		*pPW = '\0';

		if (strcmp(PW, PWs) == 0)
		{
			free(PWs);
			return 1;
		}

		CurrentFileOffset = ftell(f_MemberFile);
	}
	if (PWs != NULL)
	{
		free(PWs);
	}
	return 0;
}