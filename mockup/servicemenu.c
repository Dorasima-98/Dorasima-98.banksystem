#include "userfunc.h"

static int con_flag = 1;

int serviceMenu()
{
	int menuSelection;
	con_flag = 1;
	system("cls");
	PRINTCEN("Service menu");
	DRAWLINE('-');

	PRINTLEFT("1) Make account 2) fixed deposit and Savings 3) Deposit and withdrawal");
	PRINTLEFT("4) Bank Transfer 5) Inquiry history 6) Back to startmenu");
	DRAWLINE('-');
INVALIDINPUT:
	PRINTLEFT("Please select menu by given numbers ");
	printf("> ");

	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	menuSelection = atoi(buffer);

	switch (menuSelection)
	{
	case 1:
		makeAccountMenu();
		break;
	case 2:
		fixedDepositAndSavingsMenu();
		break;
	case 3:
		transferMenu();
		break;
	case 4:
		atmMenu();
		break;
	case 5:
		historyInquiry();
		break;
	case 6:
		con_flag = 0;
		break;
	default:
		goto INVALIDINPUT;
		break;
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
void makeAccountMenu()
{
	system("cls");
	PRINTCEN("Make account menu");
	DRAWLINE('-');
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
void fixedDepositAndSavingsMenu()
{
	int selection;

	system("cls");
	PRINTCEN("Fixed deposit and Savings menu");
	DRAWLINE('-');
	PRINTLEFT("1) Service application 2) Service inquiry and cancellation");
INVALIDINPUT:
	PRINTLEFT("Please select menu by given numbers");
	printf("> ");

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
	selection = atoi(buffer);

	switch (selection)
	{
	case 1:
		while (1)
		{
			system("cls");
			PRINTLEFT("1) fixedDeposit	2)installmenSavings");
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
					goto ESCAPE;
				}
			}
			if (atoi(buffer) == 1)
			{
				fixedDeposit();
				goto ESCAPE;
			}
			else if (atoi(buffer) == 2)
			{
				Savings();
				goto ESCAPE;
			}
		}
	ESCAPE:
		return;
	case 2:
		inquiryAndCancel();
		return;
	default:
		goto INVALIDINPUT;
	}
}
void fixedDeposit()
{
	system("cls");
	PRINTCEN("-- Fixed deposit -- ");
	DRAWLINE('-');
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
void Savings()
{
	system("cls");
	PRINTCEN(" -- Installment savings --");
	DRAWLINE('-');
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
void transferMenu()
{
	system("cls");
	PRINTCEN("Transfer menu");
	DRAWLINE('-');
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
void inquiryAndCancel()
{
	system("cls");
	PRINTCEN("Inquiry and Cancel menu");
	DRAWLINE('-');
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
void atmMenu()
{
	system("cls");
	PRINTCEN("atm menu");
	DRAWLINE('-');
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
void historyInquiry()
{
	system("cls");
	PRINTCEN("History menu");
	DRAWLINE('-');
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
