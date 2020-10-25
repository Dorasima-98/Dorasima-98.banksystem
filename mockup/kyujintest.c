
#include "userfunc.h"
#include <time.h>

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
	system("cls");
	PRINTCEN(L"예금 신청");
	DRAWLINE('-');
	//파일 읽기
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	int cnt = 0;
	char* account;
	char* n[5] = { 0, };
	char selectIO[10];
	int selectDay = 0;
	float NapMoney = 0;
	float resultMon = 0;
	char accountName[10];

	int lineCount = 1;

	fp1 = fopen("ioaccount.txt", "r");
	//일단 테스트용 파일로 해보기

	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	if (fp1 != NULL) {
		char buffer[256];
		while (!feof(fp1)) {
			fgets(buffer, sizeof(buffer), fp1);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			while (ptr != NULL) {
				printf("%s\n", ptr); //잘 들어가나 확인용(나중에 지워야 함)
				ptr = strtok(NULL, "\n");
			}
		}
	}
	fclose(fp1);
	//입출금 계좌선택
	printf("입출금 계좌를 선택하세요.\n");
	scanf("%s", &selectIO);
	
	printf("예금 계좌명을 입력해주세요.\n");
	scanf("%s", accountName);

	//만기일 선택
	DRAWLINE('-');
	PRINTLEFT(L"===적금 서비스의 만기일을 선택해주세요===");
	PRINTLEFT(L"만기일  1) 6개월(1.0%)   2) 1년(1.5%)   3) 2년(2.0%)");
	wprintf(L"> ");
	scanf("%d", &selectDay);
	//납입액 선택
	printf("납입액을 선택하세요.\n");
	scanf("%f", &NapMoney);
	//최종 수령액 계산
	if (selectDay == 1) {
		resultMon = NapMoney + NapMoney * 0.01 *0.5;
	}
	else if (selectDay == 2) {
		resultMon = NapMoney + NapMoney * 0.015;
	}
	else if (selectDay == 3) {
		resultMon = NapMoney + NapMoney* 0.02 * 2;
	}
	//계좌번호 랜덤생성
	srand(time(NULL));
	int accountnum = rand() % 99999;

	fp2 = fopen("test.txt", "a");
	fprintf(fp2, "날짜|%s|%05d|%f|0 \n", accountName, accountnum, resultMon );
	fclose(fp2);

}



void Savings()
{
	system("cls");
	PRINTCEN(L" 적금 신청");
	DRAWLINE('-');
	//파일 읽기
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	int cnt = 0;
	char* account;
	char* n[5] = { 0, };
	char selectIO[10];
	int selectDay = 0;
	float NapMoney = 0;
	float resultMon = 0;
	char accountName[10];

	int lineCount = 1;

	fp1 = fopen("ioaccount.txt", "r");
	//일단 테스트용 파일로 해보기

	PRINTCEN(L"=== 만기 금액 수령이 가능한 입출금 계좌 목록 ===");

	if (fp1 != NULL) {
		char buffer[256];
		while (!feof(fp1)) {
			fgets(buffer, sizeof(buffer), fp1);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			while (ptr != NULL) {
				printf("%s\n", ptr); //잘 들어가나 확인용(나중에 지워야 함)
				ptr = strtok(NULL, "\n");
			}
		}
	}
	fclose(fp1);
	//입출금 계좌선택
	printf("입출금 계좌를 선택하세요.\n");
	scanf("%s", &selectIO);

	printf("적금 계좌명을 입력해주세요.\n");
	scanf("%s", accountName);

	//만기일 선택
	DRAWLINE('-');
	PRINTLEFT(L"===적금 서비스의 만기일을 선택해주세요===");
	PRINTLEFT(L"만기일  1) 6개월(1.0%)   2) 1년(1.5%)   3) 2년(2.0%)");
	wprintf(L"> ");
	scanf("%d", &selectDay);
	//납입액 선택
	printf("납입액을 선택하세요.\n");
	scanf("%f", &NapMoney);
	//최종 수령액 계산
	if (selectDay == 1) {
		resultMon = 6 * (NapMoney + NapMoney * 0.01 * 0.5);
	}
	else if (selectDay == 2) {
		resultMon = 12 * (NapMoney + NapMoney * 0.015);
	}
	else if (selectDay == 3) {
		resultMon = 24 * (NapMoney + NapMoney * 0.02 * 2);
	}
	//계좌번호 랜덤생성
	srand(time(NULL));
	int accountnum = rand() % 99999;

	fp2 = fopen("test1.txt", "a");
	fprintf(fp2, "날짜|%s|%05d|%f|0 \n", accountName, accountnum, resultMon);
	fclose(fp2);

}
