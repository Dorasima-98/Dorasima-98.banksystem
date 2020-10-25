#include "userfunc.h"

static int con_flag = 1;
static int Bank = 0;	

int startMenu()
{
	con_flag = 1;
	int selection;
REPRINT:
	system("cls");
	PRINTCEN(L"로그인 메뉴");
	DRAWLINE('-');
	PRINTLEFT(L"1) 로그인	2) 계정생성	3) 프로그램 종료");
INVALIDINPUT:
	PRINTLEFT(L"주어진 메뉴의 번호를 선택해주세요.");
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

	//사용자 이름
Invalidinput1:
	printf("사용자 이름을 입력해주세요> \n");
	scanf_s("%s", Name, sizeof(Name));
	while (getchar() != '\n');
	/*GET_G_INPUT;	입력이 없는것을 체크, 나중에 수정
	Q_CHECK;		:Q 나가는거 체크*/
	EraseSpace(Name);
	for (int i = 0; ; i++) {
		if (Name[i] == NULL) {
			if (0 < i && i <= 40) {
				printf("아이디를 제대로 입력했습니다, 은행을 선택합니다\n");
				Sleep(3000);
				system("cls");
				break;
			}
			else {
				printf(L"이름의길이가 초과됐습니다, 이름을 다시 입력해주세요\n");
				goto Invalidinput1;
			}
		}
	}

	//은행
Invalidinput2:
	DRAWLINE('-');
	printf("건은행-1  국은행-2  대은행-3  학은행-4  교은행-5\n");
	DRAWLINE('-');
	printf("은행을 선택해주세요> ");
	scanf_s("%d", &Bank, sizeof(Bank));	//이렇게하면 스페이스바만 처리할수있음
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	if (1 <= Bank && Bank <= 5) {
		printf("은행이 선택되었습니다\n");
		Sleep(3000);
		system("cls");
	}
	else {
		printf("은행을 다시 입력해주세요\n");
		goto Invalidinput2;
	}

	//아이디
Invalidinput3:
	printf("아이디> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	for (int i = 0; i < strlen(Id); i++) {
		if (isalnum(Id[i]) != NULL) 			//영문자 또는 숫자이면 0아닌 값 반환
			continue;
		else {
			printf("잘못된 입력이 들어왔습니다, 다시 입력해주세요\n");
			goto Invalidinput3;
		}

		if (Id[i] == NULL) {
			printf("아이디 입력이 완료됐습니다\n");
			printf("비밀번호를 입력합니다\n");
			Sleep(3000);
			system("cls");
			break;
		}
	}

	//비밀번호
	do {
		printf("비밀번호> ");
		/*GET_G_INPUT;
		Q_CHECK;*/
		scanf_s("%s", password1, sizeof(password1));
		while (getchar() != '\n');
		EraseSpace(password1);
		printf("비밀번호 확인> ");
		EraseSpace(password2);
		while (getchar() != '\n');

		if (strcmp(password1, password2) == 0)		//일단 여기만 오류 -> 나주엥 수정
			pass = 0;
		else
			pass++;

		if (pass > 0) {
			printf("비밀번호를 다르게 입력했습니다, 다시 입력해주세요\n");
			pass = 0;		//pass 값 다시 초기화
			passcount++;	//입력횟수 - 5번 넘어가면 안됨
		}
		else if (pass == 0)
			printf("비밀번호를 제대로 입력했습니다\n");

		if (passcount == 5) {
			printf("비밀번호 입력횟수 5회초과\n");
			printf("프로그램 종료\n");
			Sleep(3000);
			system("cls");
			exit(0); //정상적인 종료 0, 비정상적인 종료 1
		}
	} while (passcount < 5);

	//이제 파일에 어떻게 입력할건가?
}

//이제 파일을 어떻게 불러올것인가?
int loginMenu() {

	char Id[100];
	char password1[100];
	char password2[100];
	char buffer[200];

	FILE* fp = fopen("12345.txt", "r");
	fgets(buffer, sizeof(buffer), fp);

	printf("아이디> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	//strcmp(Id, buffer); 그렇다면 어떻게 아이디, 비밀번호만 분류할것인가



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
	*p_dest = 0;	//맨 마지막에 null 저장
}