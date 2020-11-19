#include "userfunc.h"

// 에러 체크 함수
int setError()
{
	int tempnamelen = 0;
	eAccType type;
	FILE* f_setter;

	setAccListOfAll_malloc();

	for (int f = 0; f < g_allALANNums; f++) //루프돌면서
	{
		// 해당 파일찾아가기
		wchar_t waccNums[8];
		for (int i = 0; i < 8; i++)
		{
			mbtowc(waccNums + i, g_allAccountsListAndName[0][f] + i, MB_CUR_MAX);
		}
		switch (getAccType(g_allAccountsListAndName[0][f])) // 타입체크
		{
		case T1: // 입출금
			type = T1;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", waccNums[1], waccNums);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkIO(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		case T2: // 예금
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
		case T3: // 적금
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
			assert("Account Lists file is something wrong.... function: \"setInterset()\"" && 0);
		}
	}
	return 0;
NEEDTOCORRECTFILE:
	return 1;
}
// 입출금계좌파일 체크
int checkIO(FILE* f_target) // 읽으려고...이해하려고 시도하지마세요 ㅋㅋㅋㅋㅋㅋ
{
	assert(f_target != NULL && "I can't find file by account.txt..target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	size_t numOfBefore = 0;
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
			while ((*piter) != '|') // 계좌이름
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '\n') //나머지 걍 숫자
			{
				if (isdigit(*piter) == 0 && (*piter) != '|')
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
// 예금계좌파일 체크
int checkFix(FILE* f_target)
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	size_t numOfBefore = 0;
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')//잔액
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
// 적금계좌파일 확인
int checkSav(FILE* f_target)
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	size_t numOfBefore = 0;
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
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
// 이자 적용
void setInterest()
{
	FILE* f_checker;
	wchar_t waccNums[8];

	for (int f = 0; f < g_allALANNums; f++) //루프돌면서
	{
		// 해당 파일찾아가기
		switch (getAccType(g_allAccountsListAndName[0][f])) // 타입체크
		{
		case T1: // 입출금 패스
			break;
		case T2: // 예금
		case T3: // 적금
			for (int i = 0; i < 8; i++)
			{
				mbtowc(waccNums + i, g_allAccountsListAndName[0][f] + i, MB_CUR_MAX);
			}
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", waccNums[1], waccNums[0], waccNums[1], waccNums[2]);
			f_checker = _wfopen(g_wpath, L"r+");
			setFSInterest(f_checker, g_allAccountsListAndName[0][f]);
			fclose(f_checker);
			f_checker = NULL;
			break;
		default:
			assert("Account Lists file is something wrong.... function: \"setInterset()\"");
		}
	}
}
// 예적금 이자 적용
int setFSInterest(FILE* f_accfile, const char* AccNum)
{
	long CurrentFileOffset = 0;
	long AttOffset = 0;
	long beforBal = 0;
	long afterBal = 0;
	int remainService = 0;
	int flag = 0;
	size_t numOfBefore = 0;

	double interestRatio = 0;

	int line = 0;
	int inputMonth = 0;
	int inputDay = 0;
	int inputYear = 0;

	char check = 0;

	char* pcp = NULL;
	char* pgb = NULL;
	char* temp = NULL;

	size_t templen = 0;
	size_t pcplen = 0;

	// 버퍼
	FSattributes_t* targetAT = (FSattributes_t*)malloc(sizeof(FSattributes_t));
	FSinqury_t* targetIQ = (FSinqury_t*)malloc(sizeof(FSinqury_t));
	assert(targetAT != NULL && targetIQ != NULL && "setSavInterest() allocation failed");

	pcplen = fread(g_tempbuff, sizeof(char), FILE_BUFF, f_accfile);
	fflush(f_accfile);
	g_tempbuff[pcplen] = '\0';
	pcp = g_tempbuff;
	pgb = g_buffer;
	while (*pcp != '\0')
	{
		if (*pcp != '\n')
		{
			*pgb++ = *pcp++;
		}
		else
		{
			*pgb = '\0';
			//printf("%s\n", g_buffer);
			if (flag == 0)
			{
				AttOffset = strToFSatt(g_buffer, targetAT, AccNum);
				flag = 1;
			}
			else
			{
				strToFSiq(g_buffer, targetIQ, AccNum);
				inputYear = atoi(&(targetIQ->FS_date[0]));
				inputMonth = atoi(&(targetIQ->FS_date[5]));
				inputDay = atoi(&(targetIQ->FS_date[8]));
				if (inputYear == g_year && inputMonth == g_month &&
					inputDay == g_day && *(targetIQ->FS_income) == '0' &&
					(strcmp(AccNum, targetIQ->FS_mynum) == 0))
				{ // 이자 잘 붙어있으면 나가기
					free(targetAT);
					free(targetIQ);
					targetAT = NULL;
					targetIQ = NULL;

					fprintf(stdout, "%s good\n", AccNum);
					return 1;
				}
			}
			pcp++;
			pgb = g_buffer;
			memset(g_buffer, '\0', BUFF_SIZE); // 아니면 다음칸.
		}
	} // 다 찾아봐도 없으면
	remainService = atoi(targetAT->FS_remainService);
	if (remainService == 0) // 남은 기간 0이면 없애기
	{
		free(targetAT);
		free(targetIQ);
		targetAT = NULL;
		targetIQ = NULL;

		fprintf(stdout, "%s no remain\n", AccNum);
		return 0;
	}//이자 계산
	beforBal = atol(targetAT->FS_balance);
	interestRatio = atof(targetAT->FS_interest);
	afterBal = beforBal + (long)(beforBal * interestRatio / 100);



	if (temp != NULL)
	{
		free(temp);
		temp = NULL;
	}//속성 쓰기
	templen = sizeof(FSattributes_t) / sizeof(char) + 8;
	temp = (char*)malloc(sizeof(char) * templen);
	assert(temp != NULL && "setSavInterset allocation failed");

	if (T3 == getAccType(targetAT->FS_mynum)) // 적금이면 월 최대 납입액 초기화
	{
		sprintf(temp, "%s|%s|500000|%s|%d|%.1f|%ld|",
			targetAT->FS_name, targetAT->FS_mynum,targetAT->FS_Passwords,
			remainService - 1, interestRatio, afterBal);
		//system("pause");
		printf("%s\n", temp);
	}
	else
	{
		sprintf(temp, "%s|%s|%s|%s|%d|%.1f|%ld|",
			targetAT->FS_name, targetAT->FS_mynum, targetAT->FS_money,
			targetAT->FS_Passwords, remainService - 1, interestRatio, afterBal);
		printf("%s\n", temp);
		//system("pause");
	}


	//파일에 쓰기
	CurrentFileOffset = AttOffset;
	fseek(f_accfile, CurrentFileOffset, SEEK_SET);

	while (check != ' ' && check != '\n')
	{
		check = fgetc(f_accfile);
		CurrentFileOffset++;
	}
	CurrentFileOffset--;

	if (AttOffset > 0) // 중간에 껴야할 때
	{
		fseek(f_accfile, 0, SEEK_SET); //앞에것
		numOfBefore = fread(g_filebuff2, sizeof(char), AttOffset, f_accfile);
	}
	fseek(f_accfile, CurrentFileOffset, SEEK_SET);// 뒤에것
	size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_accfile);
	//printf("g_filebuff:\n %s", g_filebuff);
	f_accfile = _wfreopen(g_wpath, L"w+", f_accfile);
	if (AttOffset > 0)
	{
		fwrite(g_filebuff2, sizeof(char), numOfBefore, f_accfile);
	}
	fwrite(temp, sizeof(char), strlen(temp), f_accfile);
	fflush(f_accfile);
	fwrite(g_filebuff, sizeof(char), numOfWords, f_accfile);
	fflush(f_accfile);

	free(temp);
	temp = NULL;

	//이자 내역 쓰기
	CurrentFileOffset = 0;
	fseek(f_accfile, CurrentFileOffset, SEEK_END);

	templen = sizeof(FSinqury_t) / sizeof(char) + 5;
	temp = (char*)malloc(sizeof(char) * templen);
	assert(temp != NULL && "setSavInterset allocation failed");

	sprintf(temp, "%d-%d-%d|%s|%s|0|%ld|\n",
		g_year, g_month, g_day, targetAT->FS_name, AccNum, afterBal);

	printf("%s\n", temp);

	fwrite(temp, sizeof(char), strlen(temp), f_accfile);
	fflush(f_accfile);

	free(temp);
	temp = NULL;

	fprintf(stdout, "%s bad\n", AccNum);
	return 0;
}
// 자동이체 적용
int setAutoTransfer()
{
	int tempnamelen = 0;
	eAccType type;
	FILE* f_setter;
	IOattributes_malloc_t* ISatt = NULL;

	setAccListOfAll_malloc();

	for (int f = 0; f < g_allALANNums; f++) //루프돌면서
	{
		// 해당 파일찾아가기
		ISatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
		assert(ISatt != NULL && "ISatt allocation failed \"setAutoTransfer()\"");
		wchar_t waccNums[8];
		for (int i = 0; i < 8; i++)
		{
			mbtowc(waccNums + i, g_allAccountsListAndName[0][f] + i, MB_CUR_MAX);
		}
		switch (getAccType(g_allAccountsListAndName[0][f])) // 타입체크
		{
		case T1: // 입출금
			type = T1;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", waccNums[1], waccNums);
			f_setter = _wfopen(g_wpath, L"r+");
			fgets(g_buffer, BUFF_SIZE, f_setter);
			strToIOatt_malloc(g_buffer, ISatt);
			if (ISatt->autoNums > 0)
			{
				setAutoIOTransfer(f_setter);
				freeIOattriutes(ISatt);
				free(ISatt);
				ISatt = NULL;
			}
			else
			{
				freeIOattriutes(ISatt);
				free(ISatt);
				ISatt = NULL;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		case T2: // 예금
		case T3: // 적금
			break;
		default:
			assert("Account Lists file is something wrong.... function: \"setInterset()\"" && 0);
		}
	}
	free(ISatt);
	ISatt = NULL;
	return 0;
}
// 입출금 자동이체 적용
int setAutoIOTransfer(FILE* f_io)
{
	assert(f_io != NULL && "setAutoIOTransfer() f_io is NULL");
	IOattributes_malloc_t* IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
	IOinqury_t* IOiq = (IOinqury_t*)malloc(sizeof(IOinqury_t));

	FILE* f_temp = f_io;

	fseek(f_temp, 0, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_temp);
	strToIOatt_malloc(g_buffer, IOatt);
	char toerase[30];
	for (int i = 0; i < IOatt->autoNums; i++)
	{
	ESCAPE:
		if (g_day == atoi(IOatt->autoattributes[i][0]))
		{
			while (1)
			{
				fgets(g_buffer, BUFF_SIZE, f_temp);
				if (feof(f_temp))
				{
					break;
				}
				strToIOiq(g_buffer, IOiq);
				if (g_year == atoi(IOiq->IO_date) && g_month == atoi(&(IOiq->IO_date[5])) && g_day == atoi(&(IOiq->IO_date[8])) &&
					(strncmp(IOatt->autoattributes[i][2], IOiq->IO_othernum, 7) == 0) &&
					strncmp(IOatt->autoattributes[i][1], IOiq->IO_money, strlen(IOiq->IO_money)) == 0)
				{
					goto ESCAPE;
				}
			}
			moneyOutIO(IOatt->IO_mynum, IOatt->autoattributes[i][2], atol(IOatt->autoattributes[i][1]), 0);
			switch (getAccType(IOatt->autoattributes[i][2]))
			{
			case T1:
				moneyInIO(IOatt->autoattributes[i][2], IOatt->IO_mynum, atol(IOatt->autoattributes[i][1]));
				sprintf(toerase, "%s|%s|%s|%s|", IOatt->autoattributes[i][0], IOatt->autoattributes[i][1], IOatt->autoattributes[i][2], IOatt->autoattributes[i][3]);
				eraseAuto(IOatt->IO_mynum, toerase, 1);
				PRINTLEFT(L"이체 되었습니다.");
				break;
			case T3:
				if (moneyInFS(IOatt->autoattributes[i][2], atol(IOatt->autoattributes[i][1]), 0) == 1)
				{
					sprintf(toerase, "%s|%s|%s|%s|", IOatt->autoattributes[i][0], IOatt->autoattributes[i][1], IOatt->autoattributes[i][2], IOatt->autoattributes[i][3]);
					eraseAuto(IOatt->IO_mynum, toerase, 1);
					PRINTLEFT(L"이체 되었습니다.");
				}
				break;
			default:
				break;
			}
		}

	}

	return 0;
}
// 데이터파일이랑 똑같이 해줘가지고 넘겨줘야, 삭제를 하거나 횟수를 줄여줍니다. 삭제 실패하면 0 성공하면 1
int eraseAuto(const char* accNum, const char* toerase, int num)
{
	assert(accNum != NULL && toerase != NULL && "src is NULL moneyOutIO() function");

	FILE* f_IO;
	long CurrentFileOffset = 0;
	char* gp = NULL;
	IOattributes_malloc_t* IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}
	// 파일 찾아가기
	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(accNum) + 1));
	for (int i = 0; i < strlen(accNum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, accNum + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", *(g_tempwcp + 1), g_tempwcp);
	free(g_tempwcp);
	g_tempwcp = NULL;

	f_IO = _wfopen(g_wpath, L"r+");
	fseek(f_IO, 0, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_IO);
	strToIOatt_malloc(g_buffer, IOatt);
	int j = 0;

	gp = g_buffer;
	for (int i = 0; i < 5; i++)
	{
		while (*gp++ != '|');
	}
	while (*gp != '\n')
	{
		if (strncmp(toerase, gp, strlen(toerase)) == 0)
		{
			int remain = atoi(IOatt->autoattributes[j][3]);
			char temp[30];
			if (remain - num > 0)
			{
				sprintf(temp, "%s|%s|%s|%d|", IOatt->autoattributes[j][0], IOatt->autoattributes[j][1], IOatt->autoattributes[j][2], remain - num);
			}

			CurrentFileOffset = (long)(gp - g_buffer);
			fseek(f_IO, 0, SEEK_SET);
			size_t num2 = fread(g_filebuff2, sizeof(char), CurrentFileOffset, f_IO);
			fseek(f_IO, CurrentFileOffset + (long)strlen(toerase), SEEK_SET);
			size_t num1 = fread(g_filebuff, sizeof(char), FILE_BUFF, f_IO);

			f_IO = _wfreopen(g_wpath, L"w+", f_IO);
			fseek(f_IO, 0, SEEK_SET);
			fwrite(g_filebuff2, sizeof(char), num2, f_IO);
			if (remain - num > 0)
			{
				fwrite(temp, sizeof(char), strlen(temp), f_IO);
			}
			fwrite(g_filebuff, sizeof(char), num1, f_IO);
			fflush(f_IO);
			fclose(f_IO);

			return 1;
		}
		else
		{
			j++;
			for (int i = 0; i < 4; i++)
			{
				while (*gp++ != '|');
			}
		}
	}
	return 0;
}
// 아이디로 사용자 소유 계좌리스트 생성 계좌 개수 반환
int setAccListByID_malloc(const char* ID)
{

	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;
	int bDulpicate = 0;

	char* IDs = NULL;
	int AccountsNums = 0;
	int i = 0;
	char* pbuf = NULL;
	char* pbuftemp = NULL;
	char* pID = NULL;

	CurrentFileOffset = setBankByID(ID);

	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_MemberFile);
	if (feof(f_MemberFile))
	{
		return 0;
	}
	pbuf = g_buffer;
	pID = IDs;
	for (int j = 0; j < 4; j++)
	{
		while (*pbuf++ != '|')
		{
			CurrentFileOffset++;
		}
	}
	pbuftemp = pbuf;
	while (*pbuf != '\0')
	{
		if (*pbuf++ == '|')
		{
			AccountsNums++;
		}
	}
	pbuf = pbuftemp;

	if (g_userAccountsList != NULL)
	{

		for (int h = 0; h < g_userALNums; h++)
		{
			free(g_userAccountsList[h]);
			g_userAccountsList[h] = NULL;
		}
		free(g_userAccountsList);
		g_userAccountsList = NULL;
	}
	g_userALNums = AccountsNums;

	if (g_userALNums != 0)
	{
		g_userAccountsList = (char**)malloc(sizeof(char*) * g_userALNums);
		assert(g_userAccountsList != NULL && "g_userAccountsList memory allocation is failed");
		for (int k = 0; k < g_userALNums; k++)
		{
			g_userAccountsList[k] = (char*)malloc(sizeof(char) * 8);
			assert(g_userAccountsList[k] != NULL && "g_userAccountsList[i] memory allocation is failed");
			for (int h = 0; h < 7; h++)
			{
				g_userAccountsList[k][h] = *pbuf++;
			}
			pbuf++;
			g_userAccountsList[k][7] = '\0';
			//printf("%s\n", g_userAccountsList[k]);
		}
		return g_userALNums;
	}
	return 0;
}
// 계좌리스트 파일 긁어서 버퍼에 넣기. 계좌 개수 반환
int setAccListOfAll_malloc()
{
	long CurrentFileOffset = 0;

	int i = 0;
	size_t tempnamelen = 0;
	int AccountNums = 0;
	char* piter = NULL;;
	char* pitertemp = NULL;

	while (1)// 계좌 개수새기
	{
		fseek(f_AccountList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_AccountList);
		//printf("%s", g_buffer);
		if (feof(f_AccountList))
		{
			break;
		}
		AccountNums++;
		CurrentFileOffset = ftell(f_AccountList);
	}

	if (g_allAccountsListAndName != NULL)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int h = 0; h < g_allALANNums; h++)
			{
				free(g_allAccountsListAndName[k][h]);
				g_allAccountsListAndName[k][h] = NULL;
			}
			free(g_allAccountsListAndName[k]);
			g_allAccountsListAndName[k] = NULL;
		}
		free(g_allAccountsListAndName);
		g_allAccountsListAndName = NULL;
	}
	g_allALANNums = AccountNums;
	//printf("%d", g_allALANNums);

	g_allAccountsListAndName = (char***)malloc(sizeof(char**) * 2);
	assert(g_allAccountsListAndName != NULL && "g_allAcountsListAndName allocation failed");
	for (int j = 0; j < 2; j++)
	{
		g_allAccountsListAndName[j] = (char**)malloc(sizeof(char*) * g_allALANNums);
		assert(g_allAccountsListAndName[j] != NULL && "g_allAcountsListAndName allocation failed");
	}
	for (int k = 0; k < g_allALANNums; k++)
	{
		g_allAccountsListAndName[0][k] = (char*)malloc(sizeof(char) * 8);
		assert(g_allAccountsListAndName[0][k] != NULL && "g_allAcountsListAndName allocation failed");

	}
	CurrentFileOffset = 0;
	i = 0;
	while (i < g_allALANNums) // 계좌번호 버퍼에 담기
	{
		tempnamelen = 0;
		fseek(f_AccountList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_AccountList);
		if (feof(f_AccountList))
		{
			break;
		}
		piter = g_buffer;
		strncpy(g_allAccountsListAndName[0][i], g_buffer, 7);
		g_allAccountsListAndName[0][i][7] = '\0';
		//printf("%s |", g_allAccountsListAndName[0][i]);

		while (*piter++ != '|');
		pitertemp = piter;
		while (*piter++ != '|')
		{
			tempnamelen++;
		}
		g_allAccountsListAndName[1][i] = (char*)malloc(sizeof(char) * (tempnamelen + 1));
		assert(g_allAccountsListAndName[1][i] != NULL && "g_allAcountsListAndName allocation failed");

		strncpy(g_allAccountsListAndName[1][i], pitertemp, tempnamelen);
		g_allAccountsListAndName[1][i][tempnamelen] = '\0';
		//printf("%s\n", g_allAccountsListAndName[1][i]);

		CurrentFileOffset = ftell(f_AccountList);
		i++;
	}
	//system("pause");
	return g_allALANNums;

}