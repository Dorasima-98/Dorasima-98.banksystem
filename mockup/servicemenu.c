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
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //������
	int duration; //���� �Ⱓ(6�����̸� 6, 1���̸� 1, 2���̸� 2)
	float fixedDepositMoney = 0.0; //��ġ��(���Ծ�)
	float finalFixedDepositMoney = 0.0; //����������
	int selection;
	char accountName[10]; //���ݰ��¸�

	inputFile = fopen("ioaccount.txt", "r"); //�ϴ� �׽�Ʈ�� ���Ϸ� �غ���

	system("cls");
	PRINTCEN(L"����� ���� ����");
	DRAWLINE('-');
	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	if (inputFile != NULL) {
		char buffer[256]; //���߿� �����ؾ���
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

	/*g_buffer�� �ش��ϴ� ���� ������ ����ݰ��¿��� ��� �� ���ݰ��� �����ؾ��ϴµ�
	���� ������ �ȵż� printf�� ��ü��*/
	if (atoi(g_buffer) == 1) {
		printf("1��������~~\n");
	}
	else {
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
	switch (selection) {
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
	
	scanf("%f", &fixedDepositMoney);

	//���� ���� �Ʊ� ������ ���� �ܾ׺��� ������ ������, 1�� �̻����� if�� �־�� ��!!
	if (fixedDepositMoney < 1 || fixedDepositMoney > 1000) {
		printf("�����ѵ����� �Ѱ���ϴ�. ó������ �ٽ� �ϼ���~~"); 
		//�̰͵� �ٽ� �Է¹޴°ɷ� �ٲٱ�
	}
	else {
		printf("%.5f ������ ���ݰ��¿� ��ġ�Ǿ����ϴ�^v^\n", fixedDepositMoney);
	}

	//������ɾ� ����ϱ�
	switch (selection) {
		case 1:
			finalFixedDepositMoney = fixedDepositMoney+fixedDepositMoney*0.01*0.5;
			printf("������ɾ��� %.5f���� �Դϴ�.\n", fixedDepositMoney);
			break;

		case 2:
			finalFixedDepositMoney = fixedDepositMoney+fixedDepositMoney*0.015;
			printf("������ɾ��� %.5f���� �Դϴ�.\n", fixedDepositMoney);
			break;

		case 3:
			finalFixedDepositMoney = fixedDepositMoney+fixedDepositMoney*0.02*2;
			printf("������ɾ��� %.5f���� �Դϴ�.\n", fixedDepositMoney);
			break;
	}

	//���¹�ȣ ��������
	srand(time(NULL));
	char accountNum[8];

	//01�� ���࿡ ���� �ٲ����. ���߿� �������� ��Ʈ �Ͻô� ������ ���������� �ش޶�� ��������� ��

	accountNum[0] = '0';
	accountNum[1] = '1';
	accountNum[2] = '2';
	accountNum[7] = '\0';

	for (int k = 3; k < 7; k++) {
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
	//inputFile = fopen("fixed.txt", "r+");
	//fprintf(inputFile, " %s|%s|%f|%d|%d|%f|%f", accountName, accountNum, fixedDepositMoney, accountPassword, duration, rate, finalFixedDepositMoney);
	//fclose(inputFile);
	
	//���������� �ٽ� ���� ���������� �ű��

	//Q_CHECK();
	//wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	//system("pause");
}

void Savings()
{
	FILE* inputFile = NULL;

	int lineCount = 1;
	float rate = 0.0; //������
	int duration; //���� �Ⱓ(6�����̸� 6, 1���̸� 1, 2���̸� 2)
	float fixedDepositMoney = 0.0; //��ġ��(���Ծ�)
	int selection;
	char accountName[10]; //���ݰ��¸�

	inputFile = fopen("ioaccount.txt", "r"); //�ϴ� �׽�Ʈ�� ���Ϸ� �غ���

	system("cls");
	PRINTCEN(L"����� ���� ����");
	DRAWLINE('-');
	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	if (inputFile != NULL) {
		char buffer[256]; //���߿� �����ؾ���
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

	/*g_buffer�� �ش��ϴ� ���� ������ ����ݰ��¿��� ��� �� ���ݰ��� �����ؾ��ϴµ�
	���� ������ �ȵż� printf�� ��ü��*/
	if (atoi(g_buffer) == 1) {
		printf("1��������~~\n");
	}
	else {
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
	switch (selection) {
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

	scanf("%f", &fixedDepositMoney);

	//���� ���� �Ʊ� ������ ���� �ܾ׺��� ������ ������, 1�� �̻����� if�� �־�� ��!!
	if (fixedDepositMoney < 1 || fixedDepositMoney > 1000) {
		printf("�����ѵ����� �Ѱ���ϴ�. ó������ �ٽ� �ϼ���~~");
		//�̰͵� �ٽ� �Է¹޴°ɷ� �ٲٱ�
	}
	else {
		printf("%.5f ������ ���ݰ��¿� ���ԵǾ����ϴ�^v^\n", fixedDepositMoney);
	}

	//���¹�ȣ ��������
	srand(time(NULL));
	char accountNum[4];

	printf("���� ���¹�ȣ�� 013"); 	//01�� ���࿡ ���� �ٲ����. ���߿� �������� ��Ʈ �Ͻô� ������ ���������� �ش޶�� ��������� ��

	for (int k = 0; k < 4; k++) {
		accountNum[k] = rand() % 10 + 48;
		printf("%c", accountNum[k]);
	}
	printf("�Դϴ�^v^\n");

	system("pause");
	//�׸��� �������� ù �ٿ� "�ش� ������ �ܾ�, ���� ��й�ȣ, ���� ��û�Ⱓ, ������, ���� �� ���ɾ��� ����"�� ��!
	//�ش� ���� �ܾ�, ���� ��й�ȣ�� ���� ���� ���ؼ� �װ� ���� �������� ù �ٿ� ��
	//inputFile = fopen("fixed.txt", "a");
	//fprintf(inputFile, "%s|%d|%f|%f ", accountName, duration, rate, fixedDepositMoney);
	//fclose(inputFile);

	//Q_CHECK();
	//wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����.\n");
	//system("pause");
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

	system("cls");
	PRINTCEN(L"���� Ȯ�� �޴�");
	DRAWLINE('-');

#if TEST_ON 
	PRINTRIGHT(L"��ȸ�ϰ��� �ϴ� ���¹�ȣ�� �Է����ּ���");
	printf("> ");
INVALIDINPUT:
	GET_G_INPUT;
	Q_CHECK();

	//���¹�ȣ �м�
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
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ� ����� �ƴմϴ�. �ٽ� �Է����ּ���.");
		goto INVALIDINPUT;
	}

	// �ش� ����ã�ư���
	tempwcp = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(i_AccNum)+1));
	for (int i = 0; i < strlen(i_AccNum)+1; i++)
	{
		mbtowc(tempwcp+i,i_AccNum+i , MB_CUR_MAX);
	}
	switch (i_AccNum[2]) // Ÿ��üũ
	{
	case '1': // ������� ���¸���
		type = T1;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", tempwcp[1], tempwcp);
		break;
	case '2': // ������ �ϳ�
		type = T2;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0],tempwcp[1],tempwcp[2]);
		break;
	case'3': // ���ݵ� �ϴ� �ϳ�
		type = T3;
		swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", tempwcp[1], tempwcp[0], tempwcp[1], tempwcp[2]);
		break;
	default:
		PRINTRIGHT(L"���¹�ȣ�� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ���.");
		goto INVALIDINPUT;
	}
	free(tempwcp);
	tempwcp = NULL;

	f_Account = _wfopen(g_wpath, L"r");
	if (f_Account == NULL)
	{
		PRINTRIGHT(L"���¹�ȣ�� ã�� �� �����ϴ�. �ٽ� �Է����ּ���...");
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
		PRINTRIGHT(L"�ش� ���´� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���...");
		goto INVALIDINPUT;
	}
	
	fclose(f_Account);
	f_Account = NULL;
#endif
	wprintf(L"�ڷΰ��� Ŀ�ǵ� �Է� ����. \n");
	system("pause");

	return;
}
