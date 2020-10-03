#include "menus.h"

void startMenu()
{
	system("cls");
	PRINTCEN("loginMenu");
	DRAWLINE('-');
	PRINTLEFT("1) login 2) register 3) terminate");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,lines %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}


	system("pause");

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
	PRINTLEFT("Enter Passward... (combination of numbers, alphabet and special characters(!@#$%^&*()_+)) (abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	PRINTLEFT("Enter Passward again... (combination of numbers, alphabet and special characters(!@#$%^&*()_+)) (abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}

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
	PRINTLEFT("Enter Password...(abort to \":q\")");
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}


	system("pause");
}
void mainMenu()
{
	system("cls");
	PRINTCEN("startMenu");
	DRAWLINE('-');
	if (fgets(buffer, BUFF_SIZE, stdin) == NULL)
	{
		perror("fgets() failed");
		fprintf(stderr, "error on %s,line %d", __FILE__, __LINE__);
		system("pause");
		exit(1);
	}
	system("pause");
}
