#include "userfunc.h"


// 입출금 계좌파일 내역 한줄을 IOinqury에 내역 넣어줍니다. 성공하면 1 실패하면 0 반환
int strToIOiq(const char* str, IOinqury_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	const char* piter = str;
	const char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;

	//계좌 내역 뽑기
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_date, piter, counter);
	ioacc->IO_date[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_name, piter, counter);
	ioacc->IO_name[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_othernum, piter, counter);
	ioacc->IO_othernum[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_money, piter, counter);
	ioacc->IO_money[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
		if (counter > 2)
		{
			ioacc = NULL;
			return 0;
		}
	}
	strncpy(ioacc->IO_io, piter, 1);
	ioacc->IO_io[1] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		if (*pcounter == '\n')
		{
			ioacc = NULL;
			return 0;
		}
		counter++;
	}
	strncpy(ioacc->IO_balance, piter, counter);
	ioacc->IO_balance[counter] = '\0';
	return 1;
}
// 예적금 계좌파일 내역 한줄을 IOinqury에 내역 넣어줍니다. 3번째 인자로 넣어준 계좌번호만 출력. 성공하면 1 실패하면 0반환 
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or fsacc or accNum is NULL");

	const char* piter = str;
	const char* pcounter;
	int counter = 0;
	int findflag = 0;

	//계좌 내역 뽑기
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_date, piter, counter);
	fsacc->FS_date[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_name, piter, counter);
	fsacc->FS_name[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_mynum, piter, counter);
	fsacc->FS_mynum[counter] = '\0';

	fsacc->FS_type = getAccType(fsacc->FS_mynum);

	if (strncmp(accNum, fsacc->FS_mynum, 7) == 0)
	{
		findflag = 1;
	}

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_income, piter, counter);
	fsacc->FS_income[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_balance, piter, counter);
	fsacc->FS_balance[counter] = '\0';

	if (findflag == 1)
	{
		return 1;
	}
	return 0;
}
// 입출금 계좌파일 속성 한줄을 IOattributes_malloc_t에 넣어 줍니다. 성공하면 1 실패하면 0 반환
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	const char* piter = str;
	const char* pcounter;
	int counter = 0;
	int autonum = 0;

	//계좌 내역 뽑기
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_name, piter, counter);
	ioacc->IO_name[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_mynum, piter, counter);
	ioacc->IO_mynum[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_balance, piter, counter);
	ioacc->IO_balance[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_Passwords, piter, counter);
	ioacc->IO_Passwords[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_dateLimits, piter, counter);
	ioacc->IO_dateLimits[counter] = '\0';

	piter = pcounter;
	counter = 0;
	if (*pcounter++ == '\n')
	{
		ioacc->autoattributes = NULL;
		ioacc->autoNums = 0;
		return 1;
	}
	while (*pcounter != '\n')
	{
		for (int i = 0; i < 4; i++)
		{
			while (*pcounter++ != '|');
		}
		autonum++;
	}
	pcounter = piter;
	ioacc->autoNums = autonum;
	ioacc->autoattributes = (char***)malloc(sizeof(char**) * autonum);
	for (int j = 0; j < autonum; j++)
	{
		ioacc->autoattributes[j] = (char**)malloc(sizeof(char*) * 4);
		ioacc->autoattributes[j][0] = (char*)malloc(sizeof(char) * 3);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][0], piter, counter);
		ioacc->autoattributes[j][0][counter] = '\0';
		ioacc->autoattributes[j][1] = (char*)malloc(sizeof(char) * 13);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][1], piter, counter);
		ioacc->autoattributes[j][1][counter] = '\0';
		ioacc->autoattributes[j][2] = (char*)malloc(sizeof(char) * 8);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][2], piter, counter);
		ioacc->autoattributes[j][2][counter] = '\0';
		ioacc->autoattributes[j][3] = (char*)malloc(sizeof(char) * 3);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][3], piter, counter);
		ioacc->autoattributes[j][3][counter] = '\0';
	}

	return 1;
}
// 예적금 계좌파일 속성 한줄을 FSattritubes_t에 넣어줍니다. 3번째 인자로 넣어준 계좌번호만 출력. 성공하면 시작위치 정수, 실패하면 -1 반환
int strToFSatt(const char* str, FSattributes_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or ioacc or accNum is NULL");

	const char* piter = str;
	const char* returnValue;
	const char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;
	int flag = 1;
	int findflag = 0;


	//계좌 내역 뽑기

	while (flag == 1 && *piter != '\n')
	{
		returnValue = piter;
		pcounter = piter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_name, piter, counter);
		fsacc->FS_name[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_mynum, piter, counter);
		fsacc->FS_mynum[counter] = '\0';

		if (strncmp(fsacc->FS_mynum, accNum, 7) == 0)
		{
			findflag = 1;
		}

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_money, piter, counter);
		fsacc->FS_money[counter] = '\0';


		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_Passwords, piter, counter);
		fsacc->FS_Passwords[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_remainService, piter, counter);
		fsacc->FS_remainService[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_interest, piter, counter);
		fsacc->FS_interest[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_balance, piter, counter);
		fsacc->FS_balance[counter] = '\0';

		if (findflag == 1)
		{
			return (int)(returnValue - str);
		}
		else
		{
			pcounter = piter;
			while (*pcounter != ' ')
			{
				pcounter++;
			}
			piter = ++pcounter;
		}
	}
	fprintf(stderr, "Eof with \\n\n");
	return -1;
}
// 다쓴 IOattributes_malloc_t 해제
void freeIOattriutes(IOattributes_malloc_t* ioacc)
{
	if (ioacc != NULL)
	{
		for (int f1 = 0; f1 < ioacc->autoNums; f1++)
		{
			for (int f2 = 0; f2 < 4; f2++)
			{
				free(ioacc->autoattributes[f1][f2]);
				ioacc->autoattributes[f1][f2] = NULL;
			}
			free(ioacc->autoattributes[f1]);
			ioacc->autoattributes[f1] = NULL;
		}
		ioacc->autoattributes = NULL;
	}
}
// 계좌 타입 반환
eAccType getAccType(const char* AccNum)
{
	switch (AccNum[2]) // 타입체크
	{
	case '1': // 입출금은 계좌마다
		return T1;
		break;
	case '2': // 예금은 하나
		return T2;
		break;
	case'3': // 적금도 일단 하나
		return T3;
		break;
	default:
		return 4;
	}
}