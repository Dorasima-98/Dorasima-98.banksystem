#include "userfunc.h"


// ���� �ƴϸ� 1��ȯ, ����(?)�̸� 2 ��ȯ, ���ڸ� 0��ȯ
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
//���� or ������ �ƴϸ� 1��ȯ
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
// ���� + �����ڰ� �ƴϸ� 1��ȯ
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
// ������ Ȥ�� ������ �ƴϸ� 1��ȯ
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
// ����, ����, Ư�� �ϳ� �� �־����. �̻��Ѱ� �����ų�, ������ 1��ȯ
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
//�߰� ���� üũ�ϱ�
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
	return 0;	//�� �������� null ����
}
//�߰� ���� �����
void EraseSpace(char* ap_string)
{
	assert(ap_string != NULL && "ap_string is NULL");
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
	*p_dest = 0;	//�� �������� null ����
}
// ���ڿ� ���� ���鹮�� ���� �Լ�
char* rtrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	if (des == NULL)
	{
		des = (char*)malloc(sizeof(char) * strlen(src));//fgets �ϸ� ���๮�ڵ� ���̵��ϴ�.
	}
	assert(des != NULL && "temp memory allocation is failed.");
	char* tdes = des;
	const char* tsrc = src;

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
// ���ڿ� ���� ���鹮�� ���� �Լ�
char* ltrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	if (des == NULL)
	{
		des = (char*)malloc(sizeof(char) * strlen(src));//fgets �ϸ� ���๮�ڵ� ���̵��ϴ�.
	}
	assert(des != NULL && "temp memory allocation is failed.");
	int startFlags = 0;
	char* tdes = des;
	const char* tsrc = src;

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
// ���ڿ� �յ� ���� ��� ���� �Լ�
char* trim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	if (des == NULL)
	{
		des = (char*)malloc(sizeof(char) * strlen(src));//fgets �ϸ� ���๮�ڵ� ���̵��ϴ�.
	}
	assert(des != NULL && "temp memory allocation is failed.");
	int startFlags = 0;
	char* tdes = des;
	const char* tsrc = src;

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
int moneyInIO(const char* desNum, const char* srcNum, long money)
{
	assert(desNum != NULL && "desNum is NULL moneyInIO() function");

	FILE* f_IO;
	IOattributes_malloc_t* IOatt = NULL;
	long CurrentFileOffset = 0;
	long balance = 0;
	char toATline[15];
	char srcName[17];
	char* toIQline = NULL;
	size_t toIQlen = 0;

	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}
	//���� ã�Ƽ� ����
	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(desNum) + 1));
	for (int i = 0; i < strlen(desNum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, desNum + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", g_tempwcp[1], g_tempwcp);
	free(g_tempwcp);
	g_tempwcp = NULL;
	//�̾Ƽ�
	f_IO = _wfopen(g_wpath, L"r+");
	IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
	fseek(f_IO, 0, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_IO);
	strToIOatt_malloc(g_buffer, IOatt);
	//���غ�
	balance = atol(IOatt->IO_balance);
	balance += money;
	sprintf(toATline, "%ld", balance);
	toIQlen = sizeof(IOinqury_t); // ���� �˳��ϰ� ���� ����
	toIQline = (char*)malloc(sizeof(char) * toIQlen);
	if (srcNum == NULL)
	{
		sprintf(toIQline, "%d-%d-%d|atm|0%d00000|%ld|i|%ld|\n", g_year, g_month, g_day, g_userBank, money, balance);
	}
	else
	{
		getAccountName(srcNum, srcName);
		sprintf(toIQline, "%d-%d-%d|%s|%s|%ld|i|%ld|\n", g_year, g_month, g_day, srcName, srcNum, money, balance);
	}
	//�ϴ� ���� ��������
	fseek(f_IO, 0, SEEK_END);
	fwrite(toIQline, sizeof(char), strlen(toIQline), f_IO);
	//�����ϰ�
	fseek(f_IO, 0, SEEK_SET);
	size_t numofWords2 = fread(g_filebuff2, sizeof(char), strlen(IOatt->IO_name) + strlen(IOatt->IO_mynum) + 2, f_IO);
	CurrentFileOffset = ftell(f_IO);

	fseek(f_IO, CurrentFileOffset + (long)strlen(toATline), SEEK_SET);
	size_t numofWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_IO);
	//������� �ٽÿ�� ����
	f_IO = _wfreopen(g_wpath, L"w+", f_IO);

	fseek(f_IO, 0, SEEK_SET);
	fwrite(g_filebuff2, sizeof(char), numofWords2, f_IO);
	fwrite(toATline, sizeof(char), strlen(toATline), f_IO);
	fwrite(g_filebuff, sizeof(char), numofWords, f_IO);
	

	freeIOattriutes(IOatt);
	free(IOatt);
	free(toIQline);
	IOatt = NULL;
	toIQline = NULL;
	fclose(f_IO);

	return 1;
}
// ��ü�ѵ� ������ 0 ��ȯ, �����ϸ� 1 ��ȯ ,flag�� 1�� �Ѱ��ָ� ��ü�ѵ� ����
int moneyOutIO(const char* srcNum, const char* desNum, long money,int flag)
{
	assert(srcNum != NULL && "src is NULL moneyOutIO() function");

	FILE* f_IO;
	IOattributes_malloc_t* IOatt = NULL;
	long CurrentFileOffset = 0;
	long balance = 0;
	long datelimit = 0;
	char toATline[30]; // ���� �˳�
	char desName[17];
	char* toIQline = NULL;
	size_t toIQlen = 0;

	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}
	// ���� ã�ư���
	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(srcNum) + 1));
	for (int i = 0; i < strlen(srcNum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, srcNum + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", g_tempwcp[1], g_tempwcp);
	free(g_tempwcp);
	g_tempwcp = NULL;

	//��� �Ӽ��̱�
	f_IO = _wfopen(g_wpath, L"r+");
	IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
	fseek(f_IO, 0, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_IO);
	strToIOatt_malloc(g_buffer, IOatt);

	//�۾�
	balance = atol(IOatt->IO_balance);
	balance -= money;
	datelimit = atol(IOatt->IO_dateLimits);
	datelimit -= money;
	if (datelimit < 0 && flag != 1)
	{
		freeIOattriutes(IOatt);
		free(IOatt);
		IOatt = NULL;
		fclose(f_IO);

		return 0;
	}

	//���غ�
	sprintf(toATline, "%ld|%s|%ld", balance, IOatt->IO_Passwords, datelimit);
	toIQlen = sizeof(IOinqury_t); // ���� �˳��ϰ� ���� ����
	toIQline = (char*)malloc(sizeof(char) * toIQlen);

	if (desNum == NULL)
	{
		sprintf(toIQline, "%d-%d-%d|atm|0%d00000|%ld|o|%ld|\n", g_year, g_month, g_day, g_userBank, money, balance);
	}
	else
	{
		getAccountName(desNum, desName);
		sprintf(toIQline, "%d-%d-%d|%s|%s|%ld|o|%ld|\n", g_year, g_month, g_day, desName, desNum, money, balance);
	}

	//�ϴ� ���� ��������
	fseek(f_IO, 0, SEEK_END);
	fwrite(toIQline, sizeof(char), strlen(toIQline), f_IO);

	//�����Ҳ� �ϰ�
	fseek(f_IO, 0, SEEK_SET);
	size_t numofWords2 = fread(g_filebuff2, sizeof(char), strlen(IOatt->IO_name) + strlen(IOatt->IO_mynum) + 2, f_IO);
	CurrentFileOffset = ftell(f_IO);

	fseek(f_IO, CurrentFileOffset + (long)strlen(toATline), SEEK_SET);
	size_t numofWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_IO);

	//������� �������� �ٽ� ����
	f_IO = _wfreopen(g_wpath, L"w+", f_IO);

	fseek(f_IO, 0, SEEK_SET);
	fwrite(g_filebuff2, sizeof(char), numofWords2, f_IO);
	fwrite(toATline, sizeof(char), strlen(toATline), f_IO);
	fwrite(g_filebuff, sizeof(char), numofWords, f_IO);

	freeIOattriutes(IOatt);
	free(IOatt);
	free(toIQline);
	IOatt = NULL;
	toIQline = NULL;
	fclose(f_IO);
	return 1;
}
// ���ݰ����� ��� �� ���Ӿ� �ѵ� ������ 0�ݿ�, �����ϸ� 1��ȯ
int moneyInFS(const char* accNum, long inmoney, int service)
{
	FILE* f_FS;
	FSattributes_t* FSatt = NULL;

	long CurrentFileOffset = 0;
	long AttOffset = 0;
	long balance = 0;
	long money = 0;
	long CurrentFileOffet = 0;
	int period = 0;
	float interestrate = 0.0f;
	size_t numofWords2 = 0;

	char* toATline =NULL;
	char accName[17];
	char* toIQline = NULL;

	char check = 0;



	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}
	//���� ã�Ƽ� ����
	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(accNum) + 1));
	for (int i = 0; i < strlen(accNum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, accNum + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\0%d%c.txt", g_userBank, g_userBank, g_tempwcp[2]);
	free(g_tempwcp);
	g_tempwcp = NULL;

	//�̾Ƽ�
	f_FS = _wfopen(g_wpath, L"r+");
	FSatt = (FSattributes_t*)malloc(sizeof(FSattributes_t));
	fseek(f_FS, 0, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_FS);
	AttOffset = strToFSatt(g_buffer, FSatt, accNum);


	balance = atol(FSatt->FS_balance);
	money = atol(FSatt->FS_money);

	//���� ����
	switch (service)
	{
	case 1:
		period = 6;
		interestrate = 1.0f;
		break;
	case 2:
		period = 12;
		interestrate = 1.5f;
		break;
	case 3:
		period = 24;
		interestrate = 2.0f;
		break;
	}
	money += inmoney;
	//���� ����
	if (getAccType(accNum) == T2)
	{
		for (int i = 0; i < period; i++)
		{
			money = (money * (long)(100.0f + interestrate)) / 100;
		}
	}
	else if (getAccType(accNum) == T3)
	{
		money -= inmoney;
		if (money < 0)
		{
			free(FSatt);
			FSatt = NULL;
			fclose(f_FS);
			return 0;
		}
	}
	else
	{
		assert("int moneyInFS() function error. you should put right type of account number");
	}

	balance += inmoney;

	//���غ�
	toATline = (char*)malloc(sizeof(FSattributes_t));
	sprintf(toATline, "%s|%s|%ld|%s|%d|%.1f|%ld|", FSatt->FS_name,FSatt->FS_mynum,money, FSatt->FS_Passwords, period, interestrate, balance);
	toIQline = (char*)malloc(sizeof(FSinqury_t));
	getAccountName(accNum, accName);
	sprintf(toIQline, "%d-%d-%d|%s|%s|%ld|%ld|\n", g_year, g_month, g_day, accName, accNum, inmoney, balance);

	//�ϴ� ���� ��������
	fseek(f_FS, 0, SEEK_END);
	fwrite(toIQline, sizeof(char), strlen(toIQline), f_FS);

	//�����ϰ�
	CurrentFileOffet = AttOffset;
	fseek(f_FS, CurrentFileOffet, SEEK_SET);

	while (check != ' ' && check != '\n')
	{
		check = fgetc(f_FS);
		CurrentFileOffset++;
	}
	CurrentFileOffset--;

	if (AttOffset > 0)
	{
		fseek(f_FS, 0, SEEK_SET);
		numofWords2 = fread(g_filebuff2, sizeof(char), AttOffset, f_FS);
	}

	fseek(f_FS, CurrentFileOffset, SEEK_SET);
	size_t numofWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_FS);
	//������� �ٽÿ�� ����
	f_FS = _wfreopen(g_wpath, L"w+", f_FS);

	if (AttOffset > 0)
	{
		fseek(f_FS, 0, SEEK_SET);
		fwrite(g_filebuff2, sizeof(char), numofWords2, f_FS);
	}	
	fwrite(toATline, sizeof(char), strlen(toATline), f_FS);
	fwrite(g_filebuff, sizeof(char), numofWords, f_FS);

	free(FSatt);
	free(toIQline);
	FSatt = NULL;
	toIQline = NULL;
	fclose(f_FS);

	return 1;
}
// ����� �������� ���� ������ IOinqury�� ���� �־��ݴϴ�. �����ϸ� 1 �����ϸ� 0 ��ȯ
int strToIOiq(const char* str, IOinqury_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	const char* piter = str;
	const char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;

	//���� ���� �̱�
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
// ������ �������� ���� ������ IOinqury�� ���� �־��ݴϴ�. 3��° ���ڷ� �־��� ���¹�ȣ�� ���. �����ϸ� 1 �����ϸ� 0��ȯ 
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or fsacc or accNum is NULL");

	const char* piter = str;
	const char* pcounter;
	int counter = 0;
	int findflag = 0;

	//���� ���� �̱�
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
// ����� �������� �Ӽ� ������ IOattributes_malloc_t�� �־� �ݴϴ�. �����ϸ� 1 �����ϸ� 0 ��ȯ
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	const char* piter = str;
	const char* pcounter;
	int counter = 0;
	int autonum = 0;

	//���� ���� �̱�
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
// ������ �������� �Ӽ� ������ FSattritubes_t�� �־��ݴϴ�. 3��° ���ڷ� �־��� ���¹�ȣ�� ���. �����ϸ� ������ġ ����, �����ϸ� -1 ��ȯ
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


	//���� ���� �̱�

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
// �پ� IOattributes_malloc_t ����
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
// IOinqury_t ������ �޾Ƽ� ���� ����մϴ�.
void printIOinquiry(const IOinqury_t* ioacc)
{
	assert(ioacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_date) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_date) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_date + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_name + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_othernum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_othernum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_othernum + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_money) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_money) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_money + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_io) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_io) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_io + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_balance + j, MB_CUR_MAX);
	}

	switch (*(ioacc->IO_io))
	{
	case 'i':
		wprintf(L"< %s >/ %16s: %s/ �ݾ�: %s (�Ա�)/ �ܾ�: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
		break;
	case 'o':
		wprintf(L"< %s >/ %16s: %s/ �ݾ�: %s (���)/ �ܾ�: %s\n",
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
// FSinqury_t ������ �޾Ƽ� ���� ����մϴ�.
int printFSinquiry(const FSinqury_t* fsacc)
{
	assert(fsacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[5] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_date) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocatFSn failed");
	for (int j = 0; j < strlen(fsacc->FS_date) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_date + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_name + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_mynum + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_income) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_income) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_income + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_balance + j, MB_CUR_MAX);
	}

	switch (fsacc->FS_type)
	{
	case T2:
		wprintf(L"< %s >/ %16s: %s/ �Աݾ�: %s / ���� �ݾ�: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
		break;
	case T3:
		wprintf(L"< %s >/ %16s: %s/ �Աݾ�: %s/ ���� �ݾ�: %s\n",
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
	return 1;
}
// IOattributes_malloc_t ������ �޾Ƽ� ���� ����մϴ�.
void printIOatt(const IOattributes_malloc_t* ioacc)
{
	assert(ioacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[5] = { NULL, 0 };
	wchar_t*** wautotemps;
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_name) + 1; j++)
	{
		mbtowc(&wtemps[i][j], (ioacc->IO_name) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_mynum) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_balance) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_Passwords) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_Passwords) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_Passwords) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_dateLimits) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_dateLimits) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_dateLimits) + j, MB_CUR_MAX);
	}

	wprintf(L"< ����� ���� >/ %s: %s/ �ܾ�: %s ��ü�ѵ� %s(��/��)\n",
		wtemps[0], wtemps[1], wtemps[2], wtemps[4]);

	if (ioacc->autoNums > 0)
	{
		wautotemps = (wchar_t***)malloc(sizeof(wchar_t**) * ioacc->autoNums);
		for (int j = 0; j < ioacc->autoNums; j++)
		{
			wautotemps[j] = (wchar_t**)malloc(sizeof(wchar_t*) * 4);
			for (int u = 0; u < 4; u++)
			{
				wautotemps[j][u] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->autoattributes[j][u]) + 1));
				for (int k = 0; k < strlen(ioacc->autoattributes[j][u]) + 1; k++)
				{
					mbtowc(wautotemps[j][u] + k, (ioacc->autoattributes[j][u]) + k, MB_CUR_MAX);
				}
			}
		}

		for (int k = 0; k < ioacc->autoNums; k++)
		{
			wprintf(L"%d)<�ڵ���ü>/ %.16s�� %s ����, �ſ� %s���� �Ǹ� �����ϴ�. ���� �Ⱓ %s(��)\n",
				k + 1, wautotemps[k][2], wautotemps[k][1], wautotemps[k][0], wautotemps[k][3]);
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
	for (int h = 0; h < 5; h++)
	{
		free(wtemps[h]);
		wtemps[h] = NULL;
	}

	return;
}
// FSattributes_t ������ �޾Ƽ� ���� ����մϴ�.
void printFSatt(const FSattributes_t* fsacc)
{
	assert(fsacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[7] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_name + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_mynum + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_money) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_money) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_money + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_Passwords) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_Passwords) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_Passwords + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_remainService) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_remainService) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_remainService + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_interest) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_interest) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_interest + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_balance + j, MB_CUR_MAX);
	}

	if (fsacc->type == T2)
	{
		wprintf(L"< ���� ���� >/ %16s: %s/ �ܾ�: %s ���� ��û�Ⱓ %s(��) ������: %s ������ �ݾ� %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5], wtemps[6]);
	}
	else
	{
		wprintf(L"< ���� ���� >/ %16s: %s/ �ܾ�: %s ���� ��û�Ⱓ %s(��) ������: %s ������ �ݾ� %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5], wtemps[6]);
	}
	for (int f = 0; f < 7; f++)
	{
		free(wtemps[f]);
		wtemps[f] = NULL;
	}
}
// ������ �Լ�1
int setError()
{
	int tempnamelen = 0;
	eAccType type;
	FILE* f_setter;

	setAccListOfAll_malloc();

	for (int f = 0; f < g_allALANNums; f++) //�������鼭
	{
		// �ش� ����ã�ư���
		wchar_t waccNums[8];
		for (int i = 0; i < 8; i++)
		{
			mbtowc(waccNums + i, g_allAccountsListAndName[0][f] + i, MB_CUR_MAX);
		}
		switch (getAccType(g_allAccountsListAndName[0][f])) // Ÿ��üũ
		{
		case T1: // �����
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
		case T2: // ����
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
		case T3: // ����
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
// ������ �Լ�2
int checkIO(FILE* f_target) // ��������...�����Ϸ��� �õ����������� ������������
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
		if (line == 0) //ù��°��
		{
			while ((*piter) != '|') // �����̸�
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
			while ((*piter) != '\n') //������ �� ����
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
		else//�ι�° �� ~ 
		{
			while ((*piter) != '|') // ��¥
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
			while ((*piter) != '|') // ���̵�
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
				if (isdigit(*piter) == 0)//���¹�ȣ
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
				if (isdigit(*piter) == 0)//��
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
				if (isdigit(*piter) == 0)//�ܾ�
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
// ������ �Լ�3
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
		if (line == 0) //ù��°��
		{
		ANOTHER_ACCOUNT:
			while ((*piter) != '|') // �����̸�
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
				if (isdigit(*piter) == 0)//���¹�ȣ
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
				if (isdigit(*piter) == 0 && (*piter) != '.') //����ݾ�
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
				if (isdigit(*piter) == 0)//��й�ȣ
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
				if (isdigit(*piter) == 0)// ���� �Ⱓ
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
				if (isdigit(*piter) == 0 && (*piter) != '.')// ������
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
				if (isdigit(*piter) == 0 && (*piter) != '.')// ������ �ݾ�
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
		else //�ι�° �� ~ 
		{
			while ((*piter) != '|') // ��¥
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
			while ((*piter) != '|') // ���̵�
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
				if (isdigit(*piter) == 0)//���¹�ȣ
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
				if (isdigit(*piter) == 0 && (*piter) != '.')//����� ���� �ݾ�
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
				if (isdigit(*piter) == 0 && (*piter) != '.')//�ܾ�
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
// ������ �Լ�4
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
		if (line == 0) //ù��°��
		{

			while ((*piter) != '|') // �����̸�
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
				if (isdigit(*piter) == 0)//���¹�ȣ
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
				if (isdigit(*piter) == 0 && (*piter) != '.') //����ݾ�
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
				if (isdigit(*piter) == 0)//��й�ȣ
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
				if (isdigit(*piter) == 0)// ���� �Ⱓ
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
				if (isdigit(*piter) == 0 && (*piter) != '.')// ������
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
				if (isdigit(*piter) == 0 && (*piter) != '.')// ������ �ݾ�
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
		else //�ι�° �� ~ 
		{
			while ((*piter) != '|') // ��¥
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
			while ((*piter) != '|') // ���̵�
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
				if (isdigit(*piter) == 0)//���¹�ȣ
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
				if (isdigit(*piter) == 0 && (*piter) != '.')//����� ���� �ݾ�
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
				if (isdigit(*piter) == 0)//�ܾ�
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
// ���� ����
void setInterest()
{
	FILE* f_checker;
	wchar_t waccNums[8];

	for (int f = 0; f < g_allALANNums; f++) //�������鼭
	{
		// �ش� ����ã�ư���
		switch (getAccType(g_allAccountsListAndName[0][f])) // Ÿ��üũ
		{
		case T1: // ����� �н�
			break;
		case T2: // ����
		case T3: // ����
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
// ������ ���� ����
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

	// ����
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
				{ // ���� �� �پ������� ������
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
			memset(g_buffer, '\0', BUFF_SIZE); // �ƴϸ� ����ĭ.
		}
	} // �� ã�ƺ��� ������
	remainService = atoi(targetAT->FS_remainService);
	if (remainService == 0) // ���� �Ⱓ 0�̸� ���ֱ�
	{
		free(targetAT);
		free(targetIQ);
		targetAT = NULL;
		targetIQ = NULL;

		fprintf(stdout, "%s no remain\n", AccNum);
		return 0;
	}//���� ���
	beforBal = atol(targetAT->FS_balance);
	interestRatio = atof(targetAT->FS_interest);
	afterBal = beforBal + (long)(beforBal * interestRatio / 100);



	if (temp != NULL)
	{
		free(temp);
		temp = NULL;
	}//�Ӽ� ����
	templen = sizeof(FSattributes_t) / sizeof(char) + 8;
	temp = (char*)malloc(sizeof(char) * templen);
	assert(temp != NULL && "setSavInterset allocation failed");

	sprintf(temp, "%s|%s|%s|%s|%d|%.1f|%ld|",
		targetAT->FS_name, targetAT->FS_mynum, targetAT->FS_money,
		targetAT->FS_Passwords, remainService - 1, interestRatio, afterBal);
	printf("%s\n", temp);

	//���Ͽ� ����
	CurrentFileOffset = AttOffset;
	fseek(f_accfile, CurrentFileOffset, SEEK_SET);

	while (check != ' ' && check != '\n')
	{
		check = fgetc(f_accfile);
		CurrentFileOffset++;
	}
	CurrentFileOffset--;

	if (AttOffset > 0) // �߰��� ������ ��
	{
		fseek(f_accfile, 0, SEEK_SET); //�տ���
		numOfBefore = fread(g_filebuff2, sizeof(char), AttOffset, f_accfile);
	}
	fseek(f_accfile, CurrentFileOffset, SEEK_SET);// �ڿ���
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

	//���� ���� ����
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
// ���̵� �ߺ��Ǵ��� Ȯ���մϴ�.
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
// ���̵� �ش��ϴ� ��й�ȣ�� �´��� Ȯ���մϴ�.
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
// ���̵�� �۷ι� ��ũ �ڵ� �����ϰ� �� �� ������ ��ȯ �մϴ�....������ -1��ȯ
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
// ���¸���Ʈ �ܾ�� ���۷� ����� ���� �����̸� �ߺ����� Ȯ�� �մϴ�. �ߺ��̸� 1��ȯ �ƴϸ� 0��ȯ
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
// ���¹�ȣ�� �����ͷ� �Ѱ��ְ�, ���� �����̸��� �����ͷ� �Ѱ��ָ�ȴ�.
char* getAccountName(const char* AccNum, char* AccName)
{
	assert(AccNum != NULL && "AccNum is NULL, \"getAccountName()\"");
	for (int i = 0; i < g_allALANNums; i++)
	{
		for (int j = 0; j < g_userALNums; j++)
		{
			if (strcmp(g_allAccountsListAndName[0][i], AccNum) == 0)
			{
				strncpy(AccName, g_allAccountsListAndName[1][i], strlen(g_allAccountsListAndName[1][i])+1);
				return AccName;
			}
		}
	}
	return NULL;
}
// ���̵�� ����� ���� ���¸���Ʈ ���� ���� ���� ��ȯ
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
// ���¸���Ʈ ���� �ܾ ���ۿ� �ֱ�. ���� ���� ��ȯ
int setAccListOfAll_malloc()
{
	long CurrentFileOffset = 0;

	int i = 0;
	size_t tempnamelen = 0;
	int AccountNums = 0;
	char* piter = NULL;;
	char* pitertemp = NULL;

	while (1)// ���� ��������
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
		assert(g_allAccountsListAndName[1][k] != NULL && "g_allAcountsListAndName allocation failed");

	}
	CurrentFileOffset = 0;
	i = 0;
	while (i < g_allALANNums) // ���¹�ȣ ���ۿ� ���
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
// ���� Ÿ�� ��ȯ
eAccType getAccType(const char* AccNum)
{
	switch (AccNum[2]) // Ÿ��üũ
	{
	case '1': // ������� ���¸���
		return T1;
		break;
	case '2': // ������ �ϳ�
		return T2;
		break;
	case'3': // ���ݵ� �ϴ� �ϳ�
		return T3;
		break;
	default:
		return 4;
	}
}
