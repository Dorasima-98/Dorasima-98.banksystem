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
	PRINTLEFT(L"1) 예적금 상품 신청  2) 예적금 상품 해지");
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
	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
}
void Savings()
{
	system("cls");
	PRINTCEN(L" 적금 신청");
	DRAWLINE('-');
	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
}
void inquiryAndCancel()
{
	system("cls");
	PRINTCEN(L"내역 확인 및 해지");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
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
	system("cls");
	PRINTCEN(L"내역 확인 메뉴");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함. \n");
	system("pause");
}
