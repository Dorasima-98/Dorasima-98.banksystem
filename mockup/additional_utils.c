#include "userfunc.h"


// 숫자 아니면 1반환, 공백(?)이면 2 반환, 숫자면 0반환
int checkDigit(const char* ap_string)
{
	char* p_dest = ap_string;
	while (*p_dest != '\0')
	{
		if (isdigit(*p_dest) == 0)
		{
			if (*p_dest == ' ' || *p_dest == '\t')
			{
				return 2;
			}
			return 1;
		}
		p_dest++;
	}
	return 0;
}
//숫자 or 영문자 아니면 1반환
int checkAlnum(const char* ap_string)
{
	char* p_dest = ap_string;
	while (*p_dest != '\0')
	{
		if (isalnum(*p_dest) == 0)
		{
			return 1;
		}
		p_dest++;
	}
	return 0;
}
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
		if (isalpha(*p_dest) == 0 && *p_dest != ' ')
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
	char SC[10] = { '!','@','#','$','%','^','&','*','(',')' };
	int PWcon[3] = { 0, };
	int i = 0;

	while (*p_dest != '\0')
	{
		if (isalpha(*p_dest) != 0)
		{
			PWcon[0] = 1;
		}
		else if (isdigit(*p_dest) != 0)
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
// 입출금 계좌파일 내역 한줄을 IOinqury에 내역 넣어줍니다. 성공하면 1 실패하면 0 반환(ioacc는 NULL)
int strToIOiq(const char* str, IOinqury_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	char* piter = str;
	char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;

	//계좌 내역 뽑기
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_day, piter, counter);
	ioacc->IO_day[counter] = '\0';

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
		if (counter > 2)
		{
			ioacc = NULL;
			return 0;
		}
		counter++;
	}
	strncpy(ioacc->IO_io, piter, counter);
	ioacc->IO_io[counter] = '\0';

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
// 예적금 계좌파일 내역 한줄을 IOinqury에 내역 넣어줍니다. 3번째 인자로 넣어준 계좌번호만 출력. 성공하면 1 실패하면 0반환 (fsacc는 NULL)
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or fsacc or accNum is NULL");

	char* piter = str;
	char* pcounter;
	int counter = 0;

	//계좌 내역 뽑기
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_day, piter, counter);
	fsacc->FS_day[counter] = '\0';

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

	if (strncmp(accNum, fsacc->FS_mynum, 7) != 0)
	{
		fsacc = NULL;
		return 0;
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
	strncpy(fsacc->FS_balance, piter, counter);
	fsacc->FS_balance[counter] = '\0';

	while (*pcounter++ != '\0')
	{
		if (*pcounter = '|')
		{
			fsacc = NULL;
			return 0;
		}
	}

	return 1;
}
// IOinqury_t 포인터 받아서 내역 출력합니다.
void printIOinquiry(const IOinqury_t* ioacc)
{
	assert(ioacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_day) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_day) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_day[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_day) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_day[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_othernum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_othernum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_othernum[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_money) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_money) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_money[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_io) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_io) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_io[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_balance[i] + j, MB_CUR_MAX);
	}

	switch (*(ioacc->IO_io))
	{
	case 'i':
		wprintf(L"< %s >/ %16s: %s/ 금액: %s (입금)/ 잔액: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
		break;
	case 'o':
		wprintf(L"< %s >/ %16s: %s/ 금액: %s (출금)/ 잔액: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
		break;
	default:
		assert("Print Inquriy Error in \"printIOInquiry()\"");
	}

	for (int k = 0; k < 6; k++)
	{
		free(wtemps[k]);
		wtemps[k] = NULL;
	}
}
// FSinquiry_t 포인터를 받아서 내역 출력합니다.
void printFSinquiry(const FSinqury_t* fsacc)
{
	assert(fsacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_day) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocatFSn failed");
	for (int j = 0; j < strlen(fsacc->FS_day) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_day[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_day) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_day[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_mynum[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_money) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_money) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_money[i] + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_balance[i] + j, MB_CUR_MAX);
	}

	switch (fsacc->FS_type)
	{
	case T2:
		wprintf(L"< %s >/ %16s: %s/ 만기해지시 금액: %s / 현재 금액: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
			break;
	case T3:
		wprintf(L"< %s >/ %16s: %s/ 최대 월 납입액: %s/ 현재 금액: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
		break;
	default:
		assert("Print Inquriy Error in \"printFSInquiry()\"");
	}

	for (int k = 0; k < 5; k++)
	{
		free(wtemps[k]);
		wtemps[k] = NULL;
	}
}
// 입출금 계좌파일 속성 한줄을 IOattributes_malloc_t에 넣어 줍니다. 성공하면 1 실패하면 0 반환(ioacc는 NULL)
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	char* piter = str;
	char* pcounter;
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
		if (counter > 2)
		{
			ioacc = NULL;
			return 0;
		}
		counter++;
	}
	strncpy(ioacc->IO_dayLimits, piter, counter);
	ioacc->IO_dayLimits[counter] = '\0';

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
	strncpy(ioacc->IO_monthLimits, piter, counter);
	ioacc->IO_monthLimits[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		if (*pcounter == '\n')
		{
			ioacc->autoattributes = NULL;
			ioacc->autoNums = 0;
			return 1;
		}
	}
	pcounter = piter;
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
// 예적금 계좌파일 속성 한줄을 FSattritubes_t에 넣어줍니다. 3번째 인자로 넣어준 계좌번호만 출력. 성공하면 1, 실패하면 0 반환
int strToFSatt(const char* str, FSattributes_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or ioacc or accNum is NULL");

	char* piter = str;
	char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;
	int flag = 1;
	int findflag = 0;

	//계좌 내역 뽑기

	while (flag == 1 && *piter != '\n')
	{

		pcounter = piter;
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
		strncpy(fsacc->FS_received, piter, counter);
		fsacc->FS_received[counter] = '\0';


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
			if (counter > 2)
			{
				fsacc = NULL;
				return 0;
			}
			counter++;
		}
		strncpy(fsacc->FS_balance, piter, counter);
		fsacc->FS_balance[counter] = '\0';

		if (findflag == 1)
		{
			break;
		}
		else
		{
			while (*pcounter != '\n')
			{
				if (*pcounter++ == ' ')
				{
					flag = 1;
					piter = pcounter;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if (flag == 0)
			{
				fsacc = NULL;
				return 0;
			}

		}
		return 1;
	}
}
void printIOatt(const IOattributes_malloc_t* ioacc)
{
	assert(ioacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	wchar_t*** wautotemps;
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_name) + 1; j++)
	{
		mbtowc(&wtemps[i][j], (ioacc->IO_balance[i]) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_balance[i]) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_balance[i]) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_Passwords) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_Passwords) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_Passwords[i]) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_dayLimits) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_dayLimits) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_dayLimits[i]) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_monthLimits) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_monthLimits) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_monthLimits[i]) + j, MB_CUR_MAX);
	}
	wprintf(L"< 입출금 계좌 >/ %16s: %s/ 잔액: %s 이체한도 %s(일)/%s(월)\n",
		wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5]);

	if (ioacc->autoNums > 0)
	{
		wautotemps = (wchar_t***)malloc(sizeof(char**) * ioacc->autoNums);
		for (int j = 0; j < ioacc->autoNums; j++)
		{
			wautotemps[j] = (wchar_t**)malloc(sizeof(wchar_t*) * 4);
			for (int u = 0; u < 4; u++)
			{
				wautotemps[j][u] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->autoattributes[j][u]) + 1));
				for (int j = 0; j < strlen(ioacc->autoattributes[j][u]) + 1; j++)
				{
					mbtowc(wautotemps[j][u] + j, (ioacc->autoattributes[j][u]) + j, MB_CUR_MAX);
				}
			}
		}

		for (int k = 0; k < ioacc->autoNums; i++)
		{
			wprintf(L"%d)<자동이체>/ %16s에 %s 원씩, 매월 %s일이 되면 보냅니다. 남은 기간 %s(월)\n",
				k, wtemps[k][2], wtemps[k][1], wtemps[k][0], wtemps[k][3]);
		}

		for (int f1 = 0; f1 < ioacc->autoNums; f1++)
		{
			for (int f2 = 0; f2 < 4; f2++)
			{
				free(wautotemps[f1][f2]);
				wautotemps[f1][f2] = NULL;
			}
			free(wautotemps[f1]);
			wautotemps[f1] = NULL;
		}
		free(wautotemps);
		wautotemps = NULL;
	}
	return;
}
void printFSatt(FSattributes_t* fsacc)
{
	assert(fsacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_name[i] + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_mynum[i] + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_received) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_received) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_received[i] + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_Passwords) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_Passwords) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_Passwords[i] + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_remainService) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_remainService) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_remainService[i] + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_interest) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_interest) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_interest[i] + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_balance[i] + j, MB_CUR_MAX);
	}
	i++;

	if (fsacc-> type== T2)
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

