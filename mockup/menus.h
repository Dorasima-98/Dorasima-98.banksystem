#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "condition.h"

#define PRINTCEN(str) printf("%*s\n",48+strlen(str)/2,str)
#define PRINTRIGHT(str) printf("%100s\n",str)
#define PRINTLEFT(str) printf("%-s\n",str)
#define DRAWLINE(ch) for(int i=0;i<100;i++)printf("%c",ch)

#define BUFF_SIZE (512)

void initConsole();
void mainMenu();
void registerMenu();
void startMenu();
void loginMenu();

static char buffer[BUFF_SIZE];
