
#include "userfunc.h"
#include <time.h>

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
	//���� �б�
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
	//�ϴ� �׽�Ʈ�� ���Ϸ� �غ���

	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	if (fp1 != NULL) {
		char buffer[256];
		while (!feof(fp1)) {
			fgets(buffer, sizeof(buffer), fp1);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			while (ptr != NULL) {
				printf("%s\n", ptr); //�� ���� Ȯ�ο�(���߿� ������ ��)
				ptr = strtok(NULL, "\n");
			}
		}
	}
	fclose(fp1);
	//����� ���¼���
	printf("����� ���¸� �����ϼ���.\n");
	scanf("%s", &selectIO);
	
	printf("���� ���¸��� �Է����ּ���.\n");
	scanf("%s", accountName);

	//������ ����
	DRAWLINE('-');
	PRINTLEFT(L"===���� ������ �������� �������ּ���===");
	PRINTLEFT(L"������  1) 6����(1.0%)   2) 1��(1.5%)   3) 2��(2.0%)");
	wprintf(L"> ");
	scanf("%d", &selectDay);
	//���Ծ� ����
	printf("���Ծ��� �����ϼ���.\n");
	scanf("%f", &NapMoney);
	//���� ���ɾ� ���
	if (selectDay == 1) {
		resultMon = NapMoney + NapMoney * 0.01 *0.5;
	}
	else if (selectDay == 2) {
		resultMon = NapMoney + NapMoney * 0.015;
	}
	else if (selectDay == 3) {
		resultMon = NapMoney + NapMoney* 0.02 * 2;
	}
	//���¹�ȣ ��������
	srand(time(NULL));
	int accountnum = rand() % 99999;

	fp2 = fopen("test.txt", "a");
	fprintf(fp2, "��¥|%s|%05d|%f|0 \n", accountName, accountnum, resultMon );
	fclose(fp2);

}



void Savings()
{
	system("cls");
	PRINTCEN(L" ���� ��û");
	DRAWLINE('-');
	//���� �б�
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
	//�ϴ� �׽�Ʈ�� ���Ϸ� �غ���

	PRINTCEN(L"=== ���� �ݾ� ������ ������ ����� ���� ��� ===");

	if (fp1 != NULL) {
		char buffer[256];
		while (!feof(fp1)) {
			fgets(buffer, sizeof(buffer), fp1);
			printf("%d)", lineCount++);
			char* ptr = strtok(buffer, "\n");
			while (ptr != NULL) {
				printf("%s\n", ptr); //�� ���� Ȯ�ο�(���߿� ������ ��)
				ptr = strtok(NULL, "\n");
			}
		}
	}
	fclose(fp1);
	//����� ���¼���
	printf("����� ���¸� �����ϼ���.\n");
	scanf("%s", &selectIO);

	printf("���� ���¸��� �Է����ּ���.\n");
	scanf("%s", accountName);

	//������ ����
	DRAWLINE('-');
	PRINTLEFT(L"===���� ������ �������� �������ּ���===");
	PRINTLEFT(L"������  1) 6����(1.0%)   2) 1��(1.5%)   3) 2��(2.0%)");
	wprintf(L"> ");
	scanf("%d", &selectDay);
	//���Ծ� ����
	printf("���Ծ��� �����ϼ���.\n");
	scanf("%f", &NapMoney);
	//���� ���ɾ� ���
	if (selectDay == 1) {
		resultMon = 6 * (NapMoney + NapMoney * 0.01 * 0.5);
	}
	else if (selectDay == 2) {
		resultMon = 12 * (NapMoney + NapMoney * 0.015);
	}
	else if (selectDay == 3) {
		resultMon = 24 * (NapMoney + NapMoney * 0.02 * 2);
	}
	//���¹�ȣ ��������
	srand(time(NULL));
	int accountnum = rand() % 99999;

	fp2 = fopen("test1.txt", "a");
	fprintf(fp2, "��¥|%s|%05d|%f|0 \n", accountName, accountnum, resultMon);
	fclose(fp2);

}
