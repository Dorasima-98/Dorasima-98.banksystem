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
#include "userfunc.h"

void registerMenu() {
#if TEST_OFF
	char Name[100];
	int Bank;
	char Id[100];
	char password1[100];
	char password2[100];
	int pass = 0;
	int passcount = 0;

	//����� �̸�
Invalidinput1:
	PRINTLEFT(L"����� �̸��� �Է����ּ���");
	wprintf(L">");
	scanf_s("%s", Name, sizoef(Name));
	/*GET_G_INPUT;	�Է��� ���°��� üũ, ���߿� ����
	Q_CHECK;		:Q �����°� üũ*/
	EraseSpace(Name);
	for (int i = 0; ; i++) {
		if (Name[i] == NULL) {
			if (0 < i && i <= 40) {
				PRINTLEFT(L"���̵� ����� �Է��߽��ϴ�, ������ �����մϴ�");
				Sleep(5000);
				system("cls");
			}
			else {
				PRINTLEFT(L"�̸��Ǳ��̰� �ʰ��ƽ��ϴ�, �̸��� �ٽ� �Է����ּ���\n");
				goto Invalidinput1;
			}
		}
	}

	//����
Invalidinput2:
	DRAWLINE('-');
	PRINTCEN(L"������-1  ������-2  ������-3  ������-4  ������-5");
	DRAWLINE('-');
	PRINTLEFT(L"������ �������ּ���");
	wprintf(L">");
	scanf_s("%d", &Bank, sizeof(Bank));	//�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
	/*GET_G_INPUT;
	Q_CHECK;*/
	if (1 <= Bank && Bank <= 5) {
		printf("������ ���õǾ����ϴ�");
		Sleep(5000);
		system("cls");
	}
	else {
		PRINTLEFT(L"������ �ٽ� �Է����ּ���");
		goto Invalidinput2;
	}

	//���̵�
Invalidinput3:
	PRINTLEFT(L"���̵�");
	wprintf(L">");
	scanf_s("%s", Id, sizeof(Id));
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	for (int i = 0; i < strlen(Id); i++) {
		if (isalnum(Id[i]) != NULL) 			//������ �Ǵ� �����̸� 0�ƴ� �� ��ȯ
			continue;
		else {
			PRINTLEFT(L"�߸��� �Է��� ���Խ��ϴ�, �ٽ� �Է����ּ���");
			goto Invalidinput3;
		}

		if (Id[i] = NULL) {
			PRINTLEFT(L"���̵� �Է��� �ƽ��ϴ�");
			PRINTLEFT(L"��й�ȣ�� �Է��մϴ�");
			Sleep(5000);
			system("cls");
			break;
		}
	}

	//��й�ȣ
	do {
		PRINTLEFT(L"��й�ȣ");
		wprintf(L">");
		/*GET_G_INPUT;
		Q_CHECK;*/
		scanf_s("%s", password1, sizeof(password1));
		EraseSpace(password1);
		PRINTLEFT(L"��й�ȣ Ȯ��");
		wprintf(L">");
		scanf_s("%s", password2, sizeof(password2));
		EraseSpace(password2);

		for (int i = 0; i < strlen(password1); i++) {
			if (strcmp(password1[i], password2[i]) == 0)
				pass += 0;
			else
				pass++;
		}

		if (pass > 0) {
			PRINTLEFT(L"��й�ȣ�� �ٸ��� �Է��߽��ϴ�, �ٽ� �Է����ּ���");
			passcount++;	//�Է�Ƚ�� - 5�� �Ѿ�� �ȵ�
		}
		else if (pass == 0)
			PRINTLEFT(L"��й�ȣ�� ����� �Է��߽��ϴ�");

		if (passcount == 5) {
			PRINTLEFT(L"��й�ȣ �Է�Ƚ�� 5ȸ�ʰ�");
			PRINTLEFT(L"���α׷� ����");
			Sleep(5000);
			system("cls");
			exit(0); //�������� ���� 0, ���������� ���� 1
		}
	} while (passcount < 5);

#endif
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
