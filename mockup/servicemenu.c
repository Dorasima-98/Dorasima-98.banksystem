//���� ���� �� �Ԥ̤�

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
	PRINTCEN(L"���� �޴�");
	DRAWLINE('-');

	PRINTLEFT(L"1) ���� ���� (?) 2) ���ݰ� ���� (?) 3) �Աݰ� ��� (?)");
	PRINTLEFT(L"4) ���� ��ü (?) 5) ���� ����   (o) 6) �α׾ƿ�    (o)");
	DRAWLINE('-');
	if (g_userALNums == 0)
	{
		PRINTRIGHT(L"����������... ���� ������ ���°� �ϳ��� �����ʴϴ�. ���� ���� ���� �Ͻ���?");
	}
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
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"������� ���µ� �� �������Դϱ�?");
			goto INVALIDINPUT;
		}
		fixedDepositAndSavingsMenu();
		break;
	case 3:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"���� ��������? ����� ���� ���� ���弼��.");
			goto INVALIDINPUT;
		}
		transferMenu();
		break;
	case 4:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"���� �����Ҷ� 1�� �޴� �����ϼ���.");
			goto INVALIDINPUT;
		}
		atmMenu();
		break;
	case 5:
		if (g_userALNums == 0)
		{
			PRINTRIGHT(L"���� �����ϴ�. 1�� �޴��� ���ż� ����� ���¸��� ���弼��.");
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

	PRINTCEN(L"���»��� �޴�");
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



	PRINTLEFT(L"���� ���� �Է����ּ���.\n> ");
Invalidinput1:
	GET_G_INPUT;
	//Q_CHECK();

	AccountName_malloc = trim_malloc(AccountName_malloc, g_buffer);
	assert(AccountName_malloc != NULL && "trim is Something wrong...");

	if (strlen(AccountName_malloc) > 16 || strlen(AccountName_malloc) < 1)
	{
		PRINTRIGHT(L"�̸��� ���̴� 1�� ~ 16�� �Դϴ�. �ٽ� �Է����ּ���.\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (strlen(AccountName_malloc) == 1 && isdigit(*AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"�� ���ڷ� �����Ͻ÷��� ���ĺ����� �Է� ���ּ���...\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkAlnum(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"���¸��� ���ĺ� �⺻, ���� �������� �Է� ���ּ���..\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkDupAN(AccountName_malloc) == 1)
	{
		PRINTRIGHT(L"������ ������ �ߺ��Ǵ� ���¸��� �ֽ��ϴ�...\n> ");
		free(AccountName_malloc);
		AccountName_malloc = NULL;
		goto Invalidinput1;
	}
	else
	{
		PRINTLEFT(L"���¸��� ����� �Է��߽��ϴ�. \n");
		Sleep(1000);
		system("cls");
	}

	PRINTLEFT(L"���� ��й�ȣ�� �Է����ּ���. 4�ڸ� �����Դϴ�.\n> ");
Invalidinput2:
	GET_G_INPUT;

	PIN1 = trim_malloc(PIN1, g_buffer);
	assert(PIN1 != NULL && "trim is Something wrong...");

	if (checkDigit(PIN1) == 1)
	{
		PRINTRIGHT(L"���� ��й�ȣ�� 4�ڸ� \"����\"�Դϴ�..\n >");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}
	else if (checkDigit(PIN1) == 2)
	{
		PRINTRIGHT(L"���� ��й�ȣ�� ���̰����� ������� �ʽ��ϴ�.. �ٽ� �Է����ּ���.\n >");
		free(PIN1);
		PIN1 = NULL;
		goto Invalidinput2;
	}

	PRINTLEFT(L"���� ��й�ȣ�� �ٽ� �Է����ּ���. \n> ");
Invalidinput3:
	GET_G_INPUT;

	PIN2 = trim_malloc(PIN2, g_buffer);
	assert(PIN2 != NULL && "trim is Something wrong...");
	if (strncmp(PIN2, PIN1,4) != 0)
	{
		PRINTRIGHT(L"PassWords�� ���� ��ġ���� �ʽ��ϴ�.\n ");
		PRINTLEFT(L"PassWords �� �ٽ��ѹ� �Է��ϼ���. \n> ");
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



	temppath = (wchar_t*)malloc(sizeof(wchar_t) * ((strlen(ranNum)) + 1)); // �������� �����
	for (int j = 0; j < (strlen(ranNum)) + 1; j++)
	{
		mbtowc(temppath + j, ranNum + j, MB_CUR_MAX);
	}
	swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%d\\%s.txt", g_userBank, temppath);

	f_accFile = _wfopen(g_wpath, L"a+");
	assert(f_accFile != NULL && "create new account file failed");

	fseek(f_accFile, 0, SEEK_SET); //���������͸� ó����ġ�� �̵���Ű��
	fwrite(toTargetfile, sizeof(char), strlen(toTargetfile), f_accFile);

	fclose(f_accFile);
	f_accFile = NULL;

	fseek(f_AccountList, 0, SEEK_END);	//���¸���Ʈ ���Ͽ� ���� //���������͸� ���� ���� ������ �̵���Ű��
	fwrite(toListfile, sizeof(char), strlen(toListfile), f_AccountList); 
	fflush(f_AccountList);


	sprintf(toMemfile, "%s|", ranNum); //toMemfile�� ���¹�ȣ| ���ڿ� �Է�

	CurrentFileOffset = setBankByID(g_userID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(���� ������ + CurrentFileOffset) ��ġ�� ���������� �̵���
	while (fgetc(f_MemberFile) != '\n') //���پ� get�� �Ŷ�� �ǹ�
	{
		CurrentFileOffset++; //�ѱ��� �ѱ��ھ� �б� ����
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET); //(���� ������ + CurrentFileOffset) ��ġ�� ���������� �̵���
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
	
	// heap corruption�� free�� �� ����ϴ�. �ߴ������� ��ã�� ����
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


	printf("�����Ϸ�Ǿ����ϴ�.\n");

	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");	system("pause");

	return;
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
#if TEST_OFF
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //������
	int duration; //���� �Ⱓ(6�����̸� 6, 1���̸� 1, 2���̸� 2)
	float fixedDepositMoney = 0.0; //��ġ��(���Ծ�)
	float finalFixedDepositMoney = 0.0; //����������
	int selection;
	char accountName[10]; //���ݰ��¸�
	char* ptrAdd[30];
	int p = 0;
	inputFile = fopen("ioaccount.txt", "r"); //�ϴ� �׽�Ʈ�� ���Ϸ� �غ���

	system("cls");
	PRINTCEN(L"����� ���� ����");
	DRAWLINE('-');
	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	if (inputFile != NULL)
	{
		char buffer[256]; //���߿� �����ؾ���
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
		char buffer2[256]; //���߿� �����ؾ���
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
				printf("ptrAdd[%d]�� %s��\n", p, ptrAdd[p]);
				p++;

			}
			printf("ptrAdd[%d]�� %s��\n", p, ptrAdd[p]); 
		}
	}

	int moneySelection = 0;
	/*g_buffer�� �ش��ϴ� ���� ������ ����ݰ��¿��� ���*/

	if (atoi(g_buffer))
	{
		moneySelection = 2 + 5 * (atoi(g_buffer) - 1);
		printf("%d", moneySelection);
		printf("ptrAdd [%d] �� %d �Դϴ�", moneySelection, atoi(ptrAdd[moneySelection]));
		if (atoi(ptrAdd[moneySelection]) == 111111)
		{
			printf("hello");
		}
	}

	PRINTCEN(L"���¸� �Է�");
	DRAWLINE('-');
	printf("���� ���¸��� �Է����ּ���.\n");
	wprintf(L"> ");
	scanf("%s", &accountName);
	printf("���� ���¸��� %s�� �����Ǿ����ϴ�\n", accountName);
	system("pause");

	system("cls");
	PRINTCEN(L"������ ����");
	DRAWLINE('-');
	PRINTCEN(L"===������ ������ �������� �������ּ���===");
	PRINTLEFT(L"������  1) 6����(1.0%)   2) 1��(1.5%)   3) 2��(2.0%)");
	wprintf(L"> ");

	scanf_s("%d", &selection, 1);

	//printf�� �׳� Ȯ�ο��̶� �� ������. rate�� ���߿� �������� ù �ٿ� ����� ��
	switch (selection)
	{
	case 1:
		rate = 1.0;
		duration = 6;
		//printf("6���� ���ÿϷ�\n");
		break;

	case 2:
		rate = 1.5;
		duration = 1;
		//printf("1�� ���ÿϷ�\n");
		break;

	case 3:
		rate = 2.0;
		duration = 2;
		//printf("2�� ���ÿϷ�\n");
		break;
	}

	system("pause");
	system("cls");
	PRINTCEN(L"���Ծ� �Է�");
	DRAWLINE('-');

	PRINTCEN(L"===������ ������ ���Ծ�(��ġ��)�� �Է����ּ���===");
	PRINTLEFT(L"**Ȯ�λ���**");
	PRINTLEFT(L"���� : �� ���Ծ� �ѵ��� ��� 50�������� ������ �˴ϴ�.");
	PRINTLEFT(L"���� : ��ġ�� �ѵ��� ��� ���� ����ݰ��� �ܾ��Դϴ�.");
	PRINTLEFT(L"(���� : 1����)");
	wprintf(L"> ");

	scanf("%f", &fixedDepositMoney);

	//���� ���� �Ʊ� ������ ���� �ܾ׺��� ������ ������, 1�� �̻����� if�� �־�� ��!!

	printf("%.5f ������ ���ݰ��¿� ��ġ�Ǿ����ϴ�^v^\n", fixedDepositMoney);

	//������ɾ� ����ϱ�
	switch (selection)
	{
	case 1:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.01 * 0.5;
		printf("������ɾ��� %.5f���� �Դϴ�.\n", finalFixedDepositMoney);
		break;

	case 2:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.015;
		printf("������ɾ��� %.5f���� �Դϴ�.\n", finalFixedDepositMoney);
		break;

	case 3:
		finalFixedDepositMoney = fixedDepositMoney + fixedDepositMoney * 0.02 * 2;
		printf("������ɾ��� %.5f���� �Դϴ�.\n", finalFixedDepositMoney);
		break;
	}

	//���¹�ȣ ��������
	srand(time(NULL));
	char accountNum[8];

	//01�� ���࿡ ���� �ٲ����. ���߿� �������� ��Ʈ �Ͻô� ������ ���������� �ش޶�� ��������� ��

	accountNum[0] = '0';
	if (Bank != 0)
		accountNum[1] = atoi(Bank, accountNum, 10);
	accountNum[2] = '2';
	accountNum[7] = '\0';

	for (int k = 3; k < 7; k++)
	{
		accountNum[k] = rand() % 10 + 48;
	}

	printf("���� ���¹�ȣ�� %s�Դϴ�^v^\n", accountNum);

	int accountPassword = 1234; //����ݰ��¿��� �޾ƿ���

	system("pause");

	//������ �ٿ��� "�߰��� ��������" ��
	inputFile = fopen("fixed.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%f\n", accountName, accountNum, finalFixedDepositMoney, fixedDepositMoney);
	fclose(inputFile);

	//ù �ٿ��� "���¸�, ���¹�ȣ, �ش� ������ �ܾ�, ���� ��й�ȣ, ���� ��û�Ⱓ, ������, ���� �� ���ɾ��� ����"�� ��!
	//�ش� ���� �ܾ�, ���� ��й�ȣ�� ���� ���� ���ؼ� �װ� ���� �������� ù �ٿ� ��
	inputFile = fopen("fixed_shortcut.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%d|%d|%f|%f ", accountName, accountNum, fixedDepositMoney, accountPassword, duration, rate, finalFixedDepositMoney);
	fclose(inputFile);

	//Q_CHECK();
	//wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	//system("pause");
#endif
}

void Savings()
{
#if TEST_OFF
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //������
	int duration; //���� �Ⱓ(6�����̸� 6, 1���̸� 1, 2���̸� 2)
	float savingsDepositMoney = 0.0; //��ġ��(���Ծ�)
	int selection;
	char accountName[10]; //���ݰ��¸�

	inputFile = fopen("ioaccount.txt", "r"); //�ϴ� �׽�Ʈ�� ���Ϸ� �غ���

	system("cls");
	PRINTCEN(L"����� ���� ����");
	DRAWLINE('-');
	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	if (inputFile != NULL)
	{
		char buffer[256]; //���߿� �����ؾ���
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

	/*g_buffer�� �ش��ϴ� ���� ������ ����ݰ��¿��� ��� �� ���ݰ��� �����ؾ��ϴµ�
	���� ������ �ȵż� printf�� ��ü��*/
	if (atoi(g_buffer) == 1)
	{
		printf("1��������~~\n");
	}
	else
	{
		printf("�ٸ��� ������~~\n");
	}

	PRINTCEN(L"���¸� �Է�");
	DRAWLINE('-');
	printf("���� ���¸��� �Է����ּ���.\n");
	wprintf(L"> ");
	scanf("%s", &accountName);
	printf("���� ���¸��� %s�� �����Ǿ����ϴ�\n", accountName);
	system("pause");

	system("cls");
	PRINTCEN(L"������ ����");
	DRAWLINE('-');
	PRINTCEN(L"===������ ������ �������� �������ּ���===");
	PRINTLEFT(L"������  1) 6����(1.0%)   2) 1��(1.5%)   3) 2��(2.0%)");
	wprintf(L"> ");

	scanf_s("%d", &selection, 1);

	//printf�� �׳� Ȯ�ο��̶� �� ������. rate�� ���߿� �������� ù �ٿ� ����� ��
	//���߿� �������� ������ �����ϴ°� ���� �� ����
	switch (selection)
	{
	case 1:
		rate = 1.0;
		duration = 6;
		printf("6���� ���ÿϷ�\n");
		break;

	case 2:
		rate = 1.5;
		duration = 1;
		printf("1�� ���ÿϷ�\n");
		break;

	case 3:
		rate = 2.0;
		duration = 2;
		printf("2�� ���ÿϷ�\n");
		break;
	}

	system("pause");
	system("cls");
	PRINTCEN(L"���Ծ� �Է�");
	DRAWLINE('-');


	PRINTCEN(L"===������ ������ ���Ծ�(��ġ��)�� �Է����ּ���===");
	PRINTLEFT(L"**Ȯ�λ���**");
	PRINTLEFT(L"���� : �� ���Ծ� �ѵ��� ��� 50�������� ������ �˴ϴ�.");
	PRINTLEFT(L"���� : ��ġ�� �ѵ��� ��� ���� ����ݰ��� �ܾ��Դϴ�.");
	PRINTLEFT(L"(���� : 1����)");
	wprintf(L"> ");

	scanf("%f", &savingsDepositMoney);

	//���� ���� �Ʊ� ������ ���� �ܾ׺��� ������ ������, 1�� �̻����� if�� �־�� ��!!
	printf("%.5f ������ ���ݰ��¿� ���ԵǾ����ϴ�^v^\n", savingsDepositMoney);


	//���¹�ȣ ��������
	char accountNum[8];

	//01�� ���࿡ ���� �ٲ����. ���߿� �������� ��Ʈ �Ͻô� ������ ���������� �ش޶�� ��������� ��

	accountNum[0] = '0';
	accountNum[1] = '1';
	accountNum[2] = '3';
	accountNum[7] = '\0';

	for (int k = 3; k < 7; k++)
	{
		accountNum[k] = rand() % 10 + 48;
	}

	printf("���� ���¹�ȣ�� %s�Դϴ�^v^\n", accountNum);

	int accountPassword = 1234; //����ݰ��¿��� �޾ƿ���

	inputFile = fopen("savings_shortcut.txt", "a");
	fprintf(inputFile, "%s|%s|%f|%d|%d|%f ", accountName, accountNum, savingsDepositMoney, accountPassword, duration, rate);
	fclose(inputFile);

	system("pause");
	//�׸��� �������� ù �ٿ� "�ش� ������ �ܾ�, ���� ��й�ȣ, ���� ��û�Ⱓ, ������, ���� �� ���ɾ��� ����"�� ��!
	//�ش� ���� �ܾ�, ���� ��й�ȣ�� ���� ���� ���ؼ� �װ� ���� �������� ù �ٿ� ��


	//Q_CHECK();
	//wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	//system("pause");
#endif
}

void inquiryAndCancel() //Cancel �� �ϱ�~~~
{
	FILE* inputFile = NULL;

	/*
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
	//�ȳ�
	*/

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
	else if (*g_buffer == 'n' || *g_buffer == 'N')
	{
		wprintf(L"�ش� ������ ���¸� �������� �ʾҽ��ϴ�. ");
		system("pause");
	}
	else
	{
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
	PRINTCEN(L"���� Ȯ�� �޴�");
	DRAWLINE('-');

#if TEST_ON 
	PRINTRIGHT(L"��ȸ�ϰ��� �ϴ� ���¹�ȣ�� �Է����ּ���\n>");
INVALIDINPUT:
	GET_G_INPUT;
	Q_CHECK();

	//���¹�ȣ �м�
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
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ� ����� �ƴմϴ�. �ٽ� �Է����ּ���.\n>");
		goto INVALIDINPUT;
	}

	// �ش� ����ã�ư���
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
	switch (getAccType(i_AccNum)) // Ÿ��üũ
	{
	case T1: // ������� ���¸���
		type = T1;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", tempwcp[1], tempwcp);
		break;
	case T2: // ������ �ϳ�
		type = T2;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0], tempwcp[1], tempwcp[2]);
		break;
	case T3: // ���ݵ� �ϳ�
		type = T3;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0], tempwcp[1], tempwcp[2]);
		break;
	default:
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n >");
		goto INVALIDINPUT;
	}
	free(tempwcp);
	tempwcp = NULL;

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL) // ���� �̸� ������ �ٽ�
	{
		PRINTRIGHT(L"���¹�ȣ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���...\n> " );
		goto INVALIDINPUT;
	}

	for (int i = 0; i < g_userALNums; i++) //����� ���� �������� Ȯ��
	{
		if (strncmp(i_AccNum, g_userAccountsList[i], 7) == 0)
		{
			userHaveFlag = 1;
			break;
		}
	}
	if (userHaveFlag == 0)
	{
		PRINTRIGHT(L"���¹�ȣ�� ã�� �� �����ϴ�. Ȥ�� �ٸ� ��� ���¹�ȣ�� �ƴұ��?\n>");
		goto INVALIDINPUT;
	}
	//��� �׽�Ʈ
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
			if (CurrentFileOffset != -1) // ù���� ���� �Ӽ�
			{
				ia = (IOattributes_malloc_t*)malloc(sizeof(IOattributes_malloc_t));
				strToIOatt_malloc(g_buffer, ia);
				printIOatt(ia);
				freeIOattriutes(ia);
				free(ia);
				ia = NULL;
				accCounter++;
			}
			else // �ι��� ���� ���� ����
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
			if (CurrentFileOffset == 0) // ù���� ���� �Ӽ�
			{
				fsa = (FSattributes_t*)malloc(sizeof(FSattributes_t));
				if (strToFSatt(g_buffer, fsa, i_AccNum)== 1)  // ������ ���� ���� �ȿ� �ش� ���°� �ִ��� Ȯ��
				{
					printFSatt(fsa);
					accCounter++;
				}				
				free(fsa);
				fsa = NULL;
			}
			else // �ι��� ���� ���� ����
			{
				if (accCounter != 0)
				{
					fsi = (FSinqury_t*)malloc(sizeof(FSinqury_t));
					if (strToFSiq(g_buffer, fsi, i_AccNum) == 1) // ������ ���� ���� �ȿ� �ش� ���°� �ִ��� Ȯ��
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

		CurrentFileOffset = ftell(f_Account); //������
	}
	if (accCounter == 0)
	{
		PRINTRIGHT(L"�ش� ���´� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���...\n> ");
		goto INVALIDINPUT;
	}

	fclose(f_Account);
	f_Account = NULL;
#endif
	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����. \n");
	system("pause");

	return;
}
