//#include "userfunc.h"
//
//#define MAX 1000
//#define MAX_STR_LEN 4000
//static int con_flag = 1;
//extern int Bank;
//
//int startMenu()
//{
//	con_flag = 1;
//	int selection;
//REPRINT:
//	system("cls");
//	PRINTCEN(L"�α��� �޴�");
//	DRAWLINE('-');
//	PRINTLEFT(L"1) �α���	2) ��������	3) ���α׷� ����");
//INVALIDINPUT:
//	PRINTLEFT(L"�־��� �޴��� ��ȣ�� �������ּ���.");
//	GET_G_INPUT;
//
//	selection = atoi(g_buffer);
//	switch (selection)
//	{
//	case 1:
//		if (loginMenu())
//		{
//			break;
//		}
//		else
//		{
//			goto REPRINT;
//		}
//	case 2:
//		registerMenu();
//		goto REPRINT;
//	case 3:
//		con_flag = 0;
//		break;
//	default:
//		goto INVALIDINPUT;
//	}
//	if (con_flag == 0)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}
//
//}
//
//
//
//void registerMenu() {
//
//	char Name[100];
//	char Id[100];
//	char* Name2;
//	char password1[100];
//	char password2[100];
//	int pass = 0;
//	int passcount = 0;
//
//	FILE* fp = fopen("HumanList.txt", "w");
//
//	if (fp == NULL) {
//		puts("���Ͽ��� ����");	//printf�� ����
//	}
//
//	//����� �̸�, �߰� ���鸸 ���, �յ� �� ¥����
//Invalidinput1:
//	system("cls");
//	printf("����� �̸��� �Է����ּ���> \n");
//	gets_s(Name, sizeof(Name));	//���鵵 �Է¹���
//	Name2 = trim(Name);
//	printf("%s\n", Name);
//	printf("%s\n", Name2);
//	/*GET_G_INPUT;	�Է��� ���°��� üũ, ���߿� ����
//	Q_CHECK;		:Q �����°� üũ*/
//	for (int i = 0; ; i++) {
//		if (*(Name2 + i) == NULL) {
//			if (0 < i && i <= 40) {
//				printf("�̸��� ����� �Է��߽��ϴ�, ������ �����մϴ�\n");	
//				Sleep(2000);
//				system("cls");
//				break;
//			}
//			else {
//				printf("�̸��Ǳ��̰� �ʰ��ƽ��ϴ�, �̸��� �ٽ� �Է����ּ���\n");
//				Sleep(2000);
//				goto Invalidinput1;
//			}
//		}
//	}
//
//	//����
//Invalidinput2:
//	//DRAWLINE('-');
//	printf("������-1  ������-2  ������-3  ������-4  ������-5\n");
//	//DRAWLINE('-');
//	printf("������ �������ּ���> ");
//	scanf("%d", &Bank);	//�̷����ϸ� �����̽��ٸ� ó���Ҽ�����
//	while (getchar() != '\n');
//	/*GET_G_INPUT;
//	Q_CHECK;*/
//	if (1 <= Bank && Bank <= 5) {
//		printf("������ ���õǾ����ϴ�\n");
//		Sleep(3000);
//		system("cls");
//	}
//	else {
//		printf("������ �ٽ� �Է����ּ���\n");
//		goto Invalidinput2;
//	}
//
//	//���̵�, �߰��� ���� ���x, �յ� �������
//Invalidinput3:
//	printf("���̵�> ");
//	scanf_s("%s", Id, sizeof(Id));
//	while (getchar() != '\n');
//	/*GET_G_INPUT;
//	Q_CHECK;*/
//	trim(Id);
//	for (int i = 0; i < strlen(Id); i++) {
//		if (isalnum(Id[i]) != NULL) {			//������ �Ǵ� �����̸� 0�ƴ� �� ��ȯ
//			if (Id[i] == NULL) {
//				printf("���̵� �Է��� �Ϸ�ƽ��ϴ�\n");
//				printf("��й�ȣ�� �Է��մϴ�\n");
//				Sleep(2000);
//				system("cls");
//				break;
//			}
//		}
//		else {
//			printf("�߸��� �Է��� ���Խ��ϴ�, �ٽ� �Է����ּ���\n");
//			goto Invalidinput3;
//		}
//	}
//
//	//��й�ȣ, �߰��� ���� ���x, Ư������ ���, �յ� ���� ���
//	do {
//		printf("��й�ȣ> ");
//		/*GET_G_INPUT;
//		Q_CHECK;*/
//		scanf_s("%s", password1, sizeof(password1));
//		while (getchar() != '\n');
//		trim(password1);
//		printf("��й�ȣ Ȯ��> ");
//		scanf_s("%s", password2, sizeof(password2));
//		trim(password2);
//		while (getchar() != '\n');
//
//		if (strcmp(password1, password2) == 0)		//�ϴ� ���⸸ ���� -> ���ֿ� ����
//			pass = 0;
//		else
//			pass++;
//
//		if (pass > 0) {
//			printf("��й�ȣ�� �ٸ��� �Է��߽��ϴ�, �ٽ� �Է����ּ���\n");
//			pass = 0;		//pass �� �ٽ� �ʱ�ȭ
//			passcount++;	//�Է�Ƚ�� - 5�� �Ѿ�� �ȵ�
//		}
//		else if (pass == 0) {
//			printf("��й�ȣ�� ����� �Է��߽��ϴ�\n");
//			break;
//		}
//
//		if (passcount == 5) {
//			printf("��й�ȣ �Է�Ƚ�� 5ȸ�ʰ�\n");
//			printf("���α׷� ����\n");
//			Sleep(2000);
//			system("cls");
//			exit(0);	//���α׷� ����
//		}
//	} while (passcount < 5);
//
//
//	fprintf(fp, "%s|%s|%s|", Name2, Id, password1);	//�̻��ϰ� Name2�� �Է��� �ȵ�, ���߿� ����
//	fclose(fp);
//}
//
//int loginMenu() {
//	
//	char Id[100];
//	char password[100];
//	char Idbuffer[100];
//	char passwordbuffer[100];
//	char* ptr;		//���Ͽ��� �о�� ���̵�, ��й�ȣ
//	int passcount = 0;	//��й�ȣ ���Է� Ƚ�� 5��
//	FILE* fp = fopen("HumanList.txt", "r");
//	
//	//���̵� �˻�
//RETURN1:
//	printf("���̵�> ");
//	scanf_s("%s", Id, sizeof(Id));
//	while (getchar() != '\n');
//	/*GET_G_INPUT;
//	Q_CHECK;*/
//	if (fp != NULL) { 
//		if(!feof(fp)) {
//			fgets(Idbuffer, sizeof(Idbuffer), fp);
//			ptr = strtok(Idbuffer, "|");
//			ptr = strtok(NULL, "|");	//ù��° ���̵��ȯ
//		}
//	}else
//		printf("���Ͽ� �Էµ� ����x");
//	
//	 if(strcmp(ptr, Id) != 0) {
//		printf("���� ������ �ȵ� ���̵��Դϴ�\n");
//		printf("�ٽ� �Է����ּ���\n");
//		goto RETURN1;
//	}
//	
//
//	//���̵� �Էµƴٸ� ��й�ȣ �˻�
//	if (strcmp(ptr, Id) == 0) {
//		printf("��й�ȣ> ");
//		scanf_s("%s", password, sizeof(password));
//		while (getchar() != '\n');
//		//GET_G_INPUT;
//		//Q_CHECK;
//		if (fp != NULL) {
//			if (!feof(fp)) {
//				ptr = strtok(NULL, "|");	//�ι��� ��й�ȣ ��ȯ
//			}
//		}
//		else
//			printf("���Ͽ� �Էµ� ����x");
//
//		do {
//			if (strcmp(ptr, password) == 0) {
//				printf("��й�ȣ ����� �Է��߽��ϴ�\n");
//			}else {
//				++passcount;
//				printf("��й�ȣ�� %d�� �� �Է��� �� �ֽ��ϴ�\n", 5-passcount);
//				if (passcount == 5) {
//					printf("��й�ȣ �Է°���Ƚ�� 5�� �ʰ�\n");
//					printf("���α׷��� �����մϴ�\n");
//					Sleep(2000);
//					exit(0);
//				}
//			}
//		} while (passcount < 5);
//	}
//
//	fclose(fp);
//	
//	return 0;
//}
//
////�߰� ���� �����
//void EraseSpace(char* ap_string)
//{
//	char* p_dest = ap_string;
//
//	while (*ap_string != 0) {
//		if (*ap_string != ' ') {
//			*p_dest = *ap_string;
//			p_dest++;
//		}
//
//		ap_string++;
//	}
//	*p_dest = 0;	//�� �������� null ����
//}
//
//
//// ���ڿ� ���� ���鹮�� ���� �Լ�
//char* rtrim(char* s) {
//	char t[MAX_STR_LEN];
//	char* end;
//
//	strcpy(t, s);
//	end = t + strlen(t) - 1;
//	while (end != t && isspace(*end))
//		end--;
//	*(end + 1) = '\0';
//	s = t;
//
//	return s;
//}
//
//
//// ���ڿ� ���� ���鹮�� ���� �Լ�
//char* ltrim(char* s) {
//	char* begin;
//	begin = s;
//
//	while (*begin != '\0') {
//		if (isspace(*begin))
//			begin++;
//		else {
//			s = begin;
//			break;
//		}
//	}
//
//	return s;
//}
//
//
//// ���ڿ� �յ� ���� ��� ���� �Լ�
//char* trim(char* s) {
//	return rtrim(ltrim(s));
//}