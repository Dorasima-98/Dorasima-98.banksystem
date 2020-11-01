//���� ���� �� �Ԥ̤�

#include "userfunc.h"

static int con_flag = 1;
extern int Bank;

int g_userBank;
int g_userALNums;


int serviceMenu()
{
	int menuSelection;
	con_flag = 1;
	system("cls");
	PRINTCEN(L"���� �޴�");
	DRAWLINE('-');

	PRINTLEFT(L"1) ���� ����  2) ���ݰ� ����  3) �Աݰ� ��� ");
	PRINTLEFT(L"4) ���� ��ü  5) ���� ����    6) �α׾ƿ�    7)���� ");
	DRAWLINE('-');
	if (g_userALNums == 0)
	{
		PRINTRIGHT(L"����������... ���� ������ ���°� �ϳ��� �����ʴϴ�. ���� ���� ���� �Ͻ���?");
	}
INVALIDINPUT:
	PRINTLEFT(L"�־��� �޴��� ��ȣ�� �������ּ���. ");
	wprintf(L"> ");

	GET_G_INPUT;
	menuSelection = atoi(g_buffer);
	switch (menuSelection)
	{
	case 1:
		makeAccountMenu();
		break;
	case 2:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"����� ���¸� ���� ����� �ּ���");
			goto INVALIDINPUT;
		}
		fixedDepositAndSavingsMenu();
		break;
	case 3:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"����� ���¸� ���� ����� �ּ���");
			goto INVALIDINPUT;
		}
		atmMenu();

		break;
	case 4:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"����� ���¸� ���� ����� �ּ���");
			goto INVALIDINPUT;
		}
		transferMenu();
		break;
	case 5:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"����� ���¸� ���� ����� �ּ���");
			goto INVALIDINPUT;
		}
		historyInquiry();
		break;
	case 6:
		con_flag = 0;
		g_userBank = 0;
		for (int i = 0; i < g_userALNums; i++)
		{
			free(g_userAccountsList[i]);
			g_userAccountsList[i] = NULL;
		}
		g_userAccountsList = NULL;
		g_userALNums = 0;
		for (int j = 0; j < 17; j++)
		{
			g_userID[j] = 0;
		}
		break;

	case 7:
		con_flag = 0;
		break;
	default:
		goto INVALIDINPUT;
		break;
	}

	if (con_flag == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void makeAccountMenu()
{
	system("cls");

	PRINTCEN(L"���»��� �޴�");
	DRAWLINE('-');

	char* AccountName_malloc = NULL;
	char* PIN1 = NULL;
	char* PIN2 = NULL;
	char* toListfile = NULL;
	char* toTargetfile = NULL;
	wchar_t* temppath = NULL;

	FILE* f_accFile = NULL;

	char ranNum[8] = { 0, };
	char toMemfile[10] = { 0, };
	size_t toLfnums = 0;
	size_t toTfnums = 0;
	int tempPass = 0;

	long CurrentFileOffset = 0;



	PRINTLEFT(L"���� ���� �Է����ּ���.\n> ");
Invalidinput1:
	GET_G_INPUT;

	AccountName_malloc = trim_malloc(AccountName_malloc, g_buffer);
	assert(AccountName_malloc != NULL && "trim is Something wrong...");

	if (strlen(AccountName_malloc) > 16 || strlen(AccountName_malloc) < 1)
	{
		PRINTRIGHT(L"�̸��� ���̴� 1�� ~ 16�� �Դϴ�. �ٽ� �Է����ּ���.\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkAlnum(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"���¸��� ���ĺ��� ���ڷ� �Է� ���ּ���..\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkDupAN(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"������ ������ �ߺ��Ǵ� ���¸��� �ֽ��ϴ�...\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else
	{
		PRINTLEFT(L"���¸��� ����� �Է��߽��ϴ�. \n");
		Sleep(1000);
		system("cls");
	}

	PRINTLEFT(L"���� ��й�ȣ�� �Է����ּ���. 4�ڸ� �����Դϴ�.\n> ");
Invalidinput2:
	GET_G_INPUT;

	PIN1 = trim_malloc(PIN1, g_buffer);
	assert(PIN1 != NULL && "trim is Something wrong...");

	if (strlen(PIN1) > 4 || strlen(PIN1) < 1)
	{
		PRINTRIGHT(L"���¹�ȣ�� ���̴� 4�� �Դϴ�. �ٽ� �Է����ּ���.\n> ");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}

	if (checkDigit(PIN1) == 1)
	{
		PRINTRIGHT(L"���� ��й�ȣ�� 4�ڸ� \"����\"�Դϴ�..\n >");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}
	else if (checkDigit(PIN1) == 2)
	{
		PRINTRIGHT(L"���� ��й�ȣ�� ���̰����� ������� �ʽ��ϴ�.. �ٽ� �Է����ּ���.\n >");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}

	PRINTLEFT(L"���� ��й�ȣ�� �ٽ� �Է����ּ���. \n> ");
Invalidinput3:
	GET_G_INPUT;

	PIN2 = trim_malloc(PIN2, g_buffer);
	assert(PIN2 != NULL && "trim is Something wrong...");
	if (strncmp(PIN2, PIN1, 4) != 0)
	{
		PRINTRIGHT(L"PassWords�� ���� ��ġ���� �ʽ��ϴ�.\n ");
		PRINTLEFT(L"PassWords �� �ٽ��ѹ� �Է��ϼ���. \n> ");
		free(PIN2);
		PIN2 = NULL;
		goto Invalidinput3;
	}

	srand((int)time(NULL));
	ranNum[0] = '0';
	ranNum[1] = g_userBank + '0';
	ranNum[2] = '1';
	for (int k = 3; k < 7; k++)
	{
		ranNum[k] = rand() % 10 + 48;
	}
	ranNum[7] = '\0';

	toLfnums = 11 + strlen(AccountName_malloc);
	toTfnums = 27 + strlen(AccountName_malloc);

	toListfile = (char*)malloc(sizeof(char) * toLfnums);
	toTargetfile = (char*)malloc(sizeof(char) * toTfnums);

	sprintf(toListfile, "%s|%s|\n", ranNum, AccountName_malloc);
	sprintf(toTargetfile, "%s|%s|0|%s|3000000|\n", AccountName_malloc, ranNum, PIN1);



	temppath = (wchar_t*)malloc(sizeof(wchar_t) * ((strlen(ranNum)) + 1)); // �������� �����
	for (int j = 0; j < (strlen(ranNum)) + 1; j++)
	{
		mbtowc(temppath + j, ranNum + j, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, temppath);

	f_accFile = _wfopen(g_wpath, L"a+");
	assert(f_accFile != NULL && "create new account file failed");

	fseek(f_accFile, 0, SEEK_SET); //���������͸� ó����ġ�� �̵���Ű��
	fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_accFile);

	fclose(f_accFile);
	f_accFile = NULL;

	fseek(f_AccountList, 0, SEEK_END);	//���¸���Ʈ ���Ͽ� ���� //���������͸� ���� ���� ������ �̵���Ű��
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList);
	fflush(f_AccountList);

	sprintf(toMemfile, "%s|", ranNum); //toMemfile�� ���¹�ȣ| ���ڿ� �Է�

	CurrentFileOffset = setBankByID(g_userID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(���� ������ + CurrentFileOffset) ��ġ�� ���������� �̵���
	while (fgetc(f_MemberFile) != '\n') //���پ� get�� �Ŷ�� �ǹ�
	{
		CurrentFileOffset++; //�ѱ��� �ѱ��ھ� �б� ����
	}
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(���� ������ + CurrentFileOffset) ��ġ�� ���������� �̵���
	size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_MemberFile);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	fwrite(toMemfile, sizeof(char), strlen(toMemfile), f_MemberFile);
	fwrite(g_filebuff, sizeof(char), numOfWords, f_MemberFile);

	for (int i = 0; i < g_userALNums; i++)
	{
		free(g_userAccountsList[i]);
		g_userAccountsList[i] = NULL;
	}
	g_userAccountsList = NULL;

	setAccListByID_malloc(g_userID);
	setAccListOfAll_malloc();

	// heap corruption�� free�� �� ����ϴ�. �ߴ������� ��ã�� ����
	free(AccountName_malloc);
	AccountName_malloc = NULL;
	free(PIN1);
	PIN1 = NULL;
	free(PIN2);
	PIN2 = NULL;
	free(toListfile);
	toListfile = NULL;
	free(toTargetfile);
	toTargetfile = NULL;
	free(temppath);
	temppath = NULL;


	printf("�����Ϸ�Ǿ����ϴ�.\n");
	printf("> %c%c-%c-%s", ranNum[0], ranNum[1], ranNum[2], &ranNum[3]);

	system("pause");

	return;
}
void fixedDepositAndSavingsMenu()
{
	int selection;

	system("cls");
	PRINTCEN(L"���ݰ� ���� �޴�");
	DRAWLINE('-');
	PRINTLEFT(L"1) ������ ��ǰ ��û  2) ������ ��ǰ ������ȸ �� ����");
INVALIDINPUT:
	PRINTLEFT(L"�־��� �޴��� ��ȣ�� �Է��ϼ���.");
	wprintf(L"> ");

	GET_G_INPUT;

	selection = atoi(g_buffer);

	switch (selection)
	{
	case 1:
		while (1)
		{
			system("cls");
			PRINTLEFT(L"1) ����	2) ����");
			GET_G_INPUT;
			
			if (atoi(g_buffer) == 1 || atoi(g_buffer) == 2)
			{
				fixedDepositAndSavings(atoi(g_buffer));
				goto ESCAPE;
			}
		}
	ESCAPE:
		return;
	case 2:
		inquiryAndCancel();
		return;
	default:
		goto INVALIDINPUT;
	}
}
void fixedDepositAndSavings(int intype)
{
	int uIONums = 0;
	int selection;
	int money = 0;
	long recieved = 0;
	long limit = 0;
	long CurrentFileOffset = 0;
	long expectedmoney = 0;

	char** temp = NULL;
	char tempname[17];
	char* inputcheck = NULL;

	char toListfile[27];
	char* toTargetfile;
	char toMemfile[10];

	FILE* f_IO = NULL;
	FILE* f_fixFile = NULL;
	IOattributes_malloc_t* IOatt = NULL;
	FSattributes_t* Fixatt = NULL;

	Fixatt = (FSattributes_t*)malloc(sizeof(FSattributes_t));
	IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

	temp = (char**)malloc(sizeof(char*) * g_userALNums);
	PRINTCEN(L"���� ����� ����� ���¸� �������ּ���.");
	for (int i = 0; i < g_userALNums; i++)
	{
		if (getAccType(g_userAccountsList[i]) == T1)
		{
			uIONums++;
			getAccountName(g_userAccountsList[i], tempname);
			temp[uIONums] = g_userAccountsList[i];
			printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
			memset(IOatt->IO_name, '\0', 17);
		}
	}
	printf("> ");
INVALIDINPUT1:
	if (scanf("%d", &selection) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
		goto INVALIDINPUT1;

	}
	if (1 <= selection && selection <= uIONums)
	{
		PRINTLEFT(L"���°� ���õǾ����ϴ�\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else
	{
		PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
		while (getchar() != '\n');
		goto INVALIDINPUT1;
	}
	strncpy(IOatt->IO_mynum, temp[selection], 8);
	free(temp);
	temp = NULL;

	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}

	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
	for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
	free(g_tempwcp);
	g_tempwcp = NULL;

	f_IO = _wfopen(g_wpath, L"r+");
	IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
	fgets(g_buffer, BUFF_SIZE, f_IO);
	strToIOatt_malloc(g_buffer, IOatt);


	srand((int)time(NULL));
	Fixatt->FS_mynum[0] = '0';
	Fixatt->FS_mynum[1] = g_userBank + '0';
	if (intype == 1)
	{
		Fixatt->FS_mynum[2] = '2';
	}
	else
	{
		Fixatt->FS_mynum[2] = '3';
	}
	
	for (int k = 3; k < 7; k++)
	{
		Fixatt->FS_mynum[k] = rand() % 10 + 48;
	}
	Fixatt->FS_mynum[7] = '\0';

	PRINTCEN(L"���¸� �Է�");
	DRAWLINE('-');
	wprintf(L"���¸��� �Է����ּ���.\n");
	wprintf(L"> ");
INVALIDINPUT2:
	GET_G_INPUT;

	inputcheck = trim_malloc(inputcheck, g_buffer);
	assert(inputcheck != NULL && "trim is Something wrong...");

	if (strlen(inputcheck) > 16 || strlen(inputcheck) < 1)
	{
		PRINTRIGHT(L"�̸��� ���̴� 1�� ~ 16�� �Դϴ�. �ٽ� �Է����ּ���.\n");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}

	else if (strlen(inputcheck) == 1 && isdigit(*inputcheck) == 1)
	{
		PRINTRIGHT(L"�� ���ڷ� �����Ͻ÷��� ���ĺ����� �Է� ���ּ���...\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}
	else if (checkAlnum(inputcheck) == 1)
	{
		PRINTRIGHT(L"���¸��� ���ĺ� �⺻, ���� �������� �Է� ���ּ���..\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}
	else if (checkDupAN(inputcheck) == 1)
	{
		PRINTRIGHT(L"������ ������ �ߺ��Ǵ� ���¸��� �ֽ��ϴ�...\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}
	else
	{
		PRINTLEFT(L"���¸��� ����� �Է��߽��ϴ�. \n");
		Sleep(1000);
		strncpy(Fixatt->FS_name, inputcheck, strlen(inputcheck) + 1);
		free(inputcheck);
		inputcheck = NULL;
		system("cls");
	}
	printf("���� ���¸��� %s�� �����Ǿ����ϴ�\n", Fixatt->FS_name);


	PRINTLEFT(L"���� ��й�ȣ�� �Է����ּ���. 4�ڸ� �����Դϴ�.\n> ");
INVALIDINPUT3:
	GET_G_INPUT;

	inputcheck = trim_malloc(inputcheck, g_buffer);
	assert(inputcheck != NULL && "trim is Something wrong...");


	if (strlen(inputcheck) > 4 || strlen(inputcheck) < 1)
	{
		PRINTRIGHT(L"���¹�ȣ�� ���̴� 4�� �Դϴ�. �ٽ� �Է����ּ���.\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT3;
	}
	if (checkDigit(inputcheck) == 1)
	{
		PRINTRIGHT(L"���� ��й�ȣ�� 4�ڸ� \"����\"�Դϴ�..\n >");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT3;
	}
	else if (checkDigit(inputcheck) == 2)
	{
		PRINTRIGHT(L"���� ��й�ȣ�� ���̰����� ������� �ʽ��ϴ�.. �ٽ� �Է����ּ���.\n >");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT3;
	}
	strncpy(Fixatt->FS_Passwords, inputcheck, strlen(inputcheck) + 1);

	PRINTLEFT(L"���� ��й�ȣ�� �ٽ� �Է����ּ���. \n> ");
Invalidinput4:
	GET_G_INPUT;

	inputcheck = trim_malloc(inputcheck, g_buffer);
	assert(inputcheck != NULL && "trim is Something wrong...");
	if (strncmp(inputcheck, Fixatt->FS_Passwords, 4) != 0)
	{
		PRINTRIGHT(L"PassWords�� ���� ��ġ���� �ʽ��ϴ�.\n ");
		PRINTLEFT(L"PassWords �� �ٽ��ѹ� �Է��ϼ���. \n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto Invalidinput4;
	}
	PRINTLEFT(L"���� ��й�ȣ�� ������ �Ǿ����ϴ�. \n> ");

	//�ϴ� ���Ͽ� ����α�

	toTargetfile = (char*)malloc(sizeof(FSattributes_t));
	sprintf(toListfile, "%s|%s|\n", Fixatt->FS_mynum, Fixatt->FS_name);
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\0%d%d.txt", g_userBank, g_userBank, intype+1);

	f_fixFile = _wfopen(g_wpath, L"r+");
	assert(f_fixFile != NULL && "\nfile opening is failed.");

	fseek(f_fixFile, 0, SEEK_SET);
	if (intype == 1)
	{
		if (fgetc(f_fixFile) != EOF)
		{
			sprintf(toTargetfile, "%s|%s|0|%s|0|0.0|0| ", Fixatt->FS_name, Fixatt->FS_mynum, Fixatt->FS_Passwords);
			fseek(f_fixFile, 0, SEEK_SET);
			size_t numOfread = fread(g_filebuff, sizeof(char), FILE_BUFF, f_fixFile);
			fseek(f_fixFile, 0, SEEK_SET);
			fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_fixFile);
			fwrite(g_filebuff, sizeof(char), numOfread, f_fixFile);
		}
		else
		{
			sprintf(toTargetfile, "%s|%s|0|%s|0|0.0|0|\n", Fixatt->FS_name, Fixatt->FS_mynum, Fixatt->FS_Passwords);
			fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_fixFile);
		}
	}
	else
	{
		if (fgetc(f_fixFile) != EOF)
		{
			sprintf(toTargetfile, "%s|%s|500000|%s|0|0.0|0| ", Fixatt->FS_name, Fixatt->FS_mynum, Fixatt->FS_Passwords);
			fseek(f_fixFile, 0, SEEK_SET);
			size_t numOfread = fread(g_filebuff, sizeof(char), FILE_BUFF, f_fixFile);
			fseek(f_fixFile, 0, SEEK_SET);
			fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_fixFile);
			fwrite(g_filebuff, sizeof(char), numOfread, f_fixFile);
		}
		else
		{
			sprintf(toTargetfile, "%s|%s|500000|%s|0|0.0|0|\n", Fixatt->FS_name, Fixatt->FS_mynum, Fixatt->FS_Passwords);
			fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_fixFile);
		}
	}
	

	fclose(f_fixFile);
	f_fixFile = NULL;

	//����Ʈ���Ͽ� ����α�
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList);
	fflush(f_AccountList);

	sprintf(toMemfile, "%s|", Fixatt->FS_mynum);

	//������Ͽ� ����α�
	CurrentFileOffset = setBankByID(g_userID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	while (fgetc(f_MemberFile) != '\n')
	{
		CurrentFileOffset++;
	}
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_MemberFile);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	fwrite(toMemfile, sizeof(char), strlen(toMemfile), f_MemberFile);
	fwrite(g_filebuff, sizeof(char), numOfWords, f_MemberFile);

	for (int i = 0; i < g_userALNums; i++)
	{
		free(g_userAccountsList[i]);
		g_userAccountsList[i] = NULL;
	}
	g_userAccountsList = NULL;

	setAccListByID_malloc(g_userID);
	setAccListOfAll_malloc();

	system("cls");
	PRINTCEN(L"������ ����");
	DRAWLINE('-');
	PRINTCEN(L"===���Ͻô� ���񽺸� �������ּ���===");
	PRINTLEFT(L"������  1) 6����(1.0%)   2) 1��(1.5%)   3) 2��(2.0%)");
INVALIDINPUT5:
	wprintf(L"> ");

	if (scanf("%d", &selection) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"�ٽ� �������ּ���\n");
		goto INVALIDINPUT5;

	}
	if (1 <= selection && selection <= 3)
	{
		PRINTLEFT(L"���õǾ����ϴ�\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else
	{
		PRINTRIGHT(L"�ٽ� �������ּ���.\n");
		while (getchar() != '\n');
		goto INVALIDINPUT3;
	}

	PRINTCEN(L"���Ծ� �Է�");
	DRAWLINE('-');

	PRINTCEN(L"===������ ������ ���Ծ�(��ġ��)�� �Է����ּ���===");
	PRINTLEFT(L"**Ȯ�λ���**");
	PRINTLEFT(L"���� : �� ���Ծ� �ѵ��� ��� 50�������� ������ �˴ϴ�.");
	PRINTLEFT(L"���� : ��ġ�� �ѵ��� ��� ���� ����ݰ��� �ܾ��Դϴ�.");
	PRINTLEFT(L"(���� : 1����)");
	limit = atol(IOatt->IO_balance);
	wprintf(L"���� ��� ���ɱݾ�: %ld (��)", limit);
INVALIDINPUT6:
	wprintf(L"> ");

	if (scanf("%d", &money) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"�ٽ� �Է����ּ���\n");
		goto INVALIDINPUT6;

	}
	if (intype == 1)
	{
		if (1 <= money && (money * 10000) <= limit)
		{
			PRINTLEFT(L"�ԷµǾ����ϴ�.\n");
			while (getchar() != '\n');
			Sleep(1000);
			system("cls");
		}
		else
		{
			PRINTRIGHT(L"�Ѿ��..\n");
			while (getchar() != '\n');
			goto INVALIDINPUT6;
		}
	}
	else 
	{
		if (1 <= money && (money * 10000) <= 500000 && (money * 10000) <= limit)
		{
			PRINTLEFT(L"�ԷµǾ����ϴ�.\n");
			while (getchar() != '\n');
			Sleep(1000);
			system("cls");
		}
		else
		{
			PRINTRIGHT(L"�Ѿ��...\n");
			while (getchar() != '\n');
			goto INVALIDINPUT6;
		}
	}

	moneyOutIO(IOatt->IO_mynum, Fixatt->FS_mynum, money * 10000, 1); //flag�� 1�� �Ѱ��ָ� ��ü�ѵ� ����
	moneyInFS(Fixatt->FS_mynum, money * 10000, selection);

	wprintf(L"��û�� �Ϸ�Ǿ����ϴ�.\n");
	Sleep(1000);

	freeIOattriutes(IOatt);
	free(IOatt);
	free(Fixatt);
	free(toTargetfile);
	toTargetfile = NULL;
	IOatt = NULL;
	Fixatt = NULL;
	fclose(f_IO);
	f_IO = NULL;
#if TEST_OFF
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //������
	int duration; //���� �Ⱓ(6�����̸� 6, 1���̸� 1, 2���̸� 2)
	float fixedDepositMoney = 0.0; //��ġ��(���Ծ�)
	float finalFixedDepositMoney = 0.0; //����������
	char accountName[10]; //���ݰ��¸�

	wchar_t* temppath = NULL;
	FILE* f_accFile = NULL;
	char* toListfile = NULL;
	char* toTargetfile = NULL;
	size_t toLfnums = 0;
	size_t toTfnums = 0;

	system("cls");
	PRINTCEN(L"����� ���� ����");
	DRAWLINE('-');
	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	// �ش� ����ã�ư���
	if (tempwcp != NULL)
	{
		free(tempwcp);
		tempwcp = NULL;
	}

	tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * 8); //8�³�..
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", tempwcp[1], tempwcp);

	inputFile = _wfopen(g_wpath, L"r");

	int accountSelection = 0;

	if (inputFile != NULL)
	{
		char buffer[1024]; //���߿� �����ؾ���
		while (!feof(inputFile))
		{
			fgets(buffer, sizeof(buffer), inputFile);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			printf("%s\n", ptr);
			while (ptr != NULL)
			{
				ptr = strtok(NULL, "\n");
			}
		}
	}

	scanf("%d", &accountSelection); //����ݰ��� �����ϱ�
	//�����ؼ� �� ����ݰ��� ���� �����;� �� - �����ؾ���

	fclose(inputFile);

	//���࿡ �°� ���¹�ȣ �����ϱ�
	char ranNum[8] = { 0, };

	srand(time(NULL));
	ranNum[0] = '0';
	ranNum[1] = g_userBank + '0';
	ranNum[2] = '1';
	for (int k = 3; k < 7; k++)
	{
		ranNum[k] = rand() % 10 + 48;
	}
	ranNum[7] = '\0';

	toLfnums = 50; //�ϴ� �� ���� ����,,,
	toTfnums = 80; //�̰ŵ�

	toListfile = (char*)malloc(sizeof(char) * toLfnums);
	toTargetfile = (char*)malloc(sizeof(char) * toTfnums);

	PRINTCEN(L"���¸� �Է�");
	DRAWLINE('-');
	printf("���� ���¸��� �Է����ּ���.\n");
	wprintf(L"> ");
	scanf("%s", &accountName);
	printf("���� ���¸��� %s�� �����Ǿ����ϴ�\n", accountName);
	system("pause");

	system("cls");
	PRINTCEN(L"������ ����");
	DRAWLINE('-');
	PRINTCEN(L"===������ ������ �������� �������ּ���===");
	PRINTLEFT(L"������  1) 6����(1.0%)   2) 1��(1.5%)   3) 2��(2.0%)");
	wprintf(L"> ");

	int selection = 0;

	scanf_s("%d", &selection, 1);

	//printf�� �׳� Ȯ�ο��̶� �� ������. rate�� ���߿� �������� ù �ٿ� ����� ��
	switch (selection)
	{
	case 1:
		rate = 1.0;
		duration = 6;
		//printf("6���� ���ÿϷ�\n");
		break;

	case 2:
		rate = 1.5;
		duration = 1;
		//printf("1�� ���ÿϷ�\n");
		break;

	case 3:
		rate = 2.0;
		duration = 2;
		//printf("2�� ���ÿϷ�\n");
		break;
	}

	system("pause");
	system("cls");
	PRINTCEN(L"���Ծ� �Է�");
	DRAWLINE('-');

	PRINTCEN(L"===������ ������ ���Ծ�(��ġ��)�� �Է����ּ���===");
	PRINTLEFT(L"**Ȯ�λ���**");
	PRINTLEFT(L"���� : �� ���Ծ� �ѵ��� ��� 50�������� ������ �˴ϴ�.");
	PRINTLEFT(L"���� : ��ġ�� �ѵ��� ��� ���� ����ݰ��� �ܾ��Դϴ�.");
	PRINTLEFT(L"(���� : 1����)");
	wprintf(L"> ");

	scanf("%f", &fixedDepositMoney);

	//���� �Ʊ� ������ ����ݰ��� �ܾ׺��� ������ ������, 1�� �̻����� if�� �־�� ��!!

	//������ɾ� ����ϱ�
	switch (selection)
	{
	case 1:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.01 * 0.5;
		//printf("������ɾ��� %.5f���� �Դϴ�.\n", finalFixedDepositMoney);
		break;

	case 2:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.015;
		//printf("������ɾ��� %.5f���� �Դϴ�.\n", finalFixedDepositMoney);
		break;

	case 3:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.02 * 2;
		//printf("������ɾ��� %.5f���� �Դϴ�.\n", finalFixedDepositMoney);
		break;
	}

	int accountPassword = 1234; //����ݰ��¿��� �޾ƿ��� - �����ؾ���.

	system("pause");

	//������� ����
	temppath = (wchar_t*)malloc(sizeof(wchar_t) * ((strlen(ranNum)) + 1)); // �������� �����
	for (int j = 0; j < (strlen(ranNum)) + 1; j++)
	{
		mbtowc(temppath + j, ranNum + j, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, temppath);

	f_accFile = _wfopen(g_wpath, L"a+");
	assert(f_accFile != NULL && "create new account file failed");

	fseek(f_accFile, 0, SEEK_SET); //���������͸� ó����ġ�� �̵���Ű��
	fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_accFile);

	fclose(f_accFile);
	f_accFile = NULL;

	fseek(f_AccountList, 0, SEEK_END);	//���¸���Ʈ ���Ͽ� ���� //���������͸� ���� ���� ������ �̵���Ű��
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList);
	fflush(f_AccountList);

	sprintf(toMemfile, "%s|", ranNum); //toMemfile�� ���¹�ȣ| ���ڿ� �Է�

	CurrentFileOffset = setBankByID(g_userID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(���� ������ + CurrentFileOffset) ��ġ�� ���������� �̵���
	while (fgetc(f_MemberFile) != '\n') //���پ� get�� �Ŷ�� �ǹ�
	{
		CurrentFileOffset++; //�ѱ��� �ѱ��ھ� �б� ����
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(���� ������ + CurrentFileOffset) ��ġ�� ���������� �̵���
	}
	fseek(f_MemberFile, CurrentFileOffset + 1, SEEK_SET);

	size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_MemberFile);
	fseek(f_MemberFile, CurrentFileOffset + 1, SEEK_SET);
	fwrite(toMemfile, sizeof(char), strlen(toMemfile), f_MemberFile);
	fwrite(g_filebuff, sizeof(char), numOfWords, f_MemberFile);

	for (int i = 0; i < g_userALNums; i++)
	{
		free(g_userAccountsList[i]);
		g_userAccountsList[i] = NULL;
	}
	g_userAccountsList = NULL;

	setAccListByID_malloc(g_userID);
	setAccListOfAll_malloc();

	free(AccountName_malloc);
	AccountName_malloc = NULL;
	free(PIN1);
	PIN1 = NULL;
	free(PIN2);
	PIN2 = NULL;
	free(toListfile);
	toListfile = NULL;
	free(toTargetfile);
	toTargetfile = NULL;
	free(temppath);
	temppath = NULL;

	//������� ������ ��. �����ؾ� ��


	//������ �ٿ��� "�߰��� ��������" �� 
	inputFile = fopen("fixed.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%f\n", accountName, ranNum, finalFixedDepositMoney, fixedDepositMoney);
	fclose(inputFile);

	//ù �ٿ��� "���¸�, ���¹�ȣ, new![����� ���ɾ�], ���� ��й�ȣ, ���� ��û�Ⱓ, ������, ���� �� ���ɾ��� ����"�� ��!
	//�ش� ���� �ܾ�, ���� ��й�ȣ�� ���� ���� ���ؼ� �װ� ���� �������� ù �ٿ� ��
	inputFile = fopen("fixed_shortcut.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%d|%d|%f|%f ", accountName, finalFixedDepositMoney, fixedDepositMoney, accountPassword, duration, rate, fixedDepositMoney);
	fclose(inputFile);

	//Q_CHECK();
	//wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	//system("pause");
#endif
}
void inquiryAndCancel() //Cancel �� �ϱ�~~~
{
	FILE* inputFile = NULL;

	/*
	char accountName[6];

	char account[7];
	char finalDate[8];
	int money = 0; //���⿡ �ݾ��� �޾ƿ��� ������ ��� ���� �𸣰ڴ�,,

	system("cls");
	PRINTCEN(L"���� Ȯ�� �� ����");
	DRAWLINE('-');
	PRINTLEFT(L"���� �Ǵ� ���� ���¹�ȣ 7�ڸ��� ������������ 8�ڸ�(yyyymmdd)�� ������� �Է����ּ���");
	wprintf(L"> ");
	//7�ڸ��� ���¹�ȣ, �� ���� 8�ڸ��� ������������

	GET_G_INPUT;
	if (*g_buffer == ':')
	{
		if (*(g_buffer + 1) == 'q')
		{
			wprintf(L"�ڷΰ��� �Է��� :q\n"); system("pause");
			goto ESCAPE;
		}
	}

	for (int i=0; i<8; i++) {
		account[i] = *(g_buffer + i);
		printf("%c", account[i]);
	}
	printf("\n");
	for (int j = 0; j < 9; j++) {
		finalDate[j] = *(g_buffer + (j + 8));
		printf("%c", finalDate[j]);
	}
	system("pause"); //�Է¹����� �� ����Ƴ� Ȯ���Ϸ��� pause�ص�. printf�Լ��� ���߿� �� ������ ��.

	//���� �Ǵ� ���ݰ��� ���Ͽ��� string �޾ƿ���(|�� �׸� ����)
	inputFile = fopen("fixed.txt", "r"); //�ϴ� �׽�Ʈ�� ���Ϸ� �غ���
	if (inputFile != NULL) {
		char buffer[256]; //���߿� �����ؾ���
		while (!feof(inputFile)) {
			fgets(buffer, sizeof(buffer), inputFile);
			char* ptr = strtok(buffer, "|");
			while (ptr != NULL) {
				printf("%s\n", ptr); //�� ���� Ȯ�ο�(���߿� ������ ��)
				ptr = strtok(NULL, "|");
			}
			if (ptr == account) {
				//���¹�ȣ�� ������, ���� ptr �޾Ƽ� �����ϰ� loop Ż��
				//������ ��� �ش��ϴ� ���¿� ���� ���������� �ݾ��� �޾ƿ�
				//������ ��� �ش��ϴ� ���¿� ���� �Աݾ��� �޾ƿ�
				money = 1;
				printf("%d\n", money);
			}
		}
	}

	fclose(inputFile);
	printf("%d\n", money); //������ ��. �׽�Ʈ�Ѵٰ� ���� ��
	system("pause");

	system("cls");
	PRINTCEN(L"������ ������ȸ");
	DRAWLINE('-');
	//�Է¹��� ������������(8~15�ڸ�) ��
	wprintf(L"��û�� ��¥/����� �Ⱓ/��������/�������ɱݾ�"); //�̰͵� ���� ������ ��µž���. ���߿� �ٲٱ�
	printf("\n");
	system("pause");

	system("cls");
	//�ȳ�
	*/

	PRINTCEN(L"������ ����");
	DRAWLINE('-');
	PRINTLEFT(L"�������� �����Ͻðڽ��ϱ�?(y/n)");
	wprintf(L"> ");
	GET_G_INPUT;

	if (*g_buffer == 'y' || *g_buffer == 'Y')
	{
		wprintf(L"�ش� ������ ���¸� �����߽��ϴ�. ");
		system("pause");
		//�������� ���� �Լ� �ʿ�, ������ ����ݰ��¿� �� �Աݵ� �ؾ���
	}
	else if (*g_buffer == 'n' || *g_buffer == 'N')
	{
		wprintf(L"�ش� ������ ���¸� �������� �ʾҽ��ϴ�. ");
		system("pause");
	}
	else
	{
		goto INVALIDINPUT;
	}

INVALIDINPUT:
	return; //�ؾ���
//ESCAPE:
	return; //�ؾ���

}
void atmMenu()
{
	char** temp = NULL;
	char tempname[17];
	char* inputcheck = NULL;

	FILE* f_IO = NULL;
	IOattributes_malloc_t* IOatt = NULL;

	int selection = 0;
	size_t uIONums = 0;

	system("cls");
	PRINTCEN(L"atm menu");
	DRAWLINE('-');

	while (1)
	{
		int atmsel;
		wprintf(L"1. �Ա�\t 2. ���\n");
		wprintf(L"> ");
	INVALIDINPUT0:
		if (scanf("%d", &atmsel) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
		{
			while (getchar() != '\n');
			PRINTRIGHT(L"�޴��� �ٽ� �������ּ���..\n");
			goto INVALIDINPUT0;

		}
		if (1 <= atmsel && atmsel <= 2)
		{
			while (getchar() != '\n');
			//Sleep(1000);
			system("cls");
		}
		else
		{
			PRINTRIGHT(L"�޴��� �ٽ� �������ּ���.\n");
			while (getchar() != '\n');
			goto INVALIDINPUT0;
		}
		if (atmsel == 1)
		{
			PRINTLEFT(L"�ӱ� ���� �Ǿ����ϴ�.\n");

			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

			temp = (char**)malloc(sizeof(char*) * g_userALNums);
			PRINTCEN(L"�Ա� ������ ����� ���� ����Դϴ�.");
			for (int i = 0; i < g_userALNums; i++)
			{
				if (getAccType(g_userAccountsList[i]) == T1)
				{
					uIONums++;
					getAccountName(g_userAccountsList[i], tempname);
					temp[uIONums] = g_userAccountsList[i];
					printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
					memset(IOatt->IO_name, '\0', 17);
				}
			}
			printf("> ");

			// ����� ���� ��� �����ֱ� �����ؾ���
			/*
			FILE* inputFile = NULL;
			inputFile = fopen("ioaccount.txt", "r");
			int lineCount = 1;
			if (inputFile != NULL)
			{
				char buffer[256]; //���߿� �����ؾ���
				while (!feof(inputFile))
				{
					fgets(buffer, sizeof(buffer), inputFile);
					printf("%d)", lineCount++);
					char* ptr = strtok(buffer, "\n");
					while (ptr != NULL)
					{
						printf("%s\n", ptr);
						ptr = strtok(NULL, "\n");
					}
				}
			}
			fclose(inputFile);
			*/
			char input[100] = { "" };
			char* tok[3] = { NULL, };

			while (1)
			{
				wprintf(L"�Ա��� ���¿� ������ ��ȣ / ���� ��й�ȣ / �Ա��� �ݾ��� �Է��ϼ��� (/�� ����)\n");
				while (scanf("%s", &input) != 1)
				{
					while (getchar() != '\n');
					PRINTRIGHT(L"�ٽ� �Է����ּ���.\n");
				}
				char* ptr = strtok(input, "/");

				int i = 0;
				while (ptr != NULL)
				{
					tok[i] = ptr;
					i++;
					ptr = strtok(NULL, "/");
				}

				//����ƴ��� üũ, ��������
				printf("num: %s\n", tok[0]);
				printf("pw: %s\n", tok[1]);
				printf("inmoney: %s\n", tok[2]);

				if (checkDigit(tok[0]) != 0 && checkDigit(tok[1]) != 0 && checkDigit(tok[2]) != 0)
				{
					wprintf(L"���ڸ� �Է����ּ���.\n"); // 12.1.1)
				}
				else if (atol(tok[2]) <= 0)
				{
					wprintf(L"�Ա��� �ݾ��� 1�� �̻��̾�� �մϴ�.\n"); // 12.1.5)
				}
				else if (strcmp(IOatt->IO_Passwords, tok[1]) != 0)
				{
					wprintf(L"��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
				}
				else
				{
					strncpy(IOatt->IO_mynum, temp[atoi(tok[0])], 8);
					free(temp);
					temp = NULL;

					if (g_tempwcp != NULL)
					{
						free(g_tempwcp);
						g_tempwcp = NULL;
					}

					g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
					for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
					{
						mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
					}
					swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
					free(g_tempwcp);
					g_tempwcp = NULL;

					f_IO = _wfopen(g_wpath, L"r+");
					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					fgets(g_buffer, BUFF_SIZE, f_IO);
					strToIOatt_malloc(g_buffer, IOatt);

					moneyInIO(IOatt->IO_mynum, NULL, (atol(tok[2])));
					wprintf(L"���¿� %s���� �Ա��Ͽ����ϴ�", tok[2]);
					break;
				}
			}
			break;
		}
		else if (atmsel == 2)
		{
			PRINTLEFT(L"��� ���� �Ǿ����ϴ�.\n");
			IOattributes_malloc_t* IOatt = NULL;

			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

			temp = (char**)malloc(sizeof(char*) * g_userALNums);
			assert(temp != NULL && "temp allocation failed in fucntion...\"atm()\"");
			PRINTCEN(L"��� ������ ����� ���¸���Դϴ�.");
			for (int i = 0; i < g_userALNums; i++)
			{
				if (getAccType(g_userAccountsList[i]) == T1)
				{
					uIONums++;
					getAccountName(g_userAccountsList[i], tempname);
					temp[uIONums] = g_userAccountsList[i];
					printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
					memset(IOatt->IO_name, '\0', 17);
				}
			}
			printf("> ");

			char input2[100] = { "" };
			char* tok2[3] = { NULL, };

			while (1)
			{
				wprintf(L"����� ���¿� ������ ��ȣ / ���� ��й�ȣ / ��ݾ��� �Է��ϼ��� (/�� ����)\n");
				while (scanf("%s", &input2) != 1)
				{
					while (getchar() != '\n');
					PRINTRIGHT(L"�ٽ� �Է����ּ���.\n");
				}
				char* ptr = strtok(input2, "/");

				int i = 0;
				while (ptr != NULL)
				{
					tok2[i] = ptr;
					i++;
					ptr = strtok(NULL, "/");
				}

				//����ƴ��� üũ, ��������
				printf("num: %s\n", tok2[0]);
				printf("pw: %s\n", tok2[1]);
				printf("outmoney: %s\n", tok2[2]);

				if (checkDigit(tok2[0]) != 0 && checkDigit(tok2[1]) != 0 && checkDigit(tok2[2]) != 0)
				{
					wprintf(L"���ڸ� �Է����ּ���.\n"); // 12.2.1)
				}
				else if (atol(tok2[2]) <= 0)
				{
					wprintf(L"����� �ݾ��� 1�� �̻��̾�� �մϴ�.\n"); // 12.2.5)
				}
				else if (atol(tok2[2]) >= 3000000)
				{
					wprintf(L"��ݾ� �ѵ��� �ʰ��Ͽ����ϴ�.\n"); // 12.2.7) , �����ѵ� �߰��ؾ���
				}
				else if (strcmp(IOatt->IO_Passwords, tok2[1]) != 0)
				{
					wprintf(L"��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
				}
				else
				{
					strncpy(IOatt->IO_mynum, temp[atoi(tok2[0])], 8);
					free(temp);
					temp = NULL;

					if (g_tempwcp != NULL)
					{
						free(g_tempwcp);
						g_tempwcp = NULL;
					}

					g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
					for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
					{
						mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
					}
					swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
					free(g_tempwcp);
					g_tempwcp = NULL;

					f_IO = _wfopen(g_wpath, L"r+");
					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					fgets(g_buffer, BUFF_SIZE, f_IO);
					strToIOatt_malloc(g_buffer, IOatt);



					if (moneyOutIO(IOatt->IO_mynum, NULL, (atol(tok2[2])), 0) == 0)
					{
						wprintf(L"��ü�ѵ��� �Ѵ� �ݾ��Դϴ�.\n");
						break;
					}
					else
					{
						wprintf(L"���¿��� %s���� ����Ͽ����ϴ�\n", tok2[2]);
						break;
					}
				}
			}
			break;
		}
		else
		{
			getchar();
			printf("�ٽ� �Է��ϼ���\n");
		}
	}
	if (IOatt != NULL)
	{
		free(IOatt);
		IOatt = NULL;
	}


	system("pause");
}
void transferMenu()
{
	char** temp = NULL;
	char tempname[17];
	char* inputcheck = NULL;

	FILE* f_IO = NULL;
	IOattributes_malloc_t* IOatt = NULL;
	IOattributes_malloc_t* IOatt2 = NULL;
	FSattributes_t* FSatt = NULL;

	int selection = 0;
	int flag = 0;
	size_t uIONums = 0;
	long CurrentFileOffset = 0;

	system("cls");
	PRINTCEN(L"atm menu");
	DRAWLINE('-');

	while (1)
	{
		int transel;
		wprintf(L"1. ������ü\t 2. �ڵ���ü\n");
	INVALIDINPUT0:
		if (scanf("%d", &transel) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
		{
			while (getchar() != '\n');
			PRINTRIGHT(L"�޴��� �ٽ� �������ּ���..\n");
			goto INVALIDINPUT0;

		}
		if (1 <= transel && transel <= 2)
		{
			while (getchar() != '\n');
			//Sleep(1000);
			system("cls");
		}
		else
		{
			PRINTRIGHT(L"�޴��� �ٽ� �������ּ���.\n");
			while (getchar() != '\n');
			goto INVALIDINPUT0;
		}
		if (transel == 1)
		{
			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
			temp = (char**)malloc(sizeof(char*) * g_userALNums);
			PRINTCEN(L"���� ����� ����� ���¸� �������ּ���.");
			for (int i = 0; i < g_userALNums; i++)
			{
				if (getAccType(g_userAccountsList[i]) == T1)
				{
					uIONums++;
					getAccountName(g_userAccountsList[i], tempname);
					temp[uIONums] = g_userAccountsList[i];
					printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
					memset(IOatt->IO_name, '\0', 17);
				}
			}
			printf("> ");
		INVALIDINPUT1:
			if (scanf("%d", &selection) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
			{
				while (getchar() != '\n');
				PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
				goto INVALIDINPUT1;

			}
			if (1 <= selection && selection <= uIONums)
			{
				PRINTLEFT(L"���°� ���õǾ����ϴ�\n");
				while (getchar() != '\n');
				Sleep(1000);
				system("cls");
			}
			else
			{
				PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
				while (getchar() != '\n');
				goto INVALIDINPUT1;
			}
			strncpy(IOatt->IO_mynum, temp[selection], 8);
			free(temp);
			temp = NULL;

			if (g_tempwcp != NULL)
			{
				free(g_tempwcp);
				g_tempwcp = NULL;
			}

			g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
			for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
			{
				mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
			}
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
			free(g_tempwcp);
			g_tempwcp = NULL;

			f_IO = _wfopen(g_wpath, L"r+");
			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
			fgets(g_buffer, BUFF_SIZE, f_IO);
			strToIOatt_malloc(g_buffer, IOatt);
			fclose(f_IO);
			f_IO = NULL;
			char input3[100] = { "" };
			char* tok3[3] = { NULL, };

			while (1)
			{
				wprintf(L"�Ա��� ���� ��ȣ / ��� ���� ��й�ȣ / �Ա��� �ݾ��� �Է��ϼ��� (/�� ����)\n");
				wprintf(L"��� ������ �ܾ� / ��ü�ѵ� :\t");
				printf("%s / %s\n", IOatt->IO_balance, IOatt->IO_dateLimits);
				while (scanf("%s", &input3) != 1)
				{
					while (getchar() != '\n');
					PRINTRIGHT(L"�ٽ� �Է����ּ���.\n");
				}
				char* ptr = strtok(input3, "/");

				int i = 0;
				while (ptr != NULL)
				{
					tok3[i] = ptr;
					i++;
					ptr = strtok(NULL, "/");
				}

				//����ƴ��� üũ, ��������
				printf("num: %s\n", tok3[0]);
				printf("pw: %s\n", tok3[1]);
				printf("inmoney: %s\n", tok3[2]);

				if (checkDigit(tok3[0]) != 0 && checkDigit(tok3[1]) != 0 && checkDigit(tok3[2]) != 0)
				{
					wprintf(L"���ڸ� �Է����ּ���.\n"); // 12.1.1)
				}
				else if (atol(tok3[2]) <= 0)
				{
					wprintf(L"�Ա��� �ݾ��� 1�� �̻��̾�� �մϴ�.\n"); // 12.1.5)
				}
				else if (strcmp(IOatt->IO_Passwords, tok3[1]) != 0)
				{
					wprintf(L"��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
				}
				else if (atol(tok3[2]) > atol(IOatt->IO_dateLimits))
				{
					wprintf(L"��ü �ѵ����� ���� �ݾ��� ��ü�ؾ� �մϴ�.\n");
				}
				else
				{
					moneyOutIO(IOatt->IO_mynum, tok3[0], (atol(tok3[2])), 0);
					switch (getAccType(tok3[0]))
					{
					case T1:
						moneyInIO(tok3[0], IOatt->IO_mynum, (atol(tok3[2])));
						PRINTLEFT(L"��ü �Ǿ����ϴ�.");
						break;
					case T3:
						if (moneyInFS(tok3[0], (atol(tok3[2])), 0) == 1)
						{
							PRINTLEFT(L"��ü �Ǿ����ϴ�.");
						}
						else
						{
							PRINTRIGHT(L"�ִ� ���Ծ׿� �ʰ��˴ϴ�.");
						}
						break;
					default:
						wprintf(L"���� ���¿� ��ü�� �Ұ����մϴ�.");
						break;
					}
					Sleep(1000);
					break;
				}
			}
			freeIOattriutes(IOatt);
			freeIOattriutes(IOatt2);
			free(IOatt);
			free(IOatt2);
			free(temp);
			break;
		}
		else if (transel == 2)
		{
			while (1)
			{
				int autoSum = 0;
				int autosel;
				wprintf(L"1. �ڵ���ü ��û\t 2. �ڵ���ü ����\n");
				scanf("%d", &autosel);

				if (autosel == 1)
				{
					char input5[100] = { "" };
					char* tok5[3] = { NULL, };

					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					temp = (char**)malloc(sizeof(char*) * g_userALNums);
					PRINTCEN(L"�ڵ���ü ������ ����� ���¸� �������ּ���.");
					for (int i = 0; i < g_userALNums; i++)
					{
						if (getAccType(g_userAccountsList[i]) == T1)
						{
							uIONums++;
							getAccountName(g_userAccountsList[i], tempname);
							temp[uIONums] = g_userAccountsList[i];
							printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
							memset(IOatt->IO_name, '\0', 17);
						}
					}
					printf("> ");
				INVALIDINPUT2:
					if (scanf("%d", &selection) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
					{
						while (getchar() != '\n');
						PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
						goto INVALIDINPUT2;

					}
					if (1 <= selection && selection <= uIONums)
					{
						PRINTLEFT(L"���°� ���õǾ����ϴ�\n");
						while (getchar() != '\n');
						Sleep(1000);
						system("cls");
					}
					else
					{
						PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
						while (getchar() != '\n');
						goto INVALIDINPUT2;
					}
					strncpy(IOatt->IO_mynum, temp[selection], 8);
					free(temp);
					temp = NULL;

					if (g_tempwcp != NULL)
					{
						free(g_tempwcp);
						g_tempwcp = NULL;
					}

					g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
					for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
					{
						mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
					}
					swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
					free(g_tempwcp);
					g_tempwcp = NULL;

					f_IO = _wfopen(g_wpath, L"r+");
					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					fgets(g_buffer, BUFF_SIZE, f_IO);
					strToIOatt_malloc(g_buffer, IOatt);

					while (1)
					{
						wprintf(L"��ݰ��� ��й�ȣ / �ڵ���ü�� ���¹�ȣ / �ڵ���ü�ݾ��� �Է��ϼ��� (/�� �������ּ���)\n");
						scanf("%s", &input5);
						char* ptr = strtok(input5, "/");

						int i = 0;
						while (ptr != NULL)
						{
							tok5[i] = ptr;
							i++;
							ptr = strtok(NULL, "/");
						}

						//����ƴ��� üũ, ��������
						printf("pw: %s\n", tok5[0]);
						printf("num: %s\n", tok5[1]);
						printf("money: %s\n", tok5[2]);

						if (checkDigit(tok5[0]) != 0 && checkDigit(tok5[1]) != 0 && checkDigit(tok5[2]) != 0)
						{
							wprintf(L"�ùٸ� �������� �Է����ּ���.\n");
						}
						else if (atoi(tok5[2]) <= 0)
						{
							wprintf(L"�ڵ���ü�� �ݾ��� 1�� �̻��̾�� �մϴ�.\n");
						}
						else if (atoi(tok5[2]) >= 3000000)
						{
							wprintf(L"��ݾ� �ѵ��� �ʰ��Ͽ����ϴ�.\n");
						}
						else
						{
							//�°� �Է����� ��
							while (1)
							{
								char input6[100] = { "" };
								char* tok6[2] = { NULL, };
								wprintf(L"���ϴ� �ڵ���ü �Ⱓ/ ��ü ��¥�� �Է��ϼ���\n");
								printf("(MM/DD)\n");
								scanf("%s", &input6);
								char* ptr = strtok(input6, "/");

								int i = 0;
								while (ptr != NULL)
								{
									tok6[i] = ptr;
									i++;
									ptr = strtok(NULL, "/");
								}

								//����ƴ��� üũ, ��������
								printf("month: %s\n", tok6[0]);
								printf("day: %s\n", tok6[1]);

								if (IOatt->autoNums > 0)
								{
									for (int i = 0; i < IOatt->autoNums; i++)
									{
										if (atoi(IOatt->autoattributes[i][0]) == atoi(tok6[1]))
										{
											autoSum += atol(IOatt->autoattributes[i][1]);
										}
									}
								}

								if (checkDigit(tok6[0]) != 0 && checkDigit(tok6[1]) != 0)
								{
									wprintf(L"�ùٸ� �������� �Է����ּ���.\n");
								}
								else if (autoSum > 3000000)
								{
									wprintf(L"�ڵ���ü �ݾ��� �ش� ��¥ ��ü�ѵ��� �ʰ��˴ϴ�.\n");
									printf(" -%ld- \n", autoSum - 3000000);
								}
								else
								{
									fseek(f_IO, -2, SEEK_CUR);
									CurrentFileOffset = ftell(f_IO);
									size_t numofRead = fread(g_filebuff, sizeof(char), FILE_BUFF, f_IO);
									fseek(f_IO, CurrentFileOffset, SEEK_SET);
									fprintf(f_IO, "%s|%s|%s|%s|", tok6[1], tok5[2], tok5[1], tok6[0]);
									fwrite(g_filebuff, sizeof(char), numofRead, f_IO);
									fclose(f_IO);

									printf("src : %s\n", tok5[1]);
									printf("des : %s\n", tok5[1]);
									printf("money : %s\n", tok5[2]);
									printf("money : %s\n", tok5[2]);
									printf("day : %s\n", tok6[1]);
									printf("�ڵ���ü ��û�� �Ϸ�Ǿ����ϴ�.\n");
									Sleep(1000);

									freeIOattriutes(IOatt);
									free(IOatt);
									IOatt = NULL;
									fclose(f_IO);
									f_IO = NULL;
									break;
								}
							}
							flag = 1;
							break;
						}
					}
					break;
				}
				else if (autosel == 2)
				{

					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					temp = (char**)malloc(sizeof(char*) * g_userALNums);
					PRINTCEN(L"�ڵ���ü ������ ������ ����� ���¸� �������ּ���.");
					for (int i = 0; i < g_userALNums; i++)
					{
						if (getAccType(g_userAccountsList[i]) == T1)
						{
							uIONums++;
							getAccountName(g_userAccountsList[i], tempname);
							temp[uIONums] = g_userAccountsList[i];
							printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
							memset(IOatt->IO_name, '\0', 17);
						}
					}
					printf("> ");
				INVALIDINPUT3:
					if (scanf("%d", &selection) != 1)
					{
						while (getchar() != '\n');
						PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
						goto INVALIDINPUT3;

					}
					if (1 <= selection && selection <= uIONums)
					{
						PRINTLEFT(L"���°� ���õǾ����ϴ�\n");
						while (getchar() != '\n');
						Sleep(1000);
						system("cls");
					}
					else
					{
						PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
						while (getchar() != '\n');
						goto INVALIDINPUT3;
					}
					strncpy(IOatt->IO_mynum, temp[selection], 8);
					free(temp);
					temp = NULL;

					if (g_tempwcp != NULL)
					{
						free(g_tempwcp);
						g_tempwcp = NULL;
					}

					g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
					for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
					{
						mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
					}
					swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
					free(g_tempwcp);
					g_tempwcp = NULL;

					f_IO = _wfopen(g_wpath, L"r+");
					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					assert(IOatt != NULL && "ssibal allocation wrong...Transfer() autosel == 2");
					fgets(g_buffer, BUFF_SIZE, f_IO);
					strToIOatt_malloc(g_buffer, IOatt);
				}
				if (IOatt->autoNums > 0)
				{
					int autoselection = 0;
					char toerase[30];
					PRINTCEN(L"������ �ڵ���ü�� �������ּ���.");
					wprintf(L"��ȣ) <��ݰ���>|<�����Ⱓ>|<�ݾ�>|<��������>\n");
					for (int i = 0; i < IOatt->autoNums; i++)
					{
						printf("%d) <%s>|<%s>|<%s>|<%s>\n", i + 1, IOatt->IO_mynum, IOatt->autoattributes[i][3], IOatt->autoattributes[i][1], IOatt->autoattributes[i][2]);
					}
				INVALIDINPUT4:
					if (scanf("%d", &autoselection) != 1)
					{
						while (getchar() != '\n');
						PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
						goto INVALIDINPUT4;

					}
					if (1 <= autoselection && autoselection <= IOatt->autoNums)
					{
						PRINTLEFT(L"���°� ���õǾ����ϴ�\n");
						while (getchar() != '\n');
						Sleep(1000);
						system("cls");
					}
					else
					{
						PRINTRIGHT(L"���¸� �ٽ� �������ּ���.\n");
						while (getchar() != '\n');
						goto INVALIDINPUT4;
					}
					sprintf(toerase, "%s|%s|%s|%s|", IOatt->autoattributes[autoselection - 1][0], IOatt->autoattributes[autoselection - 1][1], IOatt->autoattributes[autoselection - 1][2], IOatt->autoattributes[autoselection - 1][3]);
					eraseAuto(IOatt->IO_mynum, toerase,atoi(IOatt->autoattributes[autoselection - 1][3]));
					wprintf(L"������ �ڵ���ü�� �����߽��ϴ�.");
					break;
					Sleep(1000);
				}
				else
				{
					wprintf(L"��û�� �ڵ���ü�� �����ϴ�.");
					Sleep(1000);
				}

				freeIOattriutes(IOatt);
				free(IOatt);
				IOatt = NULL;
			}
		}
		else
		{
			getchar();
			printf("�ٽ� �Է��ϼ���\n");
		}
		if (flag == 1)
		{
			break;
		}
	}

}
void historyInquiry()
{
	char i_AccNum[8] = { 0, };
	long CurrentFileOffset = 0;
	FILE* f_Account;
	eAccType type;
	int accCounter = 0;
	int userHaveFlag = 0;

	IOinqury_t* ii;
	IOattributes_malloc_t* ia;
	FSinqury_t* fsi;
	FSattributes_t* fsa;

	system("cls");
	PRINTCEN(L"���� Ȯ�� �޴�");
	DRAWLINE('-');

#if TEST_ON 
	PRINTRIGHT(L"��ȸ�ϰ��� �ϴ� ���¹�ȣ�� �Է����ּ���\n>");
INVALIDINPUT:
	GET_G_INPUT;


	//���¹�ȣ �м�
	int j = 0;
	int k = 0;
	for (int i = 0; i < sizeof(i_AccNum) + 2; i++)
	{
		if (!isdigit(g_buffer[i]))
		{
			if (g_buffer[i] == '-' && (i == 2 || i == 4))
			{
				k++;
				continue;
			}
			else
			{
				break;
			}
		}
		i_AccNum[j++] = g_buffer[i];
	}
	i_AccNum[7] = '\0';
	if (j != 7 || (k != 2 && k != 0))
	{
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ� ����� �ƴմϴ�. �ٽ� �Է����ּ���.\n>");
		goto INVALIDINPUT;
	}

	// �ش� ����ã�ư���
	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}

	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(i_AccNum) + 1));
	for (int i = 0; i < strlen(i_AccNum) + 1; i++)
	{
		mbtowc(g_tempwcp + i, i_AccNum + i, MB_CUR_MAX);
	}
	switch (getAccType(i_AccNum)) // Ÿ��üũ
	{
	case T1: // ������� ���¸���
		type = T1;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", g_tempwcp[1], g_tempwcp);
		break;
	case T2: // ������ �ϳ�
		type = T2;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", g_tempwcp[1], g_tempwcp[0], g_tempwcp[1], g_tempwcp[2]);
		break;
	case T3: // ���ݵ� �ϳ�
		type = T3;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", g_tempwcp[1], g_tempwcp[0], g_tempwcp[1], g_tempwcp[2]);
		break;
	default:
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n >");
		goto INVALIDINPUT;
	}
	free(g_tempwcp);
	g_tempwcp = NULL;

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL) // ���� �̸� ������ �ٽ�
	{
		PRINTRIGHT(L"���¹�ȣ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���...\n> ");
		goto INVALIDINPUT;
	}

	for (int i = 0; i < g_userALNums; i++) //����� ���� �������� Ȯ��
	{
		if (strncmp(i_AccNum, g_userAccountsList[i], 7) == 0)
		{
			userHaveFlag = 1;
			break;
		}
	}
	if (userHaveFlag == 0)
	{
		PRINTRIGHT(L"���¹�ȣ�� ã�� �� �����ϴ�. Ȥ�� �ٸ� ��� ���¹�ȣ�� �ƴұ��?\n>");
		goto INVALIDINPUT;
	}
	//��� �׽�Ʈ
	int i = 0;
	while (1)
	{
		fseek(f_Account, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_Account);
		if (feof(f_Account))
		{
			break;
		}
		switch (getAccType(i_AccNum))
		{
		case T1:
			if (CurrentFileOffset == 0) // ù���� ���� �Ӽ�
			{
				ia = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
				strToIOatt_malloc(g_buffer, ia);
				printIOatt(ia);
				freeIOattriutes(ia);
				free(ia);
				ia = NULL;
				accCounter++;
			}
			else // �ι��� ���� ���� ����
			{
				ii = (IOinqury_t*)malloc(sizeof(IOinqury_t));
				strToIOiq(g_buffer, ii);
				printIOinquiry(ii);
				free(ii);
				ii = NULL;
			}
			break;
		case T2:
		case T3:
			if (CurrentFileOffset == 0) // ù���� ���� �Ӽ�
			{
				fsa = (FSattributes_t*)malloc(sizeof(FSattributes_t));
				if (strToFSatt(g_buffer, fsa, i_AccNum) == 1)  // ������ ���� ���� �ȿ� �ش� ���°� �ִ��� Ȯ��
				{
					printFSatt(fsa);
					accCounter++;
				}
				free(fsa);
				fsa = NULL;
			}
			else // �ι��� ���� ���� ����
			{
				if (accCounter != 0)
				{
					fsi = (FSinqury_t*)malloc(sizeof(FSinqury_t));
					if (strToFSiq(g_buffer, fsi, i_AccNum) == 1) // ������ ���� ���� �ȿ� �ش� ���°� �ִ��� Ȯ��
					{
						printFSinquiry(fsi);
					}
					free(fsi);
					fsi = NULL;
				}
			}
			break;
		default:
			assert("you can be  here");
		}

		CurrentFileOffset = ftell(f_Account); //������
	}
	if (accCounter == 0)
	{
		PRINTRIGHT(L"�ش� ���´� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���...\n> ");
		goto INVALIDINPUT;
	}

	fclose(f_Account);
	f_Account = NULL;
#endif
	system("pause");

	return;
}
