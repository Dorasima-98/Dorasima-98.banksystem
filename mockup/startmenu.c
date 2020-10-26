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
//	PRINTCEN(L"로그인 메뉴");
//	DRAWLINE('-');
//	PRINTLEFT(L"1) 로그인	2) 계정생성	3) 프로그램 종료");
//INVALIDINPUT:
//	PRINTLEFT(L"주어진 메뉴의 번호를 선택해주세요.");
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
//		puts("파일오픈 실패");	//printf랑 같음
//	}
//
//	//사용자 이름, 중간 공백만 허용, 앞뒤 다 짜르기
//Invalidinput1:
//	system("cls");
//	printf("사용자 이름을 입력해주세요> \n");
//	gets_s(Name, sizeof(Name));	//공백도 입력받음
//	Name2 = trim(Name);
//	printf("%s\n", Name);
//	printf("%s\n", Name2);
//	/*GET_G_INPUT;	입력이 없는것을 체크, 나중에 수정
//	Q_CHECK;		:Q 나가는거 체크*/
//	for (int i = 0; ; i++) {
//		if (*(Name2 + i) == NULL) {
//			if (0 < i && i <= 40) {
//				printf("이름을 제대로 입력했습니다, 은행을 선택합니다\n");	
//				Sleep(2000);
//				system("cls");
//				break;
//			}
//			else {
//				printf("이름의길이가 초과됐습니다, 이름을 다시 입력해주세요\n");
//				Sleep(2000);
//				goto Invalidinput1;
//			}
//		}
//	}
//
//	//은행
//Invalidinput2:
//	//DRAWLINE('-');
//	printf("건은행-1  국은행-2  대은행-3  학은행-4  교은행-5\n");
//	//DRAWLINE('-');
//	printf("은행을 선택해주세요> ");
//	scanf("%d", &Bank);	//이렇게하면 스페이스바만 처리할수있음
//	while (getchar() != '\n');
//	/*GET_G_INPUT;
//	Q_CHECK;*/
//	if (1 <= Bank && Bank <= 5) {
//		printf("은행이 선택되었습니다\n");
//		Sleep(3000);
//		system("cls");
//	}
//	else {
//		printf("은행을 다시 입력해주세요\n");
//		goto Invalidinput2;
//	}
//
//	//아이디, 중간에 공백 허용x, 앞뒤 공백허용
//Invalidinput3:
//	printf("아이디> ");
//	scanf_s("%s", Id, sizeof(Id));
//	while (getchar() != '\n');
//	/*GET_G_INPUT;
//	Q_CHECK;*/
//	trim(Id);
//	for (int i = 0; i < strlen(Id); i++) {
//		if (isalnum(Id[i]) != NULL) {			//영문자 또는 숫자이면 0아닌 값 반환
//			if (Id[i] == NULL) {
//				printf("아이디 입력이 완료됐습니다\n");
//				printf("비밀번호를 입력합니다\n");
//				Sleep(2000);
//				system("cls");
//				break;
//			}
//		}
//		else {
//			printf("잘못된 입력이 들어왔습니다, 다시 입력해주세요\n");
//			goto Invalidinput3;
//		}
//	}
//
//	//비밀번호, 중간에 공백 허용x, 특수문자 허용, 앞뒤 공백 허용
//	do {
//		printf("비밀번호> ");
//		/*GET_G_INPUT;
//		Q_CHECK;*/
//		scanf_s("%s", password1, sizeof(password1));
//		while (getchar() != '\n');
//		trim(password1);
//		printf("비밀번호 확인> ");
//		scanf_s("%s", password2, sizeof(password2));
//		trim(password2);
//		while (getchar() != '\n');
//
//		if (strcmp(password1, password2) == 0)		//일단 여기만 오류 -> 나주엥 수정
//			pass = 0;
//		else
//			pass++;
//
//		if (pass > 0) {
//			printf("비밀번호를 다르게 입력했습니다, 다시 입력해주세요\n");
//			pass = 0;		//pass 값 다시 초기화
//			passcount++;	//입력횟수 - 5번 넘어가면 안됨
//		}
//		else if (pass == 0) {
//			printf("비밀번호를 제대로 입력했습니다\n");
//			break;
//		}
//
//		if (passcount == 5) {
//			printf("비밀번호 입력횟수 5회초과\n");
//			printf("프로그램 종료\n");
//			Sleep(2000);
//			system("cls");
//			exit(0);	//프로그램 종료
//		}
//	} while (passcount < 5);
//
//
//	fprintf(fp, "%s|%s|%s|", Name2, Id, password1);	//이상하게 Name2만 입력이 안됨, 나중에 수정
//	fclose(fp);
//}
//
//int loginMenu() {
//	
//	char Id[100];
//	char password[100];
//	char Idbuffer[100];
//	char passwordbuffer[100];
//	char* ptr;		//파일에서 읽어온 아이디, 비밀번호
//	int passcount = 0;	//비밀번호 재입력 횟수 5번
//	FILE* fp = fopen("HumanList.txt", "r");
//	
//	//아이디 검사
//RETURN1:
//	printf("아이디> ");
//	scanf_s("%s", Id, sizeof(Id));
//	while (getchar() != '\n');
//	/*GET_G_INPUT;
//	Q_CHECK;*/
//	if (fp != NULL) { 
//		if(!feof(fp)) {
//			fgets(Idbuffer, sizeof(Idbuffer), fp);
//			ptr = strtok(Idbuffer, "|");
//			ptr = strtok(NULL, "|");	//첫번째 아이디반환
//		}
//	}else
//		printf("파일에 입력된 정보x");
//	
//	 if(strcmp(ptr, Id) != 0) {
//		printf("계정 생성이 안된 아이디입니다\n");
//		printf("다시 입력해주세요\n");
//		goto RETURN1;
//	}
//	
//
//	//아이디가 입력됐다면 비밀번호 검사
//	if (strcmp(ptr, Id) == 0) {
//		printf("비밀번호> ");
//		scanf_s("%s", password, sizeof(password));
//		while (getchar() != '\n');
//		//GET_G_INPUT;
//		//Q_CHECK;
//		if (fp != NULL) {
//			if (!feof(fp)) {
//				ptr = strtok(NULL, "|");	//두번쨰 비밀번호 반환
//			}
//		}
//		else
//			printf("파일에 입력된 정보x");
//
//		do {
//			if (strcmp(ptr, password) == 0) {
//				printf("비밀번호 제대로 입력했습니다\n");
//			}else {
//				++passcount;
//				printf("비밀번호를 %d번 더 입력할 수 있습니다\n", 5-passcount);
//				if (passcount == 5) {
//					printf("비밀번호 입력가능횟수 5번 초과\n");
//					printf("프로그램을 종료합니다\n");
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
////중간 공백 지우기
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
//	*p_dest = 0;	//맨 마지막에 null 저장
//}
//
//
//// 문자열 우측 공백문자 삭제 함수
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
//// 문자열 좌측 공백문자 삭제 함수
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
//// 문자열 앞뒤 공백 모두 삭제 함수
//char* trim(char* s) {
//	return rtrim(ltrim(s));
//}