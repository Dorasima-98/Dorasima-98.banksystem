//아직 한참 덜 함ㅜㅜ

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
	PRINTCEN(L"서비스 메뉴");
	DRAWLINE('-');

	PRINTLEFT(L"1) 계좌 생성  2) 예금과 적금  3) 입금과 출금 ");
	PRINTLEFT(L"4) 계좌 이체  5) 계좌 내역    6) 로그아웃    7)종료 ");
	DRAWLINE('-');
	if (g_userALNums == 0)
	{
		PRINTRIGHT(L"여담이지만... 본인 소유의 계좌가 하나도 없으십니다. 계좌 생성 먼저 하시죠?");
	}
INVALIDINPUT:
	PRINTLEFT(L"주어진 메뉴의 번호를 선택해주세요. ");
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
			PRINTRIGHT(L"입출금 계좌를 먼저 만들어 주세요");
			goto INVALIDINPUT;
		}
		fixedDepositAndSavingsMenu();
		break;
	case 3:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"입출금 계좌를 먼저 만들어 주세요");
			goto INVALIDINPUT;
		}
		atmMenu();

		break;
	case 4:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"입출금 계좌를 먼저 만들어 주세요");
			goto INVALIDINPUT;
		}
		transferMenu();
		break;
	case 5:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"입출금 계좌를 먼저 만들어 주세요");
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

	PRINTCEN(L"계좌생성 메뉴");
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



	PRINTLEFT(L"계좌 명을 입력해주세요.\n> ");
