#include "userfunc.h"

static int con_flag = 1;
static int Bank = 0;	

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


void registerMenu() {

	char Name[100];
	char Id[100];
	char password1[100];
	char password2[100];
	int pass = 0;
	int passcount = 0;

	//����� �̸�
Invalidinput1:
	printf("����� �̸��� �Է����ּ���> \n");
	scanf_s("%s", Name, sizeof(Name));
	while (getchar() != '\n');
	/*GET_G_INPUT;	�Է��� ���°��� üũ, ���߿� ����
	Q_CHECK;		:Q �����°� üũ*/
	EraseSpace(Name);
	for (int i = 0; ; i++) {
		if (Name[i] == NULL) {
			if (0 < i && i <= 40) {
				printf("���̵� ����� �Է��߽��ϴ�, ������ �����մϴ�\n");
				Sleep(3000);
				system("cls");
				break;
			}
			else {
				printf(L"�̸��Ǳ��̰� �ʰ��ƽ��ϴ�, �̸��� �ٽ� �Է����ּ���\n");
				goto Invalidinput1;
			}
		}
	}

	//����
Invalidinput2:
	DRAWLINE('-');
	printf("������-1  ������-2  ������-3  ������-4  ������-5\n");
	DRAWLINE('-');
	printf("������ �������ּ���> ");
	scanf_s("%d", &Bank, sizeof(Bank));	//�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	if (1 <= Bank && Bank <= 5) {
		printf("������ ���õǾ����ϴ�\n");
		Sleep(3000);
		system("cls");
	}
	else {
		printf("������ �ٽ� �Է����ּ���\n");
		goto Invalidinput2;
	}

	//���̵�
Invalidinput3:
	printf("���̵�> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	for (int i = 0; i < strlen(Id); i++) {
		if (isalnum(Id[i]) != NULL) 			//������ �Ǵ� �����̸� 0�ƴ� �� ��ȯ
			continue;
		else {
			printf("�߸��� �Է��� ���Խ��ϴ�, �ٽ� �Է����ּ���\n");
			goto Invalidinput3;
		}

		if (Id[i] == NULL) {
			printf("���̵� �Է��� �Ϸ�ƽ��ϴ�\n");
			printf("��й�ȣ�� �Է��մϴ�\n");
			Sleep(3000);
			system("cls");
			break;
		}
	}

	//��й�ȣ
	do {
		printf("��й�ȣ> ");
		/*GET_G_INPUT;
		Q_CHECK;*/
		scanf_s("%s", password1, sizeof(password1));
		while (getchar() != '\n');
		EraseSpace(password1);
		printf("��й�ȣ Ȯ��> ");
		EraseSpace(password2);
		while (getchar() != '\n');

		if (strcmp(password1, password2) == 0)		//�ϴ� ���⸸ ���� -> ���ֿ� ����
			pass = 0;
		else
			pass++;

		if (pass > 0) {
			printf("��й�ȣ�� �ٸ��� �Է��߽��ϴ�, �ٽ� �Է����ּ���\n");
			pass = 0;		//pass �� �ٽ� �ʱ�ȭ
			passcount++;	//�Է�Ƚ�� - 5�� �Ѿ�� �ȵ�
		}
		else if (pass == 0)
			printf("��й�ȣ�� ����� �Է��߽��ϴ�\n");

		if (passcount == 5) {
			printf("��й�ȣ �Է�Ƚ�� 5ȸ�ʰ�\n");
			printf("���α׷� ����\n");
			Sleep(3000);
			system("cls");
			exit(0); //�������� ���� 0, ���������� ���� 1
		}
	} while (passcount < 5);

	//���� ���Ͽ� ��� �Է��Ұǰ�?
}

//���� ������ ��� �ҷ��ð��ΰ�?
int loginMenu() {

	char Id[100];
	char password1[100];
	char password2[100];
	char buffer[200];

	FILE* fp = fopen("12345.txt", "r");
	fgets(buffer, sizeof(buffer), fp);

	printf("���̵�> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	//strcmp(Id, buffer); �׷��ٸ� ��� ���̵�, ��й�ȣ�� �з��Ұ��ΰ�



	return 0;
}


void EraseSpace(char* ap_string)
{
	char* p_dest = ap_string;

	while (*ap_string != 0) {
		if (*ap_string != ' ') {
			*p_dest = *ap_string;
			p_dest++;
		}

		ap_string++;
	}
	*p_dest = 0;	//�� �������� null ����
}