#include "userfunc.h"

//#define MAX 1000
//#define MAX_STR_LEN 4000
static int con_flag = 1;
extern int Bank;

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

	char* Name_malloc = NULL;
	int bank;
	char* ID_malloc = NULL;
	char* PW1_malloc = NULL;
	char* PW2_malloc = NULL;

	int memberInfoSize = 0;
	char* memberInfo = NULL;

	char* piter = NULL;
	char* pFileOffset = NULL;
	long CurrentFileOffset = 0;

	system("cls");
Invalidinput1:
	PRINTLEFT(L"����� �̸��� �Է����ּ���...\n> ");
	GET_G_INPUT;
	//Q_CHECK();
	
	Name_malloc = trim_malloc(Name_malloc,g_buffer);
	assert(Name_malloc != NULL && "trim is Something wrong...");
	printf("%s %d\n", Name_malloc,strlen(Name_malloc));
	printf("%s\n", g_buffer);
	if (strlen(Name_malloc) > 16 || strlen(Name_malloc) < 1)
	{
		PRINTRIGHT(L"�̸��� ���̴� 1�� ~ 16�� �Դϴ�. �ٽ� �Է����ּ���.\n");
		free(Name_malloc);
		Name_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkName(Name_malloc)==1)
	{
		PRINTRIGHT(L"�̸��� ���ĺ����� �� �Է� ���ּ���..\n");
		free(Name_malloc);
		Name_malloc = NULL;
		goto Invalidinput1;
	}
	else
	{
		PRINTLEFT(L"�̸��� ����� �Է��߽��ϴ�, ������ �����մϴ�\n");
		Sleep(1000);
		system("cls");
	}

	//����
