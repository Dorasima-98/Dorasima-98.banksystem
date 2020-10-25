//아직 한참 덜 함ㅜㅜ

#include "userfunc.h"

static int con_flag = 1;


int serviceMenu()
{
	int menuSelection;
	con_flag = 1;
	system("cls");
	PRINTCEN(L"서비스 메뉴");
	DRAWLINE('-');

	PRINTLEFT(L"1) 계좌 생성 2) 예금과 적금 3) 입금과 출금");
	PRINTLEFT(L"4) 계좌 이체 5) 계좌 내역 6) 로그아웃");
	DRAWLINE('-');
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
		fixedDepositAndSavingsMenu();
		break;
	case 3:
		transferMenu();
		break;
	case 4:
		atmMenu();
		break;
	case 5:
		historyInquiry();
		break;
	case 6:
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

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
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
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //이자율
	int duration; //예금 기간(6개월이면 6, 1년이면 1, 2년이면 2)
	float fixedDepositMoney = 0.0; //예치금(납입액)
	float finalFixedDepositMoney = 0.0; //만기해지금
	int selection;
	char accountName[10]; //예금계좌명

	inputFile = fopen("ioaccount.txt", "r"); //일단 테스트용 파일로 해보기

	system("cls");
	PRINTCEN(L"출금할 계좌 선택");
	DRAWLINE('-');
	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	if (inputFile != NULL) {
		char buffer[256]; //나중에 수정해야함
		while (!feof(inputFile)) {
			fgets(buffer, sizeof(buffer), inputFile);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			while (ptr != NULL) {
				printf("%s\n", ptr);
				ptr = strtok(NULL, "\n");
			}
		}
	}
	GET_G_INPUT;
	fclose(inputFile);

	/*g_buffer에 해당하는 숫자 라인의 입출금계좌에서 출금 후 예금계좌 생성해야하는데
	파일 정리가 안돼서 printf로 대체함*/
	if (atoi(g_buffer) == 1) {
		printf("1번선택함~~\n");
	}
	else {
		printf("다른거 선택함~~\n");
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
	//나중에 이자율로 만기일 유추하는게 나을 것 같음
	switch (selection) {
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
	
	scanf("%f", &fixedDepositMoney);

	//원래 여기 아까 선택한 계좌 잔액보다 적은지 많은지, 1원 이상인지 if문 있어야 함!!
	if (fixedDepositMoney < 1 || fixedDepositMoney > 1000) {
		printf("납입한도액을 넘겼습니다. 처음부터 다시 하세요~~"); 
		//이것도 다시 입력받는걸로 바꾸기
	}
	else {
		printf("%.5f 만원이 예금계좌에 예치되었습니다^v^\n", fixedDepositMoney);
	}

	//만기수령액 계산하기
	switch (selection) {
		case 1:
			finalFixedDepositMoney = fixedDepositMoney+fixedDepositMoney*0.01*0.5;
			printf("만기수령액은 %.5f만원 입니다.\n", fixedDepositMoney);
			break;

		case 2:
			finalFixedDepositMoney = fixedDepositMoney+fixedDepositMoney*0.015;
			printf("만기수령액은 %.5f만원 입니다.\n", fixedDepositMoney);
			break;

		case 3:
			finalFixedDepositMoney = fixedDepositMoney+fixedDepositMoney*0.02*2;
			printf("만기수령액은 %.5f만원 입니다.\n", fixedDepositMoney);
			break;
	}

	//계좌번호 랜덤생성
	srand(time(NULL));
	char accountNum[8];

	//01은 은행에 따라 바꿔야함. 나중에 계정생성 파트 하시는 분한테 전역변수로 해달라고 말씀드려야 함

	accountNum[0] = '0';
	accountNum[1] = '1';
	accountNum[2] = '2';
	accountNum[7] = '\0';

	for (int k = 3; k < 7; k++) {
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
	//inputFile = fopen("fixed.txt", "r+");
	//fprintf(inputFile, " %s|%s|%f|%d|%d|%f|%f", accountName, accountNum, fixedDepositMoney, accountPassword, duration, rate, finalFixedDepositMoney);
	//fclose(inputFile);
	
	//파일포인터 다시 제일 마지막으로 옮기기

	//Q_CHECK();
	//wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	//system("pause");
}

void Savings()
{
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //이자율
	int duration; //적금 기간(6개월이면 6, 1년이면 1, 2년이면 2)
	float fixedDepositMoney = 0.0; //예치금(납입액)
	int selection;
	char accountName[10]; //적금계좌명

	inputFile = fopen("ioaccount.txt", "r"); //일단 테스트용 파일로 해보기

	system("cls");
	PRINTCEN(L"출금할 계좌 선택");
	DRAWLINE('-');
	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	if (inputFile != NULL) {
		char buffer[256]; //나중에 수정해야함
		while (!feof(inputFile)) {
			fgets(buffer, sizeof(buffer), inputFile);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			while (ptr != NULL) {
				printf("%s\n", ptr);
				ptr = strtok(NULL, "\n");
			}
		}
	}
	GET_G_INPUT;
	fclose(inputFile);

	/*g_buffer에 해당하는 숫자 라인의 입출금계좌에서 출금 후 예금계좌 생성해야하는데
	파일 정리가 안돼서 printf로 대체함*/
	if (atoi(g_buffer) == 1) {
		printf("1번선택함~~\n");
	}
	else {
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
	switch (selection) {
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

	scanf("%f", &fixedDepositMoney);

	//원래 여기 아까 선택한 계좌 잔액보다 적은지 많은지, 1원 이상인지 if문 있어야 함!!
	if (fixedDepositMoney < 1 || fixedDepositMoney > 1000) {
		printf("납입한도액을 넘겼습니다. 처음부터 다시 하세요~~");
		//이것도 다시 입력받는걸로 바꾸기
	}
	else {
		printf("%.5f 만원이 적금계좌에 납입되었습니다^v^\n", fixedDepositMoney);
	}

	//계좌번호 랜덤생성
	srand(time(NULL));
	char accountNum[4];

	printf("적금 계좌번호는 013"); 	//01은 은행에 따라 바꿔야함. 나중에 계정생성 파트 하시는 분한테 전역변수로 해달라고 말씀드려야 함

	for (int k = 0; k < 4; k++) {
		accountNum[k] = rand() % 10 + 48;
		printf("%c", accountNum[k]);
	}
	printf("입니다^v^\n");

	system("pause");
	//그리고 예금파일 첫 줄에 "해당 계좌의 잔액, 계좌 비밀번호, 서비스 신청기간, 이자율, 해지 시 수령액의 조합"이 들어감!
	//해당 계좌 잔액, 계좌 비밀번호는 지금 구현 못해서 그거 빼고 나머지는 첫 줄에 씀
	//inputFile = fopen("fixed.txt", "a");
	//fprintf(inputFile, "%s|%d|%f|%f ", accountName, duration, rate, fixedDepositMoney);
	//fclose(inputFile);

	//Q_CHECK();
	//wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	//system("pause");
}

void inquiryAndCancel()
{	
	FILE* inputFile = NULL;
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
	else if (*g_buffer == 'n' || *g_buffer == 'N') {
		wprintf(L"해당 예적금 계좌를 해지하지 않았습니다. ");
		system("pause");
	}
	else {
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

	system("cls");
	PRINTCEN(L"내역 확인 메뉴");
	DRAWLINE('-');

#if TEST_ON 
	PRINTRIGHT(L"조회하고자 하는 계좌번호를 입력해주세요");
	printf("> ");
INVALIDINPUT:
	GET_G_INPUT;
	Q_CHECK();

	//계좌번호 분석
	int j = 0;
	int k = 0;
	for (int i = 0; i < sizeof(i_AccNum)+2; i++)
	{
		if (!isdigit(g_buffer[i]))
		{
			if (g_buffer[i] == '-' && (i==2||i==4))
			{
				k++;
				continue;
			}
			else
			{
				break;
			}
		}
		i_AccNum[j++]= g_buffer[i];
	}
	i_AccNum[7] = '\0';
	if (j != 7 || (k !=2 && k!=0))
	{
		PRINTRIGHT(L"계좌번호가 올바른 양식이 아닙니다. 다시 입력해주세요.");
		goto INVALIDINPUT;
	}

	// 해당 파일찾아가기
	tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(i_AccNum)+1));
	for (int i = 0; i < strlen(i_AccNum)+1; i++)
	{
		mbtowc(tempwcp+i,i_AccNum+i , MB_CUR_MAX);
	}
	switch (i_AccNum[2]) // 타입체크
	{
	case '1': // 입출금은 계좌마다
		type = T1;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", tempwcp[1], tempwcp);
		break;
	case '2': // 예금은 하나
		type = T2;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0],tempwcp[1],tempwcp[2]);
		break;
	case'3': // 적금도 일단 하나
		type = T3;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0], tempwcp[1], tempwcp[2]);
		break;
	default:
		PRINTRIGHT(L"계좌번호가 올바르지 않습니다. 다시 입력해주세요.");
		goto INVALIDINPUT;
	}
	free(tempwcp);
	tempwcp = NULL;

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL)
	{
		PRINTRIGHT(L"계좌번호를 찾을 수 없습니다. 다시 입력해주세요...");
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
		//printf("%s", g_buffer);

		if (i > 0)
		{
			accCounter += strToInquiry(g_buffer, i_AccNum, type); //additional_utils.c
		}
		else
		{
			if (type == T1)
			{
				strToAccInfo(g_buffer, i_AccNum, type);
				i++;
			}
			else
			{
				strToFSInfo(g_buffer, i_AccNum, type);
				i++;
			}
			
		}
		CurrentFileOffset = ftell(f_Account);
	}
	if (accCounter == 0)
	{
		PRINTRIGHT(L"해당 계좌는 존재하지 않습니다. 다시 입력해주세요...");
		goto INVALIDINPUT;
	}
	
	fclose(f_Account);
	f_Account = NULL;
#endif
	wprintf(L"뒤로가기 커맨드 입력 안함. \n");
	system("pause");

	return;
}
