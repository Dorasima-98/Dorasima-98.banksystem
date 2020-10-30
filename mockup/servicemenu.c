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

	PRINTLEFT(L"1) 계좌 생성 (?) 2) 예금과 적금 (?) 3) 입금과 출금 (?)");
	PRINTLEFT(L"4) 계좌 이체 (?) 5) 계좌 내역   (o) 6) 로그아웃    (o)");
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
			PRINTRIGHT(L"입출금이 없는데 뭔 예적금입니까?");
			goto INVALIDINPUT;
		}
		fixedDepositAndSavingsMenu();
		break;
	case 3:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"돈은 있으세요? 입출금 계좌 먼저 만드세요.");
			goto INVALIDINPUT;
		}
		transferMenu();
		break;
	case 4:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"좋은 말로할때 1번 메뉴 선택하세요.");
			goto INVALIDINPUT;
		}
		atmMenu();
		break;
	case 5:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"볼게 없습니다. 1번 메뉴로 가셔서 입출금 계좌먼저 만드세요.");
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
	//Q_CHECK();

	AccountName_malloc = trim_malloc(AccountName_malloc, g_buffer);
	assert(AccountName_malloc != NULL && "trim is Something wrong...");

	if (strlen(AccountName_malloc) > 16 || strlen(AccountName_malloc) < 1)
	{
		PRINTRIGHT(L"이름의 길이는 1자 ~ 16자 입니다. 다시 입력해주세요.\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (strlen(AccountName_malloc) == 1 && isdigit(*AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"한 글자로 지정하시려면 알파벳으로 입력 해주세요...\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkAlnum(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"계좌명은 알파벳 기본, 숫자 선택으로 입력 해주세요..\n> ");
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
	if (strncmp(PIN2, PIN1,4) != 0)
	{
		PRINTRIGHT(L"PassWords가 서로 일치하지 않습니다.\n ");
		PRINTLEFT(L"PassWords 를 다시한번 입력하세요. \n> ");
		free(PIN2);
		PIN2 = NULL;
		goto Invalidinput3;
	}

	srand(time(NULL));
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

	toListfile = (char*)malloc(sizeof(char)*toLfnums);
	toTargetfile = (char*)malloc(sizeof(char) * toTfnums);

	sprintf(toListfile, "%s|%s|\n", ranNum, AccountName_malloc);
	sprintf(toTargetfile, "%s|%s|0|%s|300|5000|\n", AccountName_malloc, ranNum, PIN1);



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
	fseek(f_MemberFile, CurrentFileOffset+1, SEEK_SET);

	size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_MemberFile);
	fseek(f_MemberFile, CurrentFileOffset+1, SEEK_SET);
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

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");	system("pause");

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
	Q_CHECK();

	selection = atoi(g_buffer);

	switch (selection)
	{
	case 1:
		while (1)
		{
			system("cls");
			PRINTLEFT(L"1) 예금	2) 적금");
			GET_G_INPUT;
			if (*g_buffer == ':')
			{
				if (*(g_buffer + 1) == 'q')
				{
					wprintf(L"뒤로가기 입력함 :q\n"); system("pause");
					goto ESCAPE;
				}
			}
			if (atoi(g_buffer) == 1)
			{
				fixedDeposit();
				goto ESCAPE;
			}
			else if (atoi(g_buffer) == 2)
			{
				Savings();
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
void fixedDeposit()
{
#if TEST_OFF
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //이자율
	int duration; //예금 기간(6개월이면 6, 1년이면 1, 2년이면 2)
	float fixedDepositMoney = 0.0; //예치금(납입액)
	float finalFixedDepositMoney = 0.0; //만기해지금
	int selection;
	char accountName[10]; //예금계좌명
	char* ptrAdd[30];
	int p = 0;
	inputFile = fopen("ioaccount.txt", "r"); //일단 테스트용 파일로 해보기

	system("cls");
	PRINTCEN(L"출금할 계좌 선택");
	DRAWLINE('-');
	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	if (inputFile != NULL)
	{
		char buffer[256]; //나중에 수정해야함
		while (!feof(inputFile))
		{
			fgets(buffer, sizeof(buffer), inputFile);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			printf("%s\n", ptr);
			while (ptr != NULL)
			{
				ptrAdd[p] = ptr;
				ptr = strtok(NULL, "\n");

			}
		}
	}
	GET_G_INPUT;
	fclose(inputFile);

	int accountSelection;

	inputFile = fopen("ioaccount.txt", "r");

	p = 0;

	if (inputFile != NULL)
	{
		char buffer2[256]; //나중에 수정해야함
		printf("%d\n", p);

		while (!feof(inputFile))
		{
			fgets(buffer2, sizeof(buffer2), inputFile);
			char* ptr2 = strtok(buffer2, "\n|");
			while (ptr2 != NULL)
			{
				ptrAdd[p] = ptr2;
				ptr2 = strtok(NULL, "\n|");
				printf("%d", p);
				printf("ptrAdd[%d]는 %s임\n", p, ptrAdd[p]);
				p++;

			}
			printf("ptrAdd[%d]는 %s임\n", p, ptrAdd[p]); 
		}
	}

	int moneySelection = 0;
	/*g_buffer에 해당하는 숫자 라인의 입출금계좌에서 출금*/

	if (atoi(g_buffer))
	{
		moneySelection = 2 + 5 * (atoi(g_buffer) - 1);
		printf("%d", moneySelection);
		printf("ptrAdd [%d] 는 %d 입니당", moneySelection, atoi(ptrAdd[moneySelection]));
		if (atoi(ptrAdd[moneySelection]) == 111111)
		{
			printf("hello");
		}
	}

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

	//원래 여기 아까 선택한 계좌 잔액보다 적은지 많은지, 1원 이상인지 if문 있어야 함!!

	printf("%.5f 만원이 예금계좌에 예치되었습니다^v^\n", fixedDepositMoney);

	//만기수령액 계산하기
	switch (selection)
	{
	case 1:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.01 * 0.5;
		printf("만기수령액은 %.5f만원 입니다.\n", finalFixedDepositMoney);
		break;

	case 2:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.015;
		printf("만기수령액은 %.5f만원 입니다.\n", finalFixedDepositMoney);
		break;

	case 3:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.02 * 2;
		printf("만기수령액은 %.5f만원 입니다.\n", finalFixedDepositMoney);
		break;
	}

	//계좌번호 랜덤생성
	srand(time(NULL));
	char accountNum[8];

	//01은 은행에 따라 바꿔야함. 나중에 계정생성 파트 하시는 분한테 전역변수로 해달라고 말씀드려야 함

	accountNum[0] = '0';
	if (Bank != 0)
		accountNum[1] = atoi(Bank, accountNum, 10);
	accountNum[2] = '2';
	accountNum[7] = '\0';

	for (int k = 3; k < 7; k++)
	{
		accountNum[k] = rand() % 10 + 48;
	}

	printf("예금 계좌번호는 %s입니다^v^\n", accountNum);

	int accountPassword = 1234; //입출금계좌에서 받아오기

	system("pause");

	//마지막 줄에는 "추가된 계좌정보" 들어감
	inputFile = fopen("fixed.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%f\n", accountName, accountNum, finalFixedDepositMoney, fixedDepositMoney);
	fclose(inputFile);

	//첫 줄에는 "계좌명, 계좌번호, 해당 계좌의 잔액, 계좌 비밀번호, 서비스 신청기간, 이자율, 해지 시 수령액의 조합"이 들어감!
	//해당 계좌 잔액, 계좌 비밀번호는 지금 구현 못해서 그거 빼고 나머지는 첫 줄에 씀
	inputFile = fopen("fixed_shortcut.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%d|%d|%f|%f ", accountName, accountNum, fixedDepositMoney, accountPassword, duration, rate, finalFixedDepositMoney);
	fclose(inputFile);

	//Q_CHECK();
	//wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	//system("pause");
#endif
}

void Savings()
{
#if TEST_OFF
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //이자율
	int duration; //적금 기간(6개월이면 6, 1년이면 1, 2년이면 2)
	float savingsDepositMoney = 0.0; //예치금(납입액)
	int selection;
	char accountName[10]; //적금계좌명

	inputFile = fopen("ioaccount.txt", "r"); //일단 테스트용 파일로 해보기

	system("cls");
	PRINTCEN(L"출금할 계좌 선택");
	DRAWLINE('-');
	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	if (inputFile != NULL)
	{
		char buffer[256]; //나중에 수정해야함
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
	GET_G_INPUT;
	fclose(inputFile);

	/*g_buffer에 해당하는 숫자 라인의 입출금계좌에서 출금 후 예금계좌 생성해야하는데
	파일 정리가 안돼서 printf로 대체함*/
	if (atoi(g_buffer) == 1)
	{
		printf("1번선택함~~\n");
	}
	else
	{
		printf("다른거 선택함~~\n");
	}

	PRINTCEN(L"계좌명 입력");
	DRAWLINE('-');
	printf("적금 계좌명을 입력해주세요.\n");
	wprintf(L"> ");
	scanf("%s", &accountName);
	printf("적금 계좌명이 %s로 설정되었습니다\n", accountName);
	system("pause");

	system("cls");
	PRINTCEN(L"만기일 선택");
	DRAWLINE('-');
	PRINTCEN(L"===선택한 서비스의 만기일을 선택해주세요===");
	PRINTLEFT(L"만기일  1) 6개월(1.0%)   2) 1년(1.5%)   3) 2년(2.0%)");
	wprintf(L"> ");

	scanf_s("%d", &selection, 1);

	//printf는 그냥 확인용이라 다 빼야함. rate는 나중에 예금파일 첫 줄에 적어야 함
	//나중에 이자율로 만기일 유추하는게 나을 것 같음
	switch (selection)
	{
	case 1:
		rate = 1.0;
		duration = 6;
		printf("6개월 선택완료\n");
		break;

	case 2:
		rate = 1.5;
		duration = 1;
		printf("1년 선택완료\n");
		break;

	case 3:
		rate = 2.0;
		duration = 2;
		printf("2년 선택완료\n");
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

	scanf("%f", &savingsDepositMoney);

	//원래 여기 아까 선택한 계좌 잔액보다 적은지 많은지, 1원 이상인지 if문 있어야 함!!
	printf("%.5f 만원이 적금계좌에 납입되었습니다^v^\n", savingsDepositMoney);


	//계좌번호 랜덤생성
	char accountNum[8];

	//01은 은행에 따라 바꿔야함. 나중에 계정생성 파트 하시는 분한테 전역변수로 해달라고 말씀드려야 함

	accountNum[0] = '0';
	accountNum[1] = '1';
	accountNum[2] = '3';
	accountNum[7] = '\0';

	for (int k = 3; k < 7; k++)
	{
		accountNum[k] = rand() % 10 + 48;
	}

	printf("적금 계좌번호는 %s입니다^v^\n", accountNum);

	int accountPassword = 1234; //입출금계좌에서 받아오기

	inputFile = fopen("savings_shortcut.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%d|%d|%f ", accountName, accountNum, savingsDepositMoney, accountPassword, duration, rate);
	fclose(inputFile);

	system("pause");
	//그리고 예금파일 첫 줄에 "해당 계좌의 잔액, 계좌 비밀번호, 서비스 신청기간, 이자율, 해지 시 수령액의 조합"이 들어감!
	//해당 계좌 잔액, 계좌 비밀번호는 지금 구현 못해서 그거 빼고 나머지는 첫 줄에 씀


	//Q_CHECK();
	//wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	//system("pause");
#endif
}

void inquiryAndCancel() //Cancel 만 하기~~~
{
	FILE* inputFile = NULL;

	/*
	char accountName[6];

	char account[7];
	char finalDate[8];
	int money = 0; //여기에 금액을 받아오고 싶은데 어떻게 할지 모르겠당,,

	system("cls");
	PRINTCEN(L"내역 확인 및 해지");
	DRAWLINE('-');
	PRINTLEFT(L"예금 또는 적금 계좌번호 7자리와 해지예상일자 8자리(yyyymmdd)를 공백없이 입력해주세요");
	wprintf(L"> ");
	//7자리는 계좌번호, 그 다음 8자리는 해지예상일자

	GET_G_INPUT;
	if (*g_buffer == ':')
	{
		if (*(g_buffer + 1) == 'q')
		{
			wprintf(L"뒤로가기 입력함 :q\n"); system("pause");
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
	system("pause"); //입력받은거 잘 저장됐나 확인하려고 pause해둠. printf함수들 나중에 다 지워야 함.

	//예금 또는 적금계좌 파일에서 string 받아오기(|로 항목 구분)
	inputFile = fopen("fixed.txt", "r"); //일단 테스트용 파일로 해보기
	if (inputFile != NULL) {
		char buffer[256]; //나중에 수정해야함
		while (!feof(inputFile)) {
			fgets(buffer, sizeof(buffer), inputFile);
			char* ptr = strtok(buffer, "|");
			while (ptr != NULL) {
				printf("%s\n", ptr); //잘 들어가나 확인용(나중에 지워야 함)
				ptr = strtok(NULL, "|");
			}
			if (ptr == account) {
				//계좌번호가 같으면, 다음 ptr 받아서 저장하고 loop 탈출
				//예금의 경우 해당하는 계좌에 대한 만기해지시 금액을 받아옴
				//적금의 경우 해당하는 계좌에 대한 입금액을 받아옴
				money = 1;
				printf("%d\n", money);
			}
		}
	}

	fclose(inputFile);
	printf("%d\n", money); //지워야 함. 테스트한다고 적은 것
	system("pause");

	system("cls");
	PRINTCEN(L"예적금 이자조회");
	DRAWLINE('-');
	//입력받은 해지예상일자(8~15자리) 비교
	wprintf(L"신청한 날짜/경과된 기간/해지이자/최종수령금액"); //이것도 실제 값으로 출력돼야함. 나중에 바꾸기
	printf("\n");
	system("pause");

	system("cls");
	//안녕
	*/

	PRINTCEN(L"예적금 해지");
	DRAWLINE('-');
	PRINTLEFT(L"예적금을 해지하시겠습니까?(y/n)");
	wprintf(L"> ");
	GET_G_INPUT;

	if (*g_buffer == 'y' || *g_buffer == 'Y')
	{
		wprintf(L"해당 예적금 계좌를 해지했습니다. ");
		system("pause");
		//계좌정보 삭제 함수 필요, 지정된 입출금계좌에 돈 입금도 해야함
	}
	else if (*g_buffer == 'n' || *g_buffer == 'N')
	{
		wprintf(L"해당 예적금 계좌를 해지하지 않았습니다. ");
		system("pause");
	}
	else
	{
		goto INVALIDINPUT;
	}

INVALIDINPUT:
	return; //해야함
ESCAPE:
	return; //해야함

}

void atmMenu()
{
	system("cls");
	PRINTCEN(L"입출금 메뉴");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
}
void transferMenu()
{
	system("cls");
	PRINTCEN(L"계좌 이체 메뉴");
	DRAWLINE('-');
	GET_G_INPUT;

	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
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
	Q_CHECK();

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
	if (tempwcp != NULL)
	{
		free(tempwcp);
		tempwcp = NULL;
	}

	tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(i_AccNum) + 1));
	for (int i = 0; i < strlen(i_AccNum) + 1; i++)
	{
		mbtowc(tempwcp + i, i_AccNum + i, MB_CUR_MAX);
	}
	switch (getAccType(i_AccNum)) // 타입체크
	{
	case T1: // 입출금은 계좌마다
		type = T1;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", tempwcp[1], tempwcp);
		break;
	case T2: // 예금은 하나
		type = T2;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0], tempwcp[1], tempwcp[2]);
		break;
	case T3: // 적금도 하나
		type = T3;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0], tempwcp[1], tempwcp[2]);
		break;
	default:
		PRINTRIGHT(L"계좌번호가 올바르지 않습니다. 다시 입력해주세요.\n >");
		goto INVALIDINPUT;
	}
	free(tempwcp);
	tempwcp = NULL;

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL) // 파일 이름 없으면 다시
	{
		PRINTRIGHT(L"계좌번호를 찾을 수 없습니다. 다시 입력해주세요...\n> " );
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
			if (CurrentFileOffset != -1) // 첫줄은 계좌 속성
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
				if (strToFSatt(g_buffer, fsa, i_AccNum)== 1)  // 예적금 모음 파일 안에 해당 계좌가 있는지 확인
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
	wprintf(L"뒤로가기 커맨드 입력 안함. \n");
	system("pause");

	return;
}