Invalidinput2:
	//DRAWLINE('-');
	PRINTLEFT(L"������-1  ������-2  ������-3  ������-4  ������-5\n");
	//DRAWLINE('-');
	PRINTLEFT(L"������ �������ּ���.. \n> ");
	if (scanf("%d", &bank) != 1)  //�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"������ �ٽ� �Է����ּ���\n");
		goto Invalidinput2;

	}
	if (1 <= bank && bank <= 5) {
		PRINTLEFT(L"������ ���õǾ����ϴ�\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else {
		PRINTRIGHT(L"������ �ٽ� �������ּ���.\n");
		while (getchar() != '\n');
		goto Invalidinput2;
	}

	//���̵�, �߰��� ���� ���x, �յ� �������
Invalidinput3:
	PRINTLEFT(L"���̵� �Է��ϼ��� \n> ");
	GET_G_INPUT;
	//Q_CHECK();

	ID_malloc = trim_malloc(ID_malloc, g_buffer);
	assert(ID_malloc != NULL && "trim is Something wrong...");
	printf("%s\n", ID_malloc);
	printf("%s\n", g_buffer);
	char* tempID = ID_malloc;
	if (strlen(ID_malloc) > 16 || strlen(ID_malloc) < 8)
	{
		PRINTRIGHT(L"ID�� ���̴� 8~ 16�� �Դϴ�. �ٽ� �Է����ּ���.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else if (checkSpace(ID_malloc) == 1)
	{
		PRINTRIGHT(L"ID ���̿� ������ ������ �ʽ��ϴ�.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else if (checkID(ID_malloc) == 1)
	{
		PRINTRIGHT(L"ID�� ���ĺ��� ������ �������� �Է����ּ���.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else if (checkDupID(ID_malloc) == 1)
	{
		PRINTRIGHT(L"�ߺ��Ǵ� ���̵� �ֽ��ϴ�. �ٸ� ���̵� �Է����ּ���.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else 
	{
		PRINTLEFT(L"ID�� ����� �Է��߽��ϴ�\n");
		Sleep(1000);
	}

	//��й�ȣ, �߰��� ���� ���x, Ư������ ���, �յ� ���� ���
Invalidinput4:
	PRINTLEFT(L"��й�ȣ�� �Է��ϼ���. \n> ");
	GET_G_INPUT;
	//Q_CHECK();

	PW1_malloc = trim_malloc(PW1_malloc, g_buffer);
	assert(PW1_malloc != NULL && "trim is Something wrong...");
	printf("%s\n", PW1_malloc);
	printf("%s\n", g_buffer);
	if (strlen(PW1_malloc) > 32 || strlen(PW1_malloc) < 8)
	{
		PRINTRIGHT(L"PassWords�� ���̴� 8�� ~ 32�� �Դϴ�. �ٽ� �Է����ּ���.\n");
		free(PW1_malloc);
		PW1_malloc = NULL;
		goto Invalidinput4;
	}
	else if (checkSpace(PW1_malloc) == 1)
	{
		PRINTRIGHT(L"PassWords ���̿� ������ ������ �ʽ��ϴ�.\n");
		free(PW1_malloc);
		PW1_malloc = NULL;
		goto Invalidinput4;
	}
	else if (checkPW(PW1_malloc) == 1)
	{
		PRINTRIGHT(L"PassWords �� ������, ����, Ư�������� �������� �Է����ּ���.\n");
		free(PW1_malloc);
		PW1_malloc = NULL;
		goto Invalidinput4;
	}
	else
	{
		PRINTLEFT(L"PassWords �� �ٽ��ѹ� �Է��ϼ���. \n> ");
	}
Invalidinput5:
	GET_G_INPUT;
	//Q_CHECK();

	PW2_malloc = trim_malloc(PW2_malloc, g_buffer);
	assert(PW2_malloc != NULL && "trim is Something wrong...");
	printf("%s\n", PW2_malloc);
	printf("%s\n", g_buffer);
	if (strcmp(PW2_malloc, PW1_malloc) != 0)
	{
		PRINTRIGHT(L"PassWords�� ���� ��ġ���� �ʽ��ϴ�.\n ");
		PRINTLEFT(L"PassWords �� �ٽ��ѹ� �Է��ϼ���. \n> ");
		free(PW2_malloc);
		PW2_malloc = NULL;
		goto Invalidinput5;
	}

	fseek(f_MemberFile, CurrentFileOffset-1, SEEK_END);
	while (fgetc(f_MemberFile) != '|')
	{
		CurrentFileOffset--;
		fseek(f_MemberFile, CurrentFileOffset - 1, SEEK_END);
	}
	fseek(f_MemberFile, CurrentFileOffset, SEEK_END);
	memberInfoSize = strlen(Name_malloc) + strlen(ID_malloc) + strlen(PW1_malloc) + 8;
	memberInfo = (char*)malloc(sizeof(char) * memberInfoSize);
	assert(memberInfo != NULL && "memberInfo allcation failed");
	sprintf(memberInfo,"\n%s|%s|%s|0%d|", Name_malloc, ID_malloc, PW1_malloc, bank);
	fwrite(memberInfo, sizeof(char), memberInfoSize, f_MemberFile);

	free(Name_malloc);
	free(ID_malloc);
	free(PW1_malloc);
	free(PW2_malloc);
	Name_malloc = NULL;
	ID_malloc = NULL;
	PW1_malloc = NULL;
	PW2_malloc = NULL;
}

int loginMenu() {
	
	char Id[100];
	char password[100];
	char Idbuffer[100];
	char passwordbuffer[100];
	char* ptr =NULL;		//���Ͽ��� �о�� ���̵�, ��й�ȣ
	int passcount = 0;	//��й�ȣ ���Է� Ƚ�� 5��
	FILE* fp = fopen("HumanList.txt", "r");
	
	//���̵� �˻�
RETURN1:
	printf("���̵�> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	if (fp != NULL) { 
		if(!feof(fp)) {
			fgets(Idbuffer, sizeof(Idbuffer), fp);
			ptr = strtok(Idbuffer, "|");
			ptr = strtok(NULL, "|");	//ù��° ���̵��ȯ
		}
	}
	else
	{
		printf("���Ͽ� �Էµ� ����x");
		return;
	}
		
	if (ptr == NULL)
	{
		return;
	}
	if(strcmp(ptr, Id) != 0) {
		printf("���� ������ �ȵ� ���̵��Դϴ�\n");
		printf("�ٽ� �Է����ּ���\n");
		goto RETURN1;
	}


	//���̵� �Էµƴٸ� ��й�ȣ �˻�
	if (strcmp(ptr, Id) == 0) {
		printf("��й�ȣ> ");
		scanf_s("%s", password, sizeof(password));
		while (getchar() != '\n');
		/*GET_G_INPUT;
		Q_CHECK;*/
		if (fp != NULL) {
			if (!feof(fp)) {
				ptr = strtok(NULL, "|");	//�ι��� ��й�ȣ ��ȯ
			}
		}
		else
			printf("���Ͽ� �Էµ� ����x");

		do {
			if (strcmp(ptr, password) == 0) {
				printf("��й�ȣ ����� �Է��߽��ϴ�\n");
			}else {
				++passcount;
				printf("��й�ȣ�� %d�� �� �Է��� �� �ֽ��ϴ�\n", 5-passcount);
				if (passcount == 5) {
					printf("��й�ȣ �Է°���Ƚ�� 5�� �ʰ�\n");
					printf("���α׷��� �����մϴ�\n");
					Sleep(1000);
					exit(0);
				}
			}
		} while (passcount < 5);
	}

	fclose(fp);
	
	return 0;
}