// 막만든 함수4
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
			assert("Critical + fatal + horrendous error.... function: \"setInterset()\"" && 0);
		}
	}
	return 0;
NEEDTOCORRECTFILE:
	return 1;
}
// 막만든 함수5
int checkIO(FILE* f_target) // 읽으려고...이해하려고 시도하지마세요 ㅋㅋㅋㅋㅋㅋ
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
			while ((*piter) != '\n') //나머지 걍 숫자
			{
				if (isdigit(*piter) == 0 && (*piter) != '|')
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
// 막만든 함수6
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
				if (isdigit(*piter) == 0 && (*piter) != '.')//잔액
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
// 막만든 함수7
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
// 아직 안만듦
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
// 아이디 중복되는지 확인합니다.
int checkDupID(const char* ID)
{
	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;

	char* IDs = NULL;
	int i = 0;
	char* pbuf = NULL;
	char* pID = NULL;

	while (1)
	{
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_MemberFile);
		if (feof(f_MemberFile))
		{
			break;
		}
		IDs = (char*)malloc(sizeof(char) * 17);
		assert(IDs != NULL && "IDs memory allocation is error");
		pbuf = g_buffer;
		pID = IDs;

		while (*pbuf++ != '|');
		while (*pbuf != '|')
		{
			*pID++ = *pbuf++;
		}
		*pID = '\0';

		if (strcmp(ID, IDs) == 0)
		{
			free(IDs);
			IDs = NULL;
			return 1;
		}

		CurrentFileOffset = ftell(f_MemberFile);
	}
	if (IDs != NULL)
	{
		IDs = NULL;
		free(IDs);
	}
	return 0;
}
// 아이디에 해당하는 비밀번호가 맞는지 확인합니다.
int checkDupPW(const char* ID, const char* PW)
{
	assert(PW != NULL && "PW is NULL");
	long CurrentFileOffset = 0;

	char* PWs = NULL;
	int i = 0;
	char* pbuf = NULL;
	char* pPW = NULL;

	CurrentFileOffset = setBankByID(ID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_MemberFile);
	if (feof(f_MemberFile))
	{
		return 0;
	}
	PWs = (char*)malloc(sizeof(char) * 33);
	assert(PWs != NULL && "PWs memory allocation is error");
	pbuf = g_buffer;
	pPW = PWs;

	while (*pbuf++ != '|');
	while (*pbuf++ != '|');
	while (*pbuf != '|')
	{
		*pPW++ = *pbuf++;
	}
	*pPW = '\0';

	if (strcmp(PW, PWs) == 0)
	{
		free(PWs);
		PWs = NULL;
		return 1;
	}

	if (PWs != NULL)
	{
		free(PWs);
		PWs = NULL;
	}
	return 0;
}
// 아이디로 글로벌 뱅크 코드 세팅하고 그 줄 오프셋 반환 합니다....없으면 0반환
int setBankByID(const char* ID)
{
	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;

	char* IDs = NULL;
	int IDNums = 0;
	int i = 0;
	char* pbuf = NULL;
	char* pID = NULL;
	int bankCode = 0;

	while (1)
	{
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_MemberFile);
		if (feof(f_MemberFile))
		{
			break;
		}
		IDs = (char*)malloc(sizeof(char) * 17);
		assert(IDs != NULL && "IDs memory allocation is error");
		pbuf = g_buffer;
		pID = IDs;

		while (*pbuf++ != '|');
		while (*pbuf != '|')
		{
			*pID++ = *pbuf++;
		}
		*pID = '\0';

		if (strcmp(ID, IDs) == 0)
		{
			while (*pbuf++ != '|');
			while (*pbuf++ != '|');
			bankCode = atoi(pbuf);
			assert((isdigit(bankCode) == 0 || bankCode == 0) && "get BankCode is failed");

			IDs = NULL;
			free(IDs);

			g_userBank = bankCode;
			return CurrentFileOffset;
		}
		CurrentFileOffset = ftell(f_MemberFile);
	}
	if (IDs != NULL)
	{
		IDs = NULL;
		free(IDs);
	}
	return 0;
}
// 계좌리스트 긁어온 버퍼로 사용자 소유 계좌이름 중복인지 확인 합니다. 중복이면 1반환 아니면 0반환
int checkDupAN(const char* input)
{
	assert(input != NULL && "ID is NULL");

	long CurrentFileOffset = 0;
	int bDulpicate = 0;

	int ANlen = 0;
	char* pbuf = NULL;
	char* pbuftemp = NULL;

	for (int i = 0; i < g_allALANNums; i++)
	{
		for (int j = 0; j < g_userALNums; j++)
		{
			if (strcmp(g_allAccountsListAndName[0][i], g_userAccountsList[j]) == 0)
			{
				if (strcmp(g_allAccountsListAndName[1][i], input) == 0)
				{
					return 1;
				}
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
		for (int k = 0; k < 2; k++)
		{
			for (int h = 0; h < g_userALNums; h++)
			{
				free(g_userAccountsList[0][h]);
				g_userAccountsList[k][h] = NULL;
			}
			free(g_userAccountsList[k]);
			g_userAccountsList[k] = NULL;
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
	int tempnamelen = 0;
	int AccountNums = 0;
	char* piter = NULL;;
	char* pitertemp = NULL;

	while (1)// 계좌 개수새기
	{
		fseek(f_AccountList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_AccountList);
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
	printf("%d", g_allALANNums);

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
		assert(g_allAccountsListAndName[1][k] != NULL && "g_allAcountsListAndName allocation failed");

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
		printf("%s | ", g_allAccountsListAndName[0][i]);

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
	return g_allALANNums;

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
