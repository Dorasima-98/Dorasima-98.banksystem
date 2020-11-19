#include "userfunc.h"

// ���¿� �� �ֱ�
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
	assert(g_tempwcp != NULL && "g_tempwcp allocation failed");
	for (int i = 0; i < strlen(desNum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, desNum + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", *(g_tempwcp+1), g_tempwcp);
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
int moneyOutIO(const char* srcNum, const char* desNum, long money, int flag)
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
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", *(g_tempwcp+1), g_tempwcp);
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

	char* toATline = NULL;
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
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\0%c%c.txt", *(g_tempwcp+1), *(g_tempwcp + 1), *(g_tempwcp + 2));
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
	sprintf(toATline, "%s|%s|%ld|%s|%d|%.1f|%ld|", FSatt->FS_name, FSatt->FS_mynum, money, FSatt->FS_Passwords, period, interestrate, balance);
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