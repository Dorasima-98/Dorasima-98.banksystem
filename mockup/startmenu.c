#include "userfunc.h"

static int con_flag = 1;

int startMenu()
{
	con_flag = 1;
	int selection;
REPRINT:
	system("cls");
	PRINTCEN(L"�α��� �޴�");
	DRAWLINE('-');
	PRINTLEFT(L"1) �α���	2) ��������	3) ���α׷� ����");
INVALIDINPUT:
	PRINTLEFT(L"�־��� �޴��� ��ȣ�� �������ּ���.");
	GET_G_INPUT;

	selection = atoi(g_buffer);
	switch (selection)
	{
	case 1:
		if (loginMenu())
		{
			break;
		}
		else
		{
			goto REPRINT;
		}
	case 2:
		registerMenu();
		goto REPRINT;
	case 3:
		con_flag = 0;
		break;
	default:
		goto INVALIDINPUT;
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
void registerMenu()
{
	system("cls");
	PRINTCEN(L"�������� �޴�");
	DRAWLINE('-');

	PRINTLEFT(L"���̵� �Է��ϼ���... (���ĺ��� ������ �������� �Է��ϼ���. 8 ~ 16�ڸ�) (�ڷΰ��� \":q\")");
	GET_G_INPUT;
	Q_CHECK();

	PRINTLEFT(L"��й�ȣ�� �Է��ϼ���... (���ĺ��� ���� �׸��� ����Ű Ư�������� �������� �Է��ϼ���[ !@#$%^&*() ]...  ) (�ڷΰ��� \":q\")");
	GET_G_INPUT;
	Q_CHECK();

	PRINTLEFT(L"�ٽ��ѹ� ��й�ȣ�� �Է��ϼ���... ) (�ڷΰ��� \":q\")");
	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
}
int loginMenu()
{
	system("cls");
	PRINTCEN(L"�α��� �޴�");
	DRAWLINE('-');

	PRINTLEFT(L"���̵� �Է��ϼ���...(�ڷΰ��� \":q\")");
	GET_G_INPUT;
	Q_CHECK(0);

	PRINTLEFT(L"��й�ȣ�� �Է��ϼ���...(�ڷΰ��� \":q\")");
	GET_G_INPUT;
	Q_CHECK(0);

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	system("pause");
	return 1;
}
