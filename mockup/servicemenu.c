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
//void fixedDepositAndSavingsMenu()
//{
//	int selection;
//
//	system("cls");
//	PRINTCEN(L"예금과 적금 메뉴");
//	DRAWLINE('-');
//	PRINTLEFT(L"1) 예적금 상품 신청  2) 예적금 상품 이자조회 및 해지");
//INVALIDINPUT:
//	PRINTLEFT(L"주어진 메뉴의 번호를 입력하세요.");
//	wprintf(L"> ");
//
//	GET_G_INPUT;
//	Q_CHECK();
//
//	selection = atoi(g_buffer);
//
//	switch (selection)
//	{
//	case 1:
//		while (1)
//		{
//			system("cls");
//			PRINTLEFT(L"1) 예금	2) 적금");
//			GET_G_INPUT;
//			if (*g_buffer == ':')
//			{
//				if (*(g_buffer + 1) == 'q')
//				{
//					wprintf(L"뒤로가기 입력함 :q\n"); system("pause");
//					goto ESCAPE;
//				}
//			}
//			if (atoi(g_buffer) == 1)
//			{
//				fixedDeposit();
//				goto ESCAPE;
//			}
//			else if (atoi(g_buffer) == 2)
//			{
//				Savings();
//				goto ESCAPE;
//			}
//		}
//	ESCAPE:
//		return;
//	case 2:
//		inquiryAndCancel();
//		return;
//	default:
//		goto INVALIDINPUT;
//	}
//}
//void fixedDeposit()
//{
//	system("cls");
//	PRINTCEN(L"예금 신청");
//	DRAWLINE('-');
//}
//void Savings()
//{
//	system("cls");
//	PRINTCEN(L" 적금 신청");
//	DRAWLINE('-');
//}
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
}
void transferMenu()
{
	system("cls");
	PRINTCEN(L"계좌 이체 메뉴");
	DRAWLINE('-');
}
void historyInquiry()
{
	char i_AccNum[8] = { 0, };
	long CurrentFileOffset = 0;
	FILE* f_Account;
	
	system("cls");
	PRINTCEN(L"내역 확인 메뉴");
	DRAWLINE('-');

#if TEST_OFF
	PRINTRIGHT(L"조회하고자 하는 계좌번호를 입력해주세요");
	printf("> ");
INVALIDINPUT:
	GET_G_INPUT;
	Q_CHECK();

	//계좌번호 분석
	int j =0,k= 0;
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
	// 해당 계좌 파일찾아가기
	tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(i_AccNum)+1));
	for (int i = 0; i < strlen(i_AccNum)+1; i++)
	{
		mbtowc(tempwcp+i,i_AccNum+i , MB_CUR_MAX);
	}
	swprintf(g_wpath,MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt",i_AccNum[1] ,tempwcp);
	free(tempwcp);

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL)
	{
		PRINTRIGHT(L"계좌번호를 찾을 수 없습니다. 다시 입력해주세요...");
		goto INVALIDINPUT;
	}

	//출력 테스트
	while (1)
	{
		fseek(f_Account, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_Account);
		if (feof(f_Account))
		{
			break;
		}
		printf("%s", g_buffer);

		CurrentFileOffset = ftell(f_Account);
	}
	
	fclose(f_Account);
#endif
	wprintf(L"뒤로가기 커맨드 입력 안함. \n");
	system("pause");

	return;
}
