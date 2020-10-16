#include "userfunc.h"

static int con_flag = 1;

int serviceMenu()
{
	int menuSelection;
	con_flag = 1;
	system("cls");
	PRINTCEN(L"���� �޴�");
	DRAWLINE('-');

	PRINTLEFT(L"1) ���� ���� 2) ���ݰ� ���� 3) �Աݰ� ���");
	PRINTLEFT(L"4) ���� ��ü 5) ���� ���� 6) �α׾ƿ�");
	DRAWLINE('-');
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
	PRINTCEN(L"���»��� �޴�");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}
void fixedDepositAndSavingsMenu()
{
	int selection;

	system("cls");
	PRINTCEN(L"���ݰ� ���� �޴�");
	DRAWLINE('-');
	PRINTLEFT(L"1) ������ ��ǰ ��û  2) ������ ��ǰ ����");
INVALIDINPUT:
	PRINTLEFT(L"�־��� �޴��� ��ȣ�� �Է��ϼ���.");
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
			PRINTLEFT(L"1) ����	2) ����");
			GET_G_INPUT;
			if (*g_buffer == ':')
			{
				if (*(g_buffer + 1) == 'q')
				{
					wprintf(L"�ڷΰ��� �Է��� :q\n"); system("pause");
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
	PRINTCEN(L"���� ��û");
	DRAWLINE('-');
	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}
void Savings()
{
	system("cls");
	PRINTCEN(L" ���� ��û");
	DRAWLINE('-');
	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}
void inquiryAndCancel()
{
	system("cls");
	PRINTCEN(L"���� Ȯ�� �� ����");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}

void atmMenu()
{
	system("cls");
	PRINTCEN(L"����� �޴�");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}
void transferMenu()
{
	system("cls");
	PRINTCEN(L"���� ��ü �޴�");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}
void historyInquiry()
{
	system("cls");
	PRINTCEN(L"���� Ȯ�� �޴�");
	DRAWLINE('-');

	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����. \n");
	system("pause");
}
