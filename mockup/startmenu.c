#include "userfunc.h"

static int con_flag = 1;

int startMenu()
{
	con_flag = 1;
	int selection;
REPRINT:
	system("cls");
	PRINTCEN("loginMenu");
	DRAWLINE('-');
	PRINTLEFT("1) login	2) register	3) terminate");
INVALIDINPUT:
	PRINTLEFT("Please select menu by give number");
	printf("> ");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,lines %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	selection = atoi(buffer);
	switch (selection)
	{
	case 1:
		loginMenu();
		break;
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
	PRINTCEN("registerMenu");
	DRAWLINE('-');
	PRINTLEFT("Enter ID... (Only Alphabet and Numbers (abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	if (*buffer == ':')
	{
		if (*(buffer + 1) == 'q')
		{
			return;
		}
	}
	PRINTLEFT("Enter Passward... (combination of numbers, alphabet and special characters[ !@#$%^&*() ]...  ) (abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	if (*buffer == ':')
	{
		if (*(buffer + 1) == 'q')
		{
			return;
		}
	}
	PRINTLEFT("Enter Passward again... (combination of numbers, alphabet and special characters[ !@#$%^&*() ]...  ) (abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	if (*buffer == ':')
	{
		if (*(buffer + 1) == 'q')
		{
			return;
		}
	}
	printf("no :q");
	system("pause");
}
void loginMenu()
{
	system("cls");
	PRINTCEN("mainMenu");
	DRAWLINE('-');
	PRINTLEFT("Enter ID...(abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	if (*buffer == ':')
	{
		if (*(buffer + 1) == 'q')
		{
			return;
		}
	}
	PRINTLEFT("Enter Password...(abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	if (*buffer == ':')
	{
		if (*(buffer + 1) == 'q')
		{
			return;
		}
	}
	printf("no :q");
	system("pause");
}
