#include "userfunc.h"

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
		IDs = (char*)malloc(sizeof(char) * 17);
		assert(IDs != NULL && "IDs memory allocation is error");
		pbuf = g_buffer;
		pID = IDs;
		if (feof(f_MemberFile))
		{
			break;
		}
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
// 아이디로 글로벌 뱅크 코드 세팅하고 그 줄 오프셋 반환 합니다....없으면 -1반환
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
	return -1;
}
// 계좌리스트 긁어온 버퍼로 사용자 소유 계좌이름 중복인지 확인 합니다. 중복이면 1반환 아니면 0반환
int checkDupAN(const char* input)
{
	assert(input != NULL && "ID is NULL");

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
// 계좌번호를 포인터로 넘겨주고, 받을 계좌이름을 포인터로 넘겨주면된다.
char* getAccountName(const char* AccNum, char* AccName)
{
	assert(AccNum != NULL && "AccNum is NULL, \"getAccountName()\"");
	for (int i = 0; i < g_allALANNums; i++)
	{
		if (strncmp(g_allAccountsListAndName[0][i], AccNum, 7) == 0)
		{
			strncpy(AccName, g_allAccountsListAndName[1][i], strlen(g_allAccountsListAndName[1][i]) + 1);
			return AccName;
		}
	}
	return NULL;
}
// 계좌이체 및 atm 양식체크
int checkATMorTransfer(char* AccNum, char** items,int delnums)
{
	assert(AccNum != NULL && items != NULL && "checkATMorTransfer() parameter is NUL assertion");

	char* cp = AccNum;
	int delCounter = 0;
	char* temp;

	while (*cp++ != '\0' )
	{
		if (*cp == '/')
		{
			delCounter++;
		}
	}
	if (delCounter == delnums)
	{
		int i = 0;
		temp = strtok(AccNum, "/");
		while (temp != NULL)
		{
			items[i++] = temp;
			temp = strtok(NULL, "/");
		}
		return 1;
	}
	else
	{
		return 0;
	}

}
// 숫자 아니면 1반환, 공백(?)이면 2 반환, 숫자면 0반환
int checkDigit(const char* ap_string)
{
	assert(ap_string != NULL && "ap_string is NULL");
	const char* p_dest = ap_string;
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
	assert(ap_string != NULL && "ap_string is NULL");
	const char* p_dest = ap_string;
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
	assert(ap_string != NULL && "ap_string is NULL");
	const char* p_dest = ap_string;
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
	assert(ap_string != NULL && "ap_string is NULL");
	const char* p_dest = ap_string;

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
	assert(ap_string != NULL && "ap_string is NULL");
	const char* p_dest = ap_string;
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
	assert(ap_string != NULL && "ap_string is NULL");
	const char* p_dest = ap_string;

	while (*p_dest != '\0')
	{
		if (*p_dest++ == ' ')
		{
			return 1;
		}
	}
	return 0;	//맨 마지막에 null 저장
}
int checkExistAcc(const char* AccNum)
{
	for (int i = 0; i < g_allALANNums; i++)
	{
		if (strncmp(AccNum, g_allAccountsListAndName[0][i], 7) == 0)
		{
			return 1;
		}
	}
	return 0;
}