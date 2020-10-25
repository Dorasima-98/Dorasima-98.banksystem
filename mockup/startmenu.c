#include "userfunc.h"

static int con_flag = 1;
static int Bank = 0;	

int startMenu()
{
	con_flag = 1;
	int selection;
REPRINT:
	system("cls");
	PRINTCEN(L"·Î±×ÀÎ ¸Ş´º");
	DRAWLINE('-');
	PRINTLEFT(L"1) ·Î±×ÀÎ	2) °èÁ¤»ı¼º	3) ÇÁ·Î±×·¥ Á¾·á");
INVALIDINPUT:
	PRINTLEFT(L"ÁÖ¾îÁø ¸Ş´ºÀÇ ¹øÈ£¸¦ ¼±ÅÃÇØÁÖ¼¼¿ä.");
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

<<<<<<< HEAD
}

=======
>>>>>>> ì½”ë“œ ê²€?¬í•¨???‰ë‚´ë§??ˆìŠµ?ˆë‹¤.


}
void registerMenu() {

	char Name[100];
	char Id[100];
	char password1[100];
	char password2[100];
	int pass = 0;
	int passcount = 0;

	//»ç¿ëÀÚ ÀÌ¸§
Invalidinput1:
	printf("»ç¿ëÀÚ ÀÌ¸§À» ÀÔ·ÂÇØÁÖ¼¼¿ä> \n");
	scanf_s("%s", Name, sizeof(Name));
	while (getchar() != '\n');
	/*GET_G_INPUT;	ÀÔ·ÂÀÌ ¾ø´Â°ÍÀ» Ã¼Å©, ³ªÁß¿¡ ¼öÁ¤
	Q_CHECK;		:Q ³ª°¡´Â°Å Ã¼Å©*/
	EraseSpace(Name);
	for (int i = 0; ; i++) {
		if (Name[i] == NULL) {
			if (0 < i && i <= 40) {
				printf("¾ÆÀÌµğ¸¦ Á¦´ë·Î ÀÔ·ÂÇß½À´Ï´Ù, ÀºÇàÀ» ¼±ÅÃÇÕ´Ï´Ù\n");
				Sleep(3000);
				system("cls");
				break;
			}
			else {
				printf(L"ÀÌ¸§ÀÇ±æÀÌ°¡ ÃÊ°úµÆ½À´Ï´Ù, ÀÌ¸§À» ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä\n");
				goto Invalidinput1;
			}
		}
	}

	//ÀºÇà
Invalidinput2:
	DRAWLINE('-');
	printf("°ÇÀºÇà-1  ±¹ÀºÇà-2  ´ëÀºÇà-3  ÇĞÀºÇà-4  ±³ÀºÇà-5\n");
	DRAWLINE('-');
	printf("ÀºÇàÀ» ¼±ÅÃÇØÁÖ¼¼¿ä> ");
	scanf_s("%d", &Bank, sizeof(Bank));	//ÀÌ·¸°ÔÇÏ¸é ½ºÆäÀÌ½º¹Ù¸¸ Ã³¸®ÇÒ¼öÀÖÀ½
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	if (1 <= Bank && Bank <= 5) {
		printf("ÀºÇàÀÌ ¼±ÅÃµÇ¾ú½À´Ï´Ù\n");
		Sleep(3000);
		system("cls");
	}
	else {
		printf("ÀºÇàÀ» ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä\n");
		goto Invalidinput2;
	}

	//¾ÆÀÌµğ
Invalidinput3:
	printf("¾ÆÀÌµğ> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	for (int i = 0; i < strlen(Id); i++) {
		if (isalnum(Id[i]) != NULL) 			//¿µ¹®ÀÚ ¶Ç´Â ¼ıÀÚÀÌ¸é 0¾Æ´Ñ °ª ¹İÈ¯
			continue;
		else {
			printf("Àß¸øµÈ ÀÔ·ÂÀÌ µé¾î¿Ô½À´Ï´Ù, ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä\n");
			goto Invalidinput3;
		}

		if (Id[i] == NULL) {
			printf("¾ÆÀÌµğ ÀÔ·ÂÀÌ ¿Ï·áµÆ½À´Ï´Ù\n");
			printf("ºñ¹Ğ¹øÈ£¸¦ ÀÔ·ÂÇÕ´Ï´Ù\n");
			Sleep(3000);
			system("cls");
			break;
		}
	}

	//ºñ¹Ğ¹øÈ£
	do {
		printf("ºñ¹Ğ¹øÈ£> ");
		/*GET_G_INPUT;
		Q_CHECK;*/
		scanf_s("%s", password1, sizeof(password1));
		while (getchar() != '\n');
		EraseSpace(password1);
		printf("ºñ¹Ğ¹øÈ£ È®ÀÎ> ");
		EraseSpace(password2);
		while (getchar() != '\n');

		if (strcmp(password1, password2) == 0)		//ÀÏ´Ü ¿©±â¸¸ ¿À·ù -> ³ªÁÖ¿¨ ¼öÁ¤
			pass = 0;
		else
			pass++;

		if (pass > 0) {
			printf("ºñ¹Ğ¹øÈ£¸¦ ´Ù¸£°Ô ÀÔ·ÂÇß½À´Ï´Ù, ´Ù½Ã ÀÔ·ÂÇØÁÖ¼¼¿ä\n");
			pass = 0;		//pass °ª ´Ù½Ã ÃÊ±âÈ­
			passcount++;	//ÀÔ·ÂÈ½¼ö - 5¹ø ³Ñ¾î°¡¸é ¾ÈµÊ
		}
		else if (pass == 0)
			printf("ºñ¹Ğ¹øÈ£¸¦ Á¦´ë·Î ÀÔ·ÂÇß½À´Ï´Ù\n");

		if (passcount == 5) {
			printf("ºñ¹Ğ¹øÈ£ ÀÔ·ÂÈ½¼ö 5È¸ÃÊ°ú\n");
			printf("ÇÁ·Î±×·¥ Á¾·á\n");
			Sleep(3000);
			system("cls");
			exit(0); //Á¤»óÀûÀÎ Á¾·á 0, ºñÁ¤»óÀûÀÎ Á¾·á 1
		}
	} while (passcount < 5);

	//ÀÌÁ¦ ÆÄÀÏ¿¡ ¾î¶»°Ô ÀÔ·ÂÇÒ°Ç°¡?
}

//ÀÌÁ¦ ÆÄÀÏÀ» ¾î¶»°Ô ºÒ·¯¿Ã°ÍÀÎ°¡?
int loginMenu() {

	char Id[100];
	char password1[100];
	char password2[100];
	char buffer[200];

	FILE* fp = fopen("12345.txt", "r");
	fgets(buffer, sizeof(buffer), fp);

	printf("¾ÆÀÌµğ> ");
	scanf_s("%s", Id, sizeof(Id));
	while (getchar() != '\n');
	/*GET_G_INPUT;
	Q_CHECK;*/
	EraseSpace(Id);
	//strcmp(Id, buffer); ±×·¸´Ù¸é ¾î¶»°Ô ¾ÆÀÌµğ, ºñ¹Ğ¹øÈ£¸¸ ºĞ·ùÇÒ°ÍÀÎ°¡



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
	*p_dest = 0;	//¸Ç ¸¶Áö¸·¿¡ null ÀúÀå
	//
}