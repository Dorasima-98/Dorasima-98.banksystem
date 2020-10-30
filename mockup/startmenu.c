#include "userfunc.h"

//#define MAX 1000
//#define MAX_STR_LEN 4000
static int con_flag = 1;
extern int Bank;
int g_allALANNums;

int startMenu()
{
	con_flag = 1;
	int selection;
REPRINT:
	system("cls");
	PRINTCEN(L"로그인 메뉴");
	DRAWLINE('-');
	PRINTLEFT(L"1) 로그인 (o)	2) 계정생성 (o) 3) 프로그램 종료 (o)");
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

	char* Name_malloc = NULL;
	int bank;
	char* ID_malloc = NULL;
	char* PW1_malloc = NULL;
	char* PW2_malloc = NULL;

	size_t memberInfoSize = 0;
	char* memberInfo = NULL;

	char* piter = NULL;
	char* pFileOffset = NULL;
	long CurrentFileOffset = 0;

	system("cls");
Invalidinput1:
	PRINTLEFT(L"사용자 이름을 입력해주세요...\n> ");
	GET_G_INPUT;
	//Q_CHECK();
	
	Name_malloc = trim_malloc(Name_malloc,g_buffer);
	assert(Name_malloc != NULL && "trim is Something wrong...");

	if (strlen(Name_malloc) > 16 || strlen(Name_malloc) < 1)
	{
		PRINTRIGHT(L"이름의 길이는 1자 ~ 16자 입니다. 다시 입력해주세요.\n");
		free(Name_malloc);
		Name_malloc = NULL;
		goto Invalidinput1;
	}
	else if (checkName(Name_malloc)==1)
	{
		PRINTRIGHT(L"이름은 알파벳으로 만 입력 해주세요..\n");
		free(Name_malloc);
		Name_malloc = NULL;
		goto Invalidinput1;
	}
	else
	{
		PRINTLEFT(L"이름을 제대로 입력했습니다, 은행을 선택합니다\n");
		Sleep(1000);
		system("cls");
	}

	//은행
Invalidinput2:
	//DRAWLINE('-');
	PRINTLEFT(L"건은행-1  국은행-2  대은행-3  학은행-4  교은행-5\n");
	//DRAWLINE('-');
	PRINTLEFT(L"은행을 선택해주세요.. \n> ");
	if (scanf("%d", &bank) != 1)  //이렇게하면 스페이스바만 처리할수있음
	{
		while (getchar() != '\n');
		PRINTRIGHT(L"은행을 다시 입력해주세요\n");
		goto Invalidinput2;

	}
	if (1 <= bank && bank <= 5) {
		PRINTLEFT(L"은행이 선택되었습니다\n");
		while (getchar() != '\n');
		Sleep(1000);
		system("cls");
	}
	else {
		PRINTRIGHT(L"은행을 다시 선택해주세요.\n");
		while (getchar() != '\n');
		goto Invalidinput2;
	}

	//아이디, 중간에 공백 허용x, 앞뒤 공백허용
Invalidinput3:
	PRINTLEFT(L"아이디를 입력하세요 \n> ");
	GET_G_INPUT;
	//Q_CHECK();

	ID_malloc = trim_malloc(ID_malloc, g_buffer);
	assert(ID_malloc != NULL && "trim is Something wrong...");

	if (strlen(ID_malloc) > 16 || strlen(ID_malloc) < 8)
	{
		PRINTRIGHT(L"ID의 길이는 8~ 16자 입니다. 다시 입력해주세요.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else if (checkSpace(ID_malloc) == 1)
	{
		PRINTRIGHT(L"ID 사이에 공백은 허용되지 않습니다.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else if (checkID(ID_malloc) == 1)
	{
		PRINTRIGHT(L"ID는 알파벳과 숫자의 조합으로 입력해주세요.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else if (checkDupID(ID_malloc) == 1)
	{
		PRINTRIGHT(L"중복되는 아이디가 있습니다. 다른 아이디를 입력해주세요.\n");
		free(ID_malloc);
		ID_malloc = NULL;
		goto Invalidinput3;
	}
	else 
	{
		PRINTLEFT(L"ID을 제대로 입력했습니다\n");
		Sleep(1000);
	}

	//비밀번호, 중간에 공백 허용x, 특수문자 허용, 앞뒤 공백 허용
Invalidinput4:
	PRINTLEFT(L"비밀번호를 입력하세요. \n> ");
	GET_G_INPUT;
	//Q_CHECK();

	PW1_malloc = trim_malloc(PW1_malloc, g_buffer);
	assert(PW1_malloc != NULL && "trim is Something wrong...");
	
	if (strlen(PW1_malloc) > 32 || strlen(PW1_malloc) < 8)
	{
		PRINTRIGHT(L"PassWords의 길이는 8자 ~ 32자 입니다. 다시 입력해주세요.\n");
		free(PW1_malloc);
		PW1_malloc = NULL;
		goto Invalidinput4;
	}
	else if (checkSpace(PW1_malloc) == 1)
	{
		PRINTRIGHT(L"PassWords 사이에 공백은 허용되지 않습니다.\n");
		free(PW1_malloc);
		PW1_malloc = NULL;
		goto Invalidinput4;
	}
	else if (checkPW(PW1_malloc) == 1)
	{
		PRINTRIGHT(L"PassWords 는 영문자, 숫자, 특수문자의 조합으로 입력해주세요.\n");
		free(PW1_malloc);
		PW1_malloc = NULL;
		goto Invalidinput4;
	}
	else
	{
		PRINTLEFT(L"PassWords 를 다시한번 입력하세요. \n> ");
	}
Invalidinput5:
	GET_G_INPUT;
	//Q_CHECK();

	PW2_malloc = trim_malloc(PW2_malloc, g_buffer);
	assert(PW2_malloc != NULL && "trim is Something wrong...");
	
	if (strcmp(PW2_malloc, PW1_malloc) != 0)
	{
		PRINTRIGHT(L"PassWords가 서로 일치하지 않습니다.\n ");
		PRINTLEFT(L"PassWords 를 다시한번 입력하세요. \n> ");
		free(PW2_malloc);
		PW2_malloc = NULL;
		goto Invalidinput5;
	}

	fseek(f_MemberFile, CurrentFileOffset, SEEK_END);
	// 짜증나게 자꾸 앞에 공백하나가 생겨가지고....ㅡ.ㅡ
	while (fgetc(f_MemberFile) != '\n')
	{
		CurrentFileOffset--;
		fseek(f_MemberFile, CurrentFileOffset-1, SEEK_END);
	}
	fseek(f_MemberFile, CurrentFileOffset, SEEK_END);
	memberInfoSize = strlen(Name_malloc) + strlen(ID_malloc) + strlen(PW1_malloc) + 8;
	memberInfo = (char*)malloc(sizeof(char) * memberInfoSize);
	assert(memberInfo != NULL && "memberInfo allcation failed");
	sprintf(memberInfo,"%s|%s|%s|0%d|\n", Name_malloc, ID_malloc, PW1_malloc, bank);
	fwrite(memberInfo, sizeof(char), memberInfoSize, f_MemberFile);
	// 이제 잘 됩니다.

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
	char* userInput = NULL;
	int IDresult = 0;
	int PWresult = 0;
	int trial = 5;
	int equalIDnPW = 0;

	while (trial != 0)
	{
		PRINTLEFT(L"아이디를 입력하시오.\n> ");
		GET_G_INPUT;
		//Q_CHECK();

		userInput = trim_malloc(userInput, g_buffer);
		assert(userInput != NULL && "trim is Something wrong...");

		IDresult = checkDupID(userInput);

		setAccListByID_malloc(userInput); // 아이디 비번 틀려서 다시 호출되면 내부적으로 free(g_userAccountList) 합니다.
		strncpy(g_userID, userInput, strlen(userInput)+1);

		free(userInput);
		userInput = NULL;

		Sleep(500);

		PRINTLEFT(L"비밀번호를 입력하시오.\n>");
		GET_G_INPUT;
		//Q_CHECK();

		userInput = trim_malloc(userInput, g_buffer);
		assert(userInput != NULL && "trim is Something wrong...");

		PWresult = checkDupPW(g_userID,userInput);

		free(userInput);
		userInput = NULL;

		if (IDresult && PWresult)
		{
			PRINTLEFT(L"로그인 성공!!!");
			Sleep(1000);
			return 1;
		}
		else
		{
			PRINTRIGHT(L"둘 중 뭐가 틀렸는지도 안 알려줄겁니다.");

			trial--;
		}
	}
	PRINTRIGHT(L"5번 틀렸습니다... 좀 쉬었다가 오세요.");
	return 0;
}


