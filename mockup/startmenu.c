#include "userfunc.h"

static int con_flag = 1;

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

	//사용자 이름
Invalidinput1:
	PRINTLEFT(L"사용자 이름을 입력해주세요");
	wprintf(L">");
	scanf_s("%s", Name, sizoef(Name));
	/*GET_G_INPUT;	입력이 없는것을 체크, 나중에 수정
	Q_CHECK;		:Q 나가는거 체크*/
	EraseSpace(Name);
	for (int i = 0; ; i++) {
		if (Name[i] == NULL) {
			if (0 < i && i <= 40) {
				PRINTLEFT(L"아이디를 제대로 입력했습니다, 은행을 선택합니다");
				Sleep(5000);
				system("cls");
			}
			else {
				PRINTLEFT(L"이름의길이가 초과됐습니다, 이름을 다시 입력해주세요\n");
				goto Invalidinput1;
			}
		}
	}

	//은행
Invalidinput2:
	DRAWLINE('-');
	PRINTCEN(L"건은행-1  국은행-2  대은행-3  학은행-4  교은행-5");
	DRAWLINE('-');
	PRINTLEFT(L"은행을 선택해주세요");
	wprintf(L">");
	scanf_s("%d", &Bank, sizeof(Bank));	//이렇게하면 스페이스바만 처리할수있음
	/*GET_G_INPUT;
	Q_CHECK;*/
	if (1 <= Bank && Bank <= 5) {
		printf("은행이 선택되었습니다");
		Sleep(5000);
		system("cls");
	}
	else {
		PRINTLEFT(L"은행을 다시 입력해주세요");
		goto Invalidinput2;
	}

	//아이디
Invalidinput3:
	PRINTLEFT(L"아이디");
	wprintf(L">");
	scanf_s("%s", Id, sizeof(Id));
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	for (int i = 0; i < strlen(Id); i++) {
		if (isalnum(Id[i]) != NULL) 			//영문자 또는 숫자이면 0아닌 값 반환
			continue;
		else {
			PRINTLEFT(L"잘못된 입력이 들어왔습니다, 다시 입력해주세요");
			goto Invalidinput3;
		}

		if (Id[i] = NULL) {
			PRINTLEFT(L"아이디 입력이 됐습니다");
			PRINTLEFT(L"비밀번호를 입력합니다");
			Sleep(5000);
			system("cls");
			break;
		}
	}

	//비밀번호
	do {
		PRINTLEFT(L"비밀번호");
		wprintf(L">");
		/*GET_G_INPUT;
		Q_CHECK;*/
		scanf_s("%s", password1, sizeof(password1));
		EraseSpace(password1);
		PRINTLEFT(L"비밀번호 확인");
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
			PRINTLEFT(L"비밀번호를 다르게 입력했습니다, 다시 입력해주세요");
			passcount++;	//입력횟수 - 5번 넘어가면 안됨
		}
		else if (pass == 0)
			PRINTLEFT(L"비밀번호를 제대로 입력했습니다");

		if (passcount == 5) {
			PRINTLEFT(L"비밀번호 입력횟수 5회초과");
			PRINTLEFT(L"프로그램 종료");
			Sleep(5000);
			system("cls");
			exit(0); //정상적인 종료 0, 비정상적인 종료 1
		}
	} while (passcount < 5);

#endif
}

int loginMenu()
{
	system("cls");
	PRINTCEN(L"로그인 메뉴");
	DRAWLINE('-');

	PRINTLEFT(L"아이디를 입력하세요...(뒤로가기 \":q\")");
	GET_G_INPUT;
	Q_CHECK(0);

	PRINTLEFT(L"비밀번호를 입력하세요...(뒤로가기 \":q\")");
	GET_G_INPUT;
	Q_CHECK(0);

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
	return 1;
}
