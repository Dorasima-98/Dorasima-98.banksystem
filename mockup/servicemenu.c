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
//void fixedDepositAndSavingsMenu()
//{
//	int selection;
//
//	system("cls");
//	PRINTCEN(L"���ݰ� ���� �޴�");
//	DRAWLINE('-');
//	PRINTLEFT(L"1) ������ ��ǰ ��û  2) ������ ��ǰ ������ȸ �� ����");
//INVALIDINPUT:
//	PRINTLEFT(L"�־��� �޴��� ��ȣ�� �Է��ϼ���.");
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
//			PRINTLEFT(L"1) ����	2) ����");
//			GET_G_INPUT;
//			if (*g_buffer == ':')
//			{
//				if (*(g_buffer + 1) == 'q')
//				{
//					wprintf(L"�ڷΰ��� �Է��� :q\n"); system("pause");
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
//	PRINTCEN(L"���� ��û");
//	DRAWLINE('-');
//}
//void Savings()
//{
//	system("cls");
//	PRINTCEN(L" ���� ��û");
//	DRAWLINE('-');
//}
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
	char i_AccNum[8] = { 0, };
	long CurrentFileOffset = 0;
	FILE* f_Account;
	
	system("cls");
	PRINTCEN(L"���� Ȯ�� �޴�");
	DRAWLINE('-');

#if TEST_OFF
	PRINTRIGHT(L"��ȸ�ϰ��� �ϴ� ���¹�ȣ�� �Է����ּ���");
	printf("> ");
INVALIDINPUT:
	GET_G_INPUT;
	Q_CHECK();

	//���¹�ȣ �м�
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
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ� ����� �ƴմϴ�. �ٽ� �Է����ּ���.");
		goto INVALIDINPUT;
	}
	// �ش� ���� ����ã�ư���
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
		PRINTRIGHT(L"���¹�ȣ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���...");
		goto INVALIDINPUT;
	}

	//��� �׽�Ʈ
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
	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����. \n");
	system("pause");

	return;
}
