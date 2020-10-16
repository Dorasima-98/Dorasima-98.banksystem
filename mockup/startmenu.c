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
void registerMenu()
{
	system("cls");
	PRINTCEN(L"계정생성 메뉴");
	DRAWLINE('-');

	PRINTLEFT(L"아이디를 입력하세요... (알파벳과 숫자의 조합으로 입력하세요. 8 ~ 16자리) (뒤로가기 \":q\")");
	GET_G_INPUT;
	Q_CHECK();

	PRINTLEFT(L"비밀번호를 입력하세요... (알파벳과 숫자 그리고 숫자키 특수문자의 조합으로 입력하세요[ !@#$%^&*() ]...  ) (뒤로가기 \":q\")");
	GET_G_INPUT;
	Q_CHECK();

	PRINTLEFT(L"다시한번 비밀번호를 입력하세요... ) (뒤로가기 \":q\")");
	GET_G_INPUT;
	Q_CHECK();

	wprintf(L"뒤로가기 커맨드 입력 안함.\n");
	system("pause");
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
