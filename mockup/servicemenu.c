//���� ���� �� �Ԥ̤�

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
	PRINTLEFT(L"1) ������ ��ǰ ��û  2) ������ ��ǰ ������ȸ �� ����");
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
}
void Savings()
{
	system("cls");
	PRINTCEN(L" ���� ��û");
	DRAWLINE('-');
}
void inquiryAndCancel()
{	
	FILE* inputFile = NULL;
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
	else if (*g_buffer == 'n' || *g_buffer == 'N') {
		wprintf(L"�ش� ������ ���¸� �������� �ʾҽ��ϴ�. ");
		system("pause");
	}
	else {
		goto INVALIDINPUT;
	}

	INVALIDINPUT:
		return; //�ؾ���
	ESCAPE:
		return; //�ؾ���

}

void atmMenu()
{
	system("cls");
	PRINTCEN(L"����� �޴�");
	DRAWLINE('-');
}
void transferMenu()
{
	system("cls");
	PRINTCEN(L"���� ��ü �޴�");
	DRAWLINE('-');
}
void historyInquiry()
{
	system("cls");
	PRINTCEN(L"���� Ȯ�� �޴�");
	DRAWLINE('-');
}