Invalidinput1:
	GET_G_INPUT;

	AccountName_malloc = trim_malloc(AccountName_malloc, g_buffer);
	assert(AccountName_malloc != NULL && "trim is Something wrong...");

	if (strlen(AccountName_malloc) > 16 || strlen(AccountName_malloc) < 1)
	{
		PRINTRIGHT(L"이름의 길이는 1자 ~ 16자 입니다. 다시 입력해주세요.\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkAlnum(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"계좌명은 알파벳과 숫자로 입력 해주세요..\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkDupAN(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"소유한 계좌중 중복되는 계좌명이 있습니다...\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else
	{
		PRINTLEFT(L"계좌명을 제대로 입력했습니다. \n");
		Sleep(1000);
		system("cls");
	}

	PRINTLEFT(L"계좌 비밀번호를 입력해주세요. 4자리 정수입니다.\n> ");
Invalidinput2:
	GET_G_INPUT;

	PIN1 = trim_malloc(PIN1, g_buffer);
	assert(PIN1 != NULL && "trim is Something wrong...");

	if (strlen(PIN1) > 4 || strlen(PIN1) < 1)
	{
		PRINTRIGHT(L"계좌번호의 길이는 4자 입니다. 다시 입력해주세요.\n> ");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}

	if (checkDigit(PIN1) == 1)
	{
		PRINTRIGHT(L"계좌 비밀번호는 4자리 \"정수\"입니다..\n >");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}
	else if (checkDigit(PIN1) == 2)
	{
		PRINTRIGHT(L"계좌 비밀번호는 사이공백을 허용하지 않습니다.. 다시 입력해주세요.\n >");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}

	PRINTLEFT(L"계좌 비밀번호를 다시 입력해주세요. \n> ");
Invalidinput3:
	GET_G_INPUT;

	PIN2 = trim_malloc(PIN2, g_buffer);
	assert(PIN2 != NULL && "trim is Something wrong...");
	if (strncmp(PIN2, PIN1, 4) != 0)
	{
		PRINTRIGHT(L"PassWords가 서로 일치하지 않습니다.\n ");
		PRINTLEFT(L"PassWords 를 다시한번 입력하세요. \n> ");
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



	temppath = (wchar_t*)malloc(sizeof(wchar_t) * ((strlen(ranNum)) + 1)); // 계좌파일 만들기
	for (int j = 0; j < (strlen(ranNum)) + 1; j++)
	{
		mbtowc(temppath + j, ranNum + j, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, temppath);

	f_accFile = _wfopen(g_wpath, L"a+");
	assert(f_accFile != NULL && "create new account file failed");

	fseek(f_accFile, 0, SEEK_SET); //파일포인터를 처음위치로 이동시키기
	fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_accFile);

	fclose(f_accFile);
	f_accFile = NULL;

	fseek(f_AccountList, 0, SEEK_END);	//계좌리스트 파일에 적기 //파일포인터를 파일 제일 끝으로 이동시키기
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList);
	fflush(f_AccountList);

	sprintf(toMemfile, "%s|", ranNum); //toMemfile에 계좌번호| 문자열 입력

	CurrentFileOffset = setBankByID(g_userID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(파일 시작점 + CurrentFileOffset) 위치로 파일포인터 이동함
	while (fgetc(f_MemberFile) != '\n') //한줄씩 get할 거라는 의미
	{
		CurrentFileOffset++; //한글자 한글자씩 읽기 위해
	}
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(파일 시작점 + CurrentFileOffset) 위치로 파일포인터 이동함
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

	// heap corruption은 free할 때 생깁니다. 중단점으로 못찾어 ㅅㄱ
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


	printf("생성완료되었습니다.\n");
	printf("> %c%c-%c-%s", ranNum[0], ranNum[1], ranNum[2], &ranNum[3]);

	system("pause");

	return;
}
void fixedDepositAndSavingsMenu()
{
	int selection;

	system("cls");
	PRINTCEN(L"예금과 적금 메뉴");
	DRAWLINE('-');
	PRINTLEFT(L"1) 예적금 상품 신청  2) 예적금 상품 이자조회 및 해지");
INVALIDINPUT:
	PRINTLEFT(L"주어진 메뉴의 번호를 입력하세요.");
	wprintf(L"> ");

	GET_G_INPUT;

	selection = atoi(g_buffer);

	switch (selection)
	{
	case 1:
		while (1)
		{
			system("cls");
			PRINTLEFT(L"1) 예금	2) 적금");
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

	assert(IOatt != NULL && temp != NULL && Fixatt != NULL&&"IOatt and temp allocation failed");
	if (temp == NULL || IOatt == NULL||Fixatt == NULL)
	{
		_wperror(L"temp or IOatt or Fixatt allocation 실패");
		return;
	}
	PRINTCEN(L"돈을 출금할 입출금 계좌를 선택해주세요.");
	for (int i = 0; i < g_userALNums; i++)
	{
		if (getAccType(g_userAccountsList[i]) == T1)
		{
			getAccountName(g_userAccountsList[i], tempname);
			*(temp+uIONums) = *(g_userAccountsList+i);
			printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
			memset(IOatt->IO_name, '\0', 17);
			uIONums++;
		}
	}
	printf("> ");
INVALIDINPUT1:
	if (scanf("%d", &selection) != 1)  //이렇게하면 스페이스바만 처리할수있음
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
		goto INVALIDINPUT1;

	}
	if (1 <= selection && selection <= uIONums)
	{
		PRINTLEFT(L"계좌가 선택되었습니다\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else
	{
		PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
		while (getchar() != '\n');
		goto INVALIDINPUT1;
	}
	strncpy(IOatt->IO_mynum, *(temp+selection), 8);
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

	PRINTCEN(L"계좌명 입력");
	DRAWLINE('-');
	wprintf(L"계좌명을 입력해주세요.\n");
	wprintf(L"> ");
INVALIDINPUT2:
	GET_G_INPUT;

	inputcheck = trim_malloc(inputcheck, g_buffer);
	assert(inputcheck != NULL && "trim is Something wrong...");

	if (strlen(inputcheck) > 16 || strlen(inputcheck) < 1)
	{
		PRINTRIGHT(L"이름의 길이는 1자 ~ 16자 입니다. 다시 입력해주세요.\n");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}

	else if (strlen(inputcheck) == 1 && isdigit(*inputcheck) == 1)
	{
		PRINTRIGHT(L"한 글자로 지정하시려면 알파벳으로 입력 해주세요...\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}
	else if (checkAlnum(inputcheck) == 1)
	{
		PRINTRIGHT(L"계좌명은 알파벳 기본, 숫자 선택으로 입력 해주세요..\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}
	else if (checkDupAN(inputcheck) == 1)
	{
		PRINTRIGHT(L"소유한 계좌중 중복되는 계좌명이 있습니다...\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT2;
	}
	else
	{
		PRINTLEFT(L"계좌명을 제대로 입력했습니다. \n");
		Sleep(1000);
		strncpy(Fixatt->FS_name, inputcheck, strlen(inputcheck) + 1);
		free(inputcheck);
		inputcheck = NULL;
		system("cls");
	}
	printf("예금 계좌명이 %s로 설정되었습니다\n", Fixatt->FS_name);


	PRINTLEFT(L"계좌 비밀번호를 입력해주세요. 4자리 정수입니다.\n> ");
INVALIDINPUT3:
	GET_G_INPUT;

	inputcheck = trim_malloc(inputcheck, g_buffer);
	assert(inputcheck != NULL && "trim is Something wrong...");


	if (strlen(inputcheck) > 4 || strlen(inputcheck) < 1)
	{
		PRINTRIGHT(L"계좌번호의 길이는 4자 입니다. 다시 입력해주세요.\n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT3;
	}
	if (checkDigit(inputcheck) == 1)
	{
		PRINTRIGHT(L"계좌 비밀번호는 4자리 \"정수\"입니다..\n >");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT3;
	}
	else if (checkDigit(inputcheck) == 2)
	{
		PRINTRIGHT(L"계좌 비밀번호는 사이공백을 허용하지 않습니다.. 다시 입력해주세요.\n >");
		free(inputcheck);
		inputcheck = NULL;
		goto INVALIDINPUT3;
	}
	strncpy(Fixatt->FS_Passwords, inputcheck, strlen(inputcheck) + 1);

	PRINTLEFT(L"계좌 비밀번호를 다시 입력해주세요. \n> ");
Invalidinput4:
	GET_G_INPUT;

	inputcheck = trim_malloc(inputcheck, g_buffer);
	assert(inputcheck != NULL && "trim is Something wrong...");
	if (strncmp(inputcheck, Fixatt->FS_Passwords, 4) != 0)
	{
		PRINTRIGHT(L"PassWords가 서로 일치하지 않습니다.\n ");
		PRINTLEFT(L"PassWords 를 다시한번 입력하세요. \n> ");
		free(inputcheck);
		inputcheck = NULL;
		goto Invalidinput4;
	}
	PRINTLEFT(L"계좌 비밀번호가 설정이 되었습니다. \n> ");

	//일단 파일에 적어두기

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

	//리스트파일에 적어두기
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList);
	fflush(f_AccountList);

	sprintf(toMemfile, "%s|", Fixatt->FS_mynum);

	//멤버파일에 적어두기
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
	PRINTCEN(L"만기일 선택");
	DRAWLINE('-');
	PRINTCEN(L"===원하시는 서비스를 선택해주세요===");
	PRINTLEFT(L"만기일  1) 6개월(1.0%)   2) 1년(1.5%)   3) 2년(2.0%)");
INVALIDinput4:
	wprintf(L"> ");

	if (scanf("%d", &selection) != 1)  //이렇게하면 스페이스바만 처리할수있음
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"다시 선택해주세요\n");
		goto INVALIDinput4;

	}
	if (1 <= selection && selection <= 3)
	{
		PRINTLEFT(L"선택되었습니다\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else
	{
		PRINTRIGHT(L"다시 선택해주세요.\n");
		while (getchar() != '\n');
		goto INVALIDINPUT3;
	}

	PRINTCEN(L"납입액 입력");
	DRAWLINE('-');

	PRINTCEN(L"===선택한 서비스의 납입액(예치금)을 입력해주세요===");
	PRINTLEFT(L"**확인사항**");
	PRINTLEFT(L"적금 : 월 납입액 한도의 경우 50만원으로 제한이 됩니다.");
	PRINTLEFT(L"예금 : 예치금 한도의 경우 선택 입출금계좌 잔액입니다.");
	PRINTLEFT(L"(단위 : 1만원)");
	limit = atol(IOatt->IO_balance);
	wprintf(L"현재 출금 가능금액: %ld (원)", limit);
INVALIDINPUT6:
	wprintf(L"> ");

	if (scanf("%d", &money) != 1)  //이렇게하면 스페이스바만 처리할수있음
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"다시 입력해주세요\n");
		goto INVALIDINPUT6;

	}
	if (intype == 1)
	{
		if (1 <= money && (money * 10000) <= limit)
		{
			PRINTLEFT(L"입력되었습니다.\n");
			while (getchar() != '\n');
			Sleep(1000);
			system("cls");
		}
		else
		{
			PRINTRIGHT(L"넘어요..\n");
			while (getchar() != '\n');
			goto INVALIDINPUT6;
		}
	}
	else 
	{
		if (1 <= money && (money * 10000) <= 500000 && (money * 10000) <= limit)
		{
			PRINTLEFT(L"입력되었습니다.\n");
			while (getchar() != '\n');
			Sleep(1000);
			system("cls");
		}
		else
		{
			PRINTRIGHT(L"넘어요...\n");
			while (getchar() != '\n');
			goto INVALIDINPUT6;
		}
	}

	moneyOutIO(IOatt->IO_mynum, Fixatt->FS_mynum, money * 10000, 1); //flag를 1로 넘겨주면 이체한도 무시
	moneyInFS(Fixatt->FS_mynum, money * 10000, selection);

	wprintf(L"신청이 완료되었습니다.\n");
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
	float rate = 0.0; //이자율
	int duration; //예금 기간(6개월이면 6, 1년이면 1, 2년이면 2)
	float fixedDepositMoney = 0.0; //예치금(납입액)
	float finalFixedDepositMoney = 0.0; //만기해지금
	char accountName[10]; //예금계좌명

	wchar_t* temppath = NULL;
	FILE* f_accFile = NULL;
	char* toListfile = NULL;
	char* toTargetfile = NULL;
	size_t toLfnums = 0;
	size_t toTfnums = 0;

	system("cls");
	PRINTCEN(L"출금할 계좌 선택");
	DRAWLINE('-');
	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	// 해당 파일찾아가기
	if (tempwcp != NULL)
	{
		free(tempwcp);
		tempwcp = NULL;
	}

	tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * 8); //8맞낭..
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", tempwcp[1], tempwcp);

	inputFile = _wfopen(g_wpath, L"r");

	int accountSelection = 0;

	if (inputFile != NULL)
	{
		char buffer[1024]; //나중에 수정해야함
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

	scanf("%d", &accountSelection); //입출금계좌 선택하기
	//선택해서 그 입출금계좌 정보 가져와야 함 - 구현해야함

	fclose(inputFile);

	//은행에 맞게 계좌번호 생성하기
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

	toLfnums = 50; //일단 잘 몰라서 대충,,,
	toTfnums = 80; //이거두

	toListfile = (char*)malloc(sizeof(char) * toLfnums);
	toTargetfile = (char*)malloc(sizeof(char) * toTfnums);

	PRINTCEN(L"계좌명 입력");
	DRAWLINE('-');
	printf("예금 계좌명을 입력해주세요.\n");
	wprintf(L"> ");
	scanf("%s", &accountName);
	printf("예금 계좌명이 %s로 설정되었습니다\n", accountName);
	system("pause");

	system("cls");
	PRINTCEN(L"만기일 선택");
	DRAWLINE('-');
	PRINTCEN(L"===선택한 서비스의 만기일을 선택해주세요===");
	PRINTLEFT(L"만기일  1) 6개월(1.0%)   2) 1년(1.5%)   3) 2년(2.0%)");
	wprintf(L"> ");

	int selection = 0;

	scanf_s("%d", &selection, 1);

	//printf는 그냥 확인용이라 다 빼야함. rate는 나중에 예금파일 첫 줄에 적어야 함
	switch (selection)
	{
	case 1:
		rate = 1.0;
		duration = 6;
		//printf("6개월 선택완료\n");
		break;

	case 2:
		rate = 1.5;
		duration = 1;
		//printf("1년 선택완료\n");
		break;

	case 3:
		rate = 2.0;
		duration = 2;
		//printf("2년 선택완료\n");
		break;
	}

	system("pause");
	system("cls");
	PRINTCEN(L"납입액 입력");
	DRAWLINE('-');

	PRINTCEN(L"===선택한 서비스의 납입액(예치금)을 입력해주세요===");
	PRINTLEFT(L"**확인사항**");
	PRINTLEFT(L"적금 : 월 납입액 한도의 경우 50만원으로 제한이 됩니다.");
	PRINTLEFT(L"예금 : 예치금 한도의 경우 선택 입출금계좌 잔액입니다.");
	PRINTLEFT(L"(단위 : 1만원)");
	wprintf(L"> ");

	scanf("%f", &fixedDepositMoney);

	//여기 아까 선택한 입출금계좌 잔액보다 적은지 많은지, 1원 이상인지 if문 있어야 함!!

	//만기수령액 계산하기
	switch (selection)
	{
	case 1:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.01 * 0.5;
		//printf("만기수령액은 %.5f만원 입니다.\n", finalFixedDepositMoney);
		break;

	case 2:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.015;
		//printf("만기수령액은 %.5f만원 입니다.\n", finalFixedDepositMoney);
		break;

	case 3:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.02 * 2;
		//printf("만기수령액은 %.5f만원 입니다.\n", finalFixedDepositMoney);
		break;
	}

	int accountPassword = 1234; //입출금계좌에서 받아오기 - 구현해야함.

	system("pause");

	//여기부터 복붙
	temppath = (wchar_t*)malloc(sizeof(wchar_t) * ((strlen(ranNum)) + 1)); // 계좌파일 만들기
	for (int j = 0; j < (strlen(ranNum)) + 1; j++)
	{
		mbtowc(temppath + j, ranNum + j, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, temppath);

	f_accFile = _wfopen(g_wpath, L"a+");
	assert(f_accFile != NULL && "create new account file failed");

	fseek(f_accFile, 0, SEEK_SET); //파일포인터를 처음위치로 이동시키기
	fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_accFile);

	fclose(f_accFile);
	f_accFile = NULL;

	fseek(f_AccountList, 0, SEEK_END);	//계좌리스트 파일에 적기 //파일포인터를 파일 제일 끝으로 이동시키기
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList);
	fflush(f_AccountList);

	sprintf(toMemfile, "%s|", ranNum); //toMemfile에 계좌번호| 문자열 입력

	CurrentFileOffset = setBankByID(g_userID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(파일 시작점 + CurrentFileOffset) 위치로 파일포인터 이동함
	while (fgetc(f_MemberFile) != '\n') //한줄씩 get할 거라는 의미
	{
		CurrentFileOffset++; //한글자 한글자씩 읽기 위해
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(파일 시작점 + CurrentFileOffset) 위치로 파일포인터 이동함
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

	//여기까지 복붙한 거. 수정해야 함


	//마지막 줄에는 "추가된 계좌정보" 들어감 
	inputFile = fopen("fixed.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%f\n", accountName, ranNum, finalFixedDepositMoney, fixedDepositMoney);
	fclose(inputFile);

	//첫 줄에는 "계좌명, 계좌번호, new![만기시 수령액], 계좌 비밀번호, 서비스 신청기간, 이자율, 해지 시 수령액의 조합"이 들어감!
	//해당 계좌 잔액, 계좌 비밀번호는 지금 구현 못해서 그거 빼고 나머지는 첫 줄에 씀
	inputFile = fopen("fixed_shortcut.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%d|%d|%f|%f ", accountName, finalFixedDepositMoney, fixedDepositMoney, accountPassword, duration, rate, fixedDepositMoney);
	fclose(inputFile);

	//Q_CHECK();
	//wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	//system("pause");
#endif
}
void inquiryAndCancel() 
{
	size_t uIONums = 0;
	char** temp = NULL;
	FILE* f_IO = NULL;
	FILE* f_FS = NULL;
	IOattributes_malloc_t* IOatt = NULL;
	FSattributes_t* FSatt = NULL;

	FSatt = (FSattributes_t*)malloc(sizeof(FSattributes_t));
	IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

	char tempname[17];
	int selection = 0;
	long CurrentFileOffset = 0;

	temp = (char**)malloc(sizeof(char*) * g_userALNums);
	assert(temp!=NULL && "temp allocation is failed at inquiryAndCancel");
	PRINTCEN(L"서비스를 해지할 예적금 계좌를 선택해주세요.");
	for (int i = 0; i < g_userALNums; i++)
	{
		if (getAccType(g_userAccountsList[i]) == T2 || getAccType(g_userAccountsList[i]))
		{
			getAccountName(g_userAccountsList[i], tempname);
			*(temp+uIONums) = *(g_userAccountsList+i);
			printf("%d) %s/%s\n", (int)uIONums, tempname, g_userAccountsList[i]);
			//memset(IOatt->IO_name, '\0', 17);
			uIONums++;
		}
	}
	printf("> ");
INVALIDINPUT1:
	if (scanf("%d", &selection) != 1)  //이렇게하면 스페이스바만 처리할수있음
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
		goto INVALIDINPUT1;

	}
	if (1 <= selection && selection <= uIONums)
	{
		PRINTLEFT(L"계좌가 선택되었습니다\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else
	{
		PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
		while (getchar() != '\n');
		goto INVALIDINPUT1;
	}
	g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(temp[selection]) + 1));
	for (int i = 0; i < strlen(temp[selection]) + 1; i++)
	{
		mbtowc(g_tempwcp + i, temp[selection] + i, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\0%c%c.txt", g_tempwcp[1], g_tempwcp[1], g_tempwcp[2]);
	free(g_tempwcp);
	g_tempwcp = NULL;

	f_FS = _wfopen(g_wpath, L"r+");
	fgets(g_buffer, BUFF_SIZE, f_FS);
	CurrentFileOffset = strToFSatt(g_buffer, FSatt, temp[selection]);

	wprintf(L"수령 금액은: %ld (원)입니다.", atol(FSatt->FS_balance));

	free(temp);
	temp = NULL;

	if (g_tempwcp != NULL)
	{
		free(g_tempwcp);
		g_tempwcp = NULL;
	}

	fseek(f_FS, CurrentFileOffset, SEEK_SET);

	size_t numofread = 0;
	size_t numofread2 = 0;
	char check = fgetc(f_FS);
	while (check != ' ' && check != '\n')
	{
		check = fgetc(f_FS);
	}
	if (CurrentFileOffset == 0 && check == ' ')
	{
		//fseek(f_FS, 0, SEEK_SET);
		numofread = fread(g_filebuff, sizeof(char), FILE_BUFF, f_FS);

		f_FS = _wfreopen(g_wpath, L"w+", f_FS);
		fseek(f_FS, 0, SEEK_SET);
		fwrite(g_filebuff, sizeof(char), numofread, f_FS);
	}
	else if (check == ' ' && CurrentFileOffset != 0)
	{
		numofread2 = CurrentFileOffset;
		CurrentFileOffset = ftell(f_FS);
		fseek(f_FS, 0, SEEK_SET);
		numofread2 = fread(g_filebuff2, sizeof(char), numofread2, f_FS);
		fseek(f_FS, CurrentFileOffset, SEEK_SET);
		numofread = fread(g_filebuff, sizeof(char), FILE_BUFF, f_FS);

		f_FS = _wfreopen(g_wpath, L"w+", f_FS);
		fwrite(g_filebuff2, sizeof(char), numofread2, f_FS);
		fwrite(g_filebuff, sizeof(char), numofread, f_FS);
	}
	else if (check == '\n' && CurrentFileOffset > 0 )
	{
		numofread2 = (size_t)(CurrentFileOffset) - 1 ;
		CurrentFileOffset = ftell(f_FS) - 2;
		fseek(f_FS, 0, SEEK_SET);
		numofread2 = fread(g_filebuff2, sizeof(char), numofread2, f_FS);
		fseek(f_FS, CurrentFileOffset, SEEK_SET);
		numofread = fread(g_filebuff, sizeof(char), FILE_BUFF, f_FS);

		f_FS = _wfreopen(g_wpath, L"w+", f_FS);
		fwrite(g_filebuff2, sizeof(char), numofread2, f_FS);
		fwrite(g_filebuff, sizeof(char), numofread, f_FS);
	}
	else if (check == '\n' && CurrentFileOffset == 0) // 일단 다 지우는 거로
	{
		//CurrentFileOffset = ftell(f_FS) - 2;
		//numofread = fread(g_filebuff, sizeof(char), FILE_BUFF, f_FS);
		f_FS = _wfreopen(g_wpath, L"w+", f_FS);
		//fwrite(g_filebuff, sizeof(char), numofread, f_FS);
	}

	fclose(f_FS);

	// ******* ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ *********
	// account.txt랑 members.txt 최신화 해야함
	char toEraselist[30]; 
	char toErasemem[10]; 

	if (temp != NULL)
	{
		free(temp);
		temp = NULL;

	}
	uIONums = 0;
	temp = (char**)malloc(sizeof(char*) * g_userALNums);
	assert(temp != NULL && "temp allocation is failed at inquiryAndCancel");
	PRINTCEN(L"돈을 입금할 입출금 계좌를 선택해주세요.");
	for (int i = 0; i < g_userALNums; i++)
	{
		if (getAccType(g_userAccountsList[i]) == T1)
		{
			getAccountName(g_userAccountsList[i], tempname);
			*(temp+uIONums) = *(g_userAccountsList+i);
			printf("%d) %s/%s\n", (int)uIONums + 1, tempname, g_userAccountsList[i]);
			memset(IOatt->IO_name, '\0', 17);
			uIONums++;
		}
	}
	printf("> ");
INVALIDINPUT2:
	if (scanf("%d", &selection) != 1)  //이렇게하면 스페이스바만 처리할수있음
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
		goto INVALIDINPUT2;

	}
	if (1 <= selection && selection <= uIONums)
	{
		PRINTLEFT(L"계좌가 선택되었습니다\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else
	{
		PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
		while (getchar() != '\n');
		goto INVALIDINPUT2;
	}
	strncpy(IOatt->IO_mynum, temp[selection], 8);
	free(temp);
	temp = NULL;

	moneyInIO(IOatt->IO_mynum, FSatt->FS_mynum, atol(FSatt->FS_balance));

	PRINTCEN(L"예적금 해지 되었습니다.");

	freeIOattriutes(IOatt);
	free(IOatt);
	free(FSatt);
	IOatt = NULL;
	FSatt = NULL;

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
		wprintf(L"1. 입금\t 2. 출금\n");
		wprintf(L"> ");
	INVALIDINPUT0:
		if (scanf("%d", &atmsel) != 1)  //이렇게하면 스페이스바만 처리할수있음
		{
			while (getchar() != '\n');
			PRINTRIGHT(L"메뉴를 다시 선택해주세요..\n");
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
			PRINTRIGHT(L"메뉴를 다시 선택해주세요.\n");
			while (getchar() != '\n');
			goto INVALIDINPUT0;
		}
		if (atmsel == 1)
		{
			PRINTLEFT(L"임금 선택 되었습니다.\n");

			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

			temp = (char**)malloc(sizeof(char*) * g_userALNums);
			PRINTCEN(L"입금 가능한 입출금 계좌 목록입니다.");
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

			char input[100] = { "" };
			char* tok[3] = { NULL, };

			while (1)
			{
				wprintf(L"입금할 계좌에 지정된 번호 / 계좌 비밀번호 / 입금할 금액을 입력하세요 (/로 구분)\n");
				while (scanf("%s", &input) != 1)
				{
					while (getchar() != '\n');
					PRINTRIGHT(L"다시 입력해주세요.\n");
				}
				
				
				if (checkATMorTransfer(input,tok,2)!=1)
				{
					wprintf(L"양식에 맞게 입력해주세요...\n");
				}
				else if (checkDigit(tok[0]) != 0 && checkDigit(tok[1]) != 0 && checkDigit(tok[2]) != 0)
				{
					wprintf(L"숫자를 입력해주세요.\n"); // 12.1.1)
				}
				else if (atol(tok[2]) <= 0)
				{
					wprintf(L"입금할 금액은 1원 이상이어야 합니다.\n"); // 12.1.5)
				}
				else if (strcmp(IOatt->IO_Passwords, tok[1]) != 0)
				{
					wprintf(L"비밀번호가 틀렸습니다.\n");
				}
				else if (1 <= atoi(tok[0]) && atoi(tok[0]) <= uIONums)
				{
					wprintf(L"주어진 번호에서 선택하십시오.\n");
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
					if (f_IO == NULL && errno == ENOENT)//목적 계좌가 없을때
					{
						_wperror(L"해당 계좌가 존재하지 않습니다.\n");
						errno = 0;
						continue;
					}
					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					fgets(g_buffer, BUFF_SIZE, f_IO);
					strToIOatt_malloc(g_buffer, IOatt);

					//저장됐는지 체크, 지워야함
					printf("target num: %s\n", tok[0]);
					printf("pw: %s\n", tok[1]);
					printf("inmoney: %s\n", tok[2]);

					moneyInIO(IOatt->IO_mynum, NULL, (atol(tok[2])));
					wprintf(L"계좌에 %ld원을 입금하였습니다", atol(tok[2]));
					break;
				}
			}
			break;
		}
		else if (atmsel == 2)
		{
			PRINTLEFT(L"출금 선택 되었습니다.\n");
			IOattributes_malloc_t* IOatt = NULL;

			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));

			temp = (char**)malloc(sizeof(char*) * g_userALNums);
			assert(temp != NULL && "temp allocation failed in fucntion...\"atm()\"");
			PRINTCEN(L"출금 가능한 입출금 계좌목록입니다.");
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
				wprintf(L"출금할 계좌에 지정된 번호 / 계좌 비밀번호 / 출금액을 입력하세요 (/로 구분)\n");
				while (scanf("%s", &input2) != 1)
				{
					while (getchar() != '\n');
					PRINTRIGHT(L"다시 입력해주세요.\n");
				}
				char* ptr = strtok(input2, "/");

				int i = 0;
				while (ptr != NULL)
				{
					tok2[i] = ptr;
					i++;
					ptr = strtok(NULL, "/");
				}

				//저장됐는지 체크, 지워야함
				printf("num: %s\n", tok2[0]);
				printf("pw: %s\n", tok2[1]);
				printf("outmoney: %s\n", tok2[2]);

				if (checkATMorTransfer(input2, tok2,2) != 1)
				{
					wprintf(L"양식이 올바르지 않습니다.\n");
				}
				else if (checkDigit(tok2[0]) != 0 && checkDigit(tok2[1]) != 0 && checkDigit(tok2[2]) != 0)
				{
					wprintf(L"양식이 올바르지 않습니다.\n"); // 12.2.1)
				}
				else if (atol(tok2[2]) <= 0)
				{
					wprintf(L"출금할 금액은 1원 이상이어야 합니다.\n"); // 12.2.5)
				}
				else if (atol(tok2[2]) >= 3000000)
				{
					wprintf(L"출금액 한도를 초과하였습니다.\n"); // 12.2.7) , 월별한도 추가해야함
				}
				else if (strcmp(IOatt->IO_Passwords, tok2[1]) != 0)
				{
					wprintf(L"비밀번호가 틀렸습니다.\n");
				}
				else if (tok2[0] != NULL &&1 <= atoi(tok2[0]) && atoi(tok2[0]) <= uIONums)
				{
					wprintf(L"주어진 번호에서 선택하십시오.\n");
				}
				else
				{
					g_tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(IOatt->IO_mynum) + 1));
					for (int i = 0; i < strlen(IOatt->IO_mynum) + 1; i++)
					{
						mbtowc(g_tempwcp + i, IOatt->IO_mynum + i, MB_CUR_MAX);
					}
					swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, g_tempwcp);
					free(g_tempwcp);
					g_tempwcp = NULL;

					f_IO = _wfopen(g_wpath, L"r+");
					assert(f_IO != NULL && "_wfopen failed");
					if (f_IO == NULL && errno == ENOENT)//목적 계좌가 없을때
					{
						_wperror(L"해당 계좌가 존재하지 않습니다.\n");
						errno = 0;
						continue;
					}
					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					assert(IOatt != NULL && "IOatt allocation failed");
					if (IOatt == NULL)
					{
						perror("IOatt allocation failed");
						continue;
					}
					fgets(g_buffer, BUFF_SIZE, f_IO);
					strToIOatt_malloc(g_buffer, IOatt);

					if (tok2[0] != NULL)
					{
						strncpy(IOatt->IO_mynum, temp[atoi(tok2[0]) - 1], 8);
						free(temp);
						temp = NULL;

						if (g_tempwcp != NULL)
						{
							free(g_tempwcp);
							g_tempwcp = NULL;
						}

						if (moneyOutIO(IOatt->IO_mynum, NULL, (atol(tok2[2])), 0) == 0)
						{
							wprintf(L"이체한도가 넘는 금액입니다.\n");
							break;
						}
						else
						{
							wprintf(L"계좌에서 %ld원을 출금하였습니다\n", atol(tok2[2]));
							break;
						}
					}
					else
					{
						continue;
					}
				}
			}
			break;
		}
		else
		{
			wprintf(L"다시 입력하세요\n");
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
		wprintf(L"1. 계좌이체\t 2. 자동이체\n");
	INVALIDINPUT0:
		if (scanf("%d", &transel) != 1)  //이렇게하면 스페이스바만 처리할수있음
		{
			while (getchar() != '\n');
			PRINTRIGHT(L"메뉴를 다시 선택해주세요..\n");
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
			PRINTRIGHT(L"메뉴를 다시 선택해주세요.\n");
			while (getchar() != '\n');
			goto INVALIDINPUT0;
		}
		if (transel == 1)
		{
			IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
			temp = (char**)malloc(sizeof(char*) * g_userALNums);
			assert(IOatt != NULL && temp != NULL && "IOatt and temp allocation failed");
			if (temp == NULL || IOatt == NULL)
			{
				_wperror(L"temp or IOatt or Fixatt allocation 실패");
				return;
			}
			PRINTCEN(L"돈을 출금할 입출금 계좌를 선택해주세요.");
			for (int i = 0; i < g_userALNums; i++)
			{
				if (getAccType(g_userAccountsList[i]) == T1)
				{
					getAccountName(g_userAccountsList[i], tempname);
					*(temp+uIONums) = g_userAccountsList[i];
					printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
					memset(IOatt->IO_name, '\0', 17);
					uIONums++;
				}
			}
			printf("> ");
		INVALIDINPUT1:
			if (scanf("%d", &selection) != 1)  //이렇게하면 스페이스바만 처리할수있음
			{
				while (getchar() != '\n');
				PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
				goto INVALIDINPUT1;

			}
			if (1 <= selection && selection <= uIONums)
			{
				PRINTLEFT(L"계좌가 선택되었습니다\n");
				while (getchar() != '\n');
				Sleep(1000);
				system("cls");
			}
			else
			{
				PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
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
				wprintf(L"입금할 계좌 번호 / 출금 계좌 비밀번호 / 입금할 금액을 입력하세요 (/로 구분)\n");
				wprintf(L"출금 계좌의 잔액 / 이체한도 :\t");
				printf("%s / %s\n", IOatt->IO_balance, IOatt->IO_dateLimits);
				while (scanf("%s", &input3) != 1)
				{
					while (getchar() != '\n');
					PRINTRIGHT(L"다시 입력해주세요.\n");
				}
				if (checkATMorTransfer(input3, tok3,2) != 1)
				{
					wprintf(L"양식이 올바르지 않습니다.\n");
				}
				else if (checkDigit(tok3[0]) != 0 && checkDigit(tok3[1]) != 0 && checkDigit(tok3[2]) != 0)
				{
					wprintf(L"숫자를 입력해주세요.\n"); // 12.1.1)
				}
				else if (atol(tok3[2]) <= 0)
				{
					wprintf(L"입금할 금액은 1원 이상이어야 합니다.\n"); // 12.1.5)
				}
				else if (strcmp(IOatt->IO_Passwords, tok3[1]) != 0)
				{
					wprintf(L"비밀번호가 틀렸습니다.\n");
				}
				else if (atol(tok3[2]) > atol(IOatt->IO_dateLimits))
				{
					wprintf(L"이체 한도보다 적은 금액을 이체해야 합니다.\n");
				}
				else if (checkExistAcc(tok3[0])!=1)
				{
					wprintf(L"목적 계좌가 존재하지 않습니다.\n");
				}
				else if (T2 == getAccType(tok3[0]))
				{
					wprintf(L"예금 계좌에 이체할 수 없습니다.\n");
				}
				else
				{
					//저장됐는지 체크, 지워야함
					printf("num: %s\n", tok3[0]);
					printf("pw: %s\n", tok3[1]);
					printf("inmoney: %s\n", tok3[2]);

					moneyOutIO(IOatt->IO_mynum, tok3[0], (atol(tok3[2])), 0);
					switch (getAccType(tok3[0]))
					{
					case T1:
						moneyInIO(tok3[0], IOatt->IO_mynum, (atol(tok3[2])));
						PRINTLEFT(L"이체 되었습니다.");
						break;
					case T3:
						if (moneyInFS(tok3[0], (atol(tok3[2])), 0) == 1)
						{
							PRINTLEFT(L"이체 되었습니다.");
						}
						else
						{
							PRINTRIGHT(L"최대 납입액에 초과됩니다.");
						}
						break;
					default:
						wprintf(L"예금 계좌에 이체는 불가능합니다.");
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
				wprintf(L"1. 자동이체 신청\t 2. 자동이체 해지\n");
				if (scanf("%d", &autosel) != 1)
				{
					wprintf(L"다시 입력해주세요.\n");
					continue;
				}

				if (autosel == 1)
				{
					char input4[100] = { "" };
					char* tok4[3] = { NULL, };

					IOatt = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
					temp = (char**)malloc(sizeof(char*) * g_userALNums);
					assert(IOatt != NULL && temp != NULL && "IOatt and temp allocation failed");
					if (temp == NULL || IOatt == NULL)
					{
						_wperror(L"temp or IOatt allocation 실패");
						continue;
					}
					PRINTCEN(L"자동이체 설정할 입출금 계좌를 선택해주세요.");
					for (int i = 0; i < g_userALNums; i++)
					{
						if (getAccType(g_userAccountsList[i]) == T1)
						{
							getAccountName(g_userAccountsList[i], tempname);
							*(temp+uIONums) = g_userAccountsList[i];
							printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
							memset(IOatt->IO_name, '\0', 17);
							uIONums++;
						}
					}
					printf("> ");
				INVALIDINPUT2:
					if (scanf("%d", &selection) != 1)  //이렇게하면 스페이스바만 처리할수있음
					{
						while (getchar() != '\n');
						PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
						goto INVALIDINPUT2;

					}
					if (1 <= selection && selection <= uIONums)
					{
						PRINTLEFT(L"계좌가 선택되었습니다\n");
						while (getchar() != '\n');
						Sleep(1000);
						system("cls");
					}
					else
					{
						PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
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
						wprintf(L"출금계좌 비밀번호 / 자동이체할 계좌번호 / 자동이체금액을 입력하세요 (/로 구분해주세요)\n");
						if (scanf("%s", &input4) != 1)
						{
							wprintf(L"다시 입력해주세요.\n");
							continue;
						}

						if (checkATMorTransfer(input4, tok4,2) != 1)
						{
							wprintf(L"양식이 올바르지 않습니다.\n");
						}
						if (checkDigit(tok4[0]) != 0 && checkDigit(tok4[1]) != 0 && checkDigit(tok4[2]) != 0)
						{
							wprintf(L"올바른 형식으로 입력해주세요.\n");
						}
						else if (atoi(tok4[2]) <= 0)
						{
							wprintf(L"자동이체할 금액은 1원 이상이어야 합니다.\n");
						}
						else if (atoi(tok4[2]) >= 3000000)
						{
							wprintf(L"출금액 한도를 초과하였습니다.\n");
						}
						else
						{
							//저장됐는지 체크, 지워야함
							printf("pw: %s\n", tok4[0]);
							printf("num: %s\n", tok4[1]);
							printf("money: %s\n", tok4[2]);

							//맞게 입력했을 때
							while (1)
							{
								char input6[100] = { "" };
								char* tok6[2] = { NULL, };
								wprintf(L"원하는 자동이체 기간/ 이체 날짜를 입력하세요\n");
								printf("(MM/DD)\n");
								
								if (scanf("%s", &input6)!= 1)
								{
									wprintf(L"다시 입력해주세요.\n");
									continue;
								}

								if (IOatt->autoNums > 0) // 자동이체 설정이 이미 존재하는지 체크하고, 그 값을 더해놓기
								{
									for (int i = 0; i < IOatt->autoNums; i++)
									{
										if (atoi(IOatt->autoattributes[i][0]) == atoi(tok6[1]))
										{
											autoSum += atol(IOatt->autoattributes[i][1]);
										}
									}
								}

								if (checkATMorTransfer(input6, tok6,1) != 1)
								{
									wprintf(L"양식이 올바르지 않습니다.\n");
								}
								else if (checkDigit(tok6[0]) != 0 && checkDigit(tok6[1]) != 0)
								{
									wprintf(L"올바른 형식으로 입력해주세요.\n");
								}
								else if (autoSum > 3000000)
								{
									wprintf(L"자동이체 금액이 이체한도에 초과됩니다.\n");
									printf(" -%ld- \n", autoSum - 3000000);
								}
								else
								{
									//저장됐는지 체크, 지워야함
									printf("month: %s\n", tok6[0]);
									printf("day: %s\n", tok6[1]);


									fseek(f_IO, -2, SEEK_CUR);
									CurrentFileOffset = ftell(f_IO);
									size_t numofRead = fread(g_filebuff, sizeof(char), FILE_BUFF, f_IO);
									fseek(f_IO, CurrentFileOffset, SEEK_SET);
									fprintf(f_IO, "%s|%s|%s|%s|", tok6[1], tok4[2], tok4[1], tok6[0]);
									fwrite(g_filebuff, sizeof(char), numofRead, f_IO);
									fclose(f_IO);

									printf("src : %s\n", tok4[1]);
									printf("des : %s\n", tok4[1]);
									printf("money : %s\n", tok4[2]);
									printf("money : %s\n", tok4[2]);
									printf("day : %s\n", tok6[1]);
									printf("자동이체 신청이 완료되었습니다.\n");
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
					temp = (char**)malloc(sizeof(char*) * g_userALNums+1);
					assert(IOatt != NULL && temp != NULL && "IOatt and temp allocation failed");
					if (temp == NULL || IOatt == NULL)
					{
						_wperror(L"temp or IOatt allocation 실패");
						continue;
					}
					PRINTCEN(L"자동이체 설정을 삭제할 입출금 계좌를 선택해주세요.");
					for (int i = 0; i < g_userALNums; i++)
					{
						if (getAccType(g_userAccountsList[i]) == T1)
						{
							getAccountName(g_userAccountsList[i], tempname);
							*(temp+uIONums) = *(g_userAccountsList+i);
							printf("%d) %s/%s\n", i + 1, tempname, g_userAccountsList[i]);
							memset(IOatt->IO_name, '\0', 17);
							uIONums++;
						}
					}
					printf("> ");
				INVALIDINPUT3:
					if (scanf("%d", &selection) != 1)
					{
						while (getchar() != '\n');
						PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
						goto INVALIDINPUT3;

					}
					if (1 <= selection && selection <= uIONums)
					{
						PRINTLEFT(L"계좌가 선택되었습니다\n");
						while (getchar() != '\n');
						Sleep(1000);
						system("cls");
					}
					else
					{
						PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
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
				if (IOatt != NULL && IOatt->autoNums > 0)
				{
					int autoselection = 0;
					char toerase[30];
					PRINTCEN(L"삭제할 자동이체를 선택해주세요.");
					wprintf(L"번호) <출금계좌>|<남은기간>|<금액>|<목적계좌>\n");
					for (int i = 0; i < IOatt->autoNums; i++)
					{
						printf("%d) <%s>|<%s>|<%s>|<%s>\n", i + 1, IOatt->IO_mynum, IOatt->autoattributes[i][3], IOatt->autoattributes[i][1], IOatt->autoattributes[i][2]);
					}
				INVALIDINPUT4:
					if (scanf("%d", &autoselection) != 1)
					{
						while (getchar() != '\n');
						PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
						goto INVALIDINPUT4;

					}
					if (1 <= autoselection && autoselection <= IOatt->autoNums)
					{
						PRINTLEFT(L"계좌가 선택되었습니다\n");
						while (getchar() != '\n');
						Sleep(1000);
						system("cls");
					}
					else
					{
						PRINTRIGHT(L"계좌를 다시 선택해주세요.\n");
						while (getchar() != '\n');
						goto INVALIDINPUT4;
					}
					sprintf(toerase, "%s|%s|%s|%s|", IOatt->autoattributes[autoselection - 1][0], IOatt->autoattributes[autoselection - 1][1], IOatt->autoattributes[autoselection - 1][2], IOatt->autoattributes[autoselection - 1][3]);
					eraseAuto(IOatt->IO_mynum, toerase,atoi(IOatt->autoattributes[autoselection - 1][3]));
					wprintf(L"선택한 자동이체를 삭제했습니다.");
					break;
					Sleep(1000);
				}
				else
				{
					wprintf(L"신청된 자동이체가 없습니다.");
					Sleep(1000);
				}

				freeIOattriutes(IOatt);
				free(IOatt);
				IOatt = NULL;
			}
		}
		else
		{
			wprintf(L"다시 입력하세요\n");
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
	PRINTCEN(L"내역 확인 메뉴");
	DRAWLINE('-');

#if TEST_ON 
	PRINTRIGHT(L"조회하고자 하는 계좌번호를 입력해주세요\n>");
INVALIDINPUT:
	GET_G_INPUT;


	//계좌번호 분석
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
		PRINTRIGHT(L"계좌번호가 올바른 양식이 아닙니다. 다시 입력해주세요.\n>");
		goto INVALIDINPUT;
	}

	// 해당 파일찾아가기
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
	switch (getAccType(i_AccNum)) // 타입체크
	{
	case T1: // 입출금은 계좌마다
		type = T1;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", g_tempwcp[1], g_tempwcp);
		break;
	case T2: // 예금은 하나
		type = T2;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", g_tempwcp[1], g_tempwcp[0], g_tempwcp[1], g_tempwcp[2]);
		break;
	case T3: // 적금도 하나
		type = T3;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", g_tempwcp[1], g_tempwcp[0], g_tempwcp[1], g_tempwcp[2]);
		break;
	default:
		PRINTRIGHT(L"계좌번호가 올바르지 않습니다. 다시 입력해주세요.\n >");
		goto INVALIDINPUT;
	}
	free(g_tempwcp);
	g_tempwcp = NULL;

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL) // 파일 이름 없으면 다시
	{
		PRINTRIGHT(L"계좌번호를 찾을 수 없습니다. 다시 입력해주세요...\n> ");
		goto INVALIDINPUT;
	}

	for (int i = 0; i < g_userALNums; i++) //사용자 소유 계좌인지 확인
	{
		if (strncmp(i_AccNum, g_userAccountsList[i], 7) == 0)
		{
			userHaveFlag = 1;
			break;
		}
	}
	if (userHaveFlag == 0)
	{
		PRINTRIGHT(L"계좌번호를 찾을 수 없습니다. 혹시 다른 사람 계좌번호는 아닐까요?\n>");
		goto INVALIDINPUT;
	}
	//출력 테스트
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
			if (CurrentFileOffset == 0) // 첫줄은 계좌 속성
			{
				ia = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
				strToIOatt_malloc(g_buffer, ia);
				printIOatt(ia);
				freeIOattriutes(ia);
				free(ia);
				ia = NULL;
				accCounter++;
			}
			else // 두번쨰 줄은 계좌 내역
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
			if (CurrentFileOffset == 0) // 첫줄은 계좌 속성
			{
				fsa = (FSattributes_t*)malloc(sizeof(FSattributes_t));
				if (strToFSatt(g_buffer, fsa, i_AccNum) == 1)  // 예적금 모음 파일 안에 해당 계좌가 있는지 확인
				{
					printFSatt(fsa);
					accCounter++;
				}
				free(fsa);
				fsa = NULL;
			}
			else // 두번쨰 줄은 계좌 내역
			{
				if (accCounter != 0)
				{
					fsi = (FSinqury_t*)malloc(sizeof(FSinqury_t));
					if (strToFSiq(g_buffer, fsi, i_AccNum) == 1) // 예적금 모음 파일 안에 해당 계좌가 있는지 확인
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

		CurrentFileOffset = ftell(f_Account); //다음줄
	}
	if (accCounter == 0)
	{
		PRINTRIGHT(L"해당 계좌는 존재하지 않습니다. 다시 입력해주세요...\n> ");
		goto INVALIDINPUT;
	}

	fclose(f_Account);
	f_Account = NULL;
#endif
	system("pause");

	return;
}
