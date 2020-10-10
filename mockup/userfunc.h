#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE (128)

#define PRINTCEN(str) printf("%*s\n",48+strlen(str)/2,str)
#define PRINTRIGHT(str) printf("%100s\n",str)
#define PRINTLEFT(str) printf("%-s\n",str)
#define DRAWLINE(ch) for(int i=0;i<100;i++)printf("%c",ch); printf("\n")

int startMenu();
void registerMenu();
int loginMenu();

int serviceMenu();
void makeAccountMenu();
void fixedDepositAndSavingsMenu();
void fixedDeposit();
void Savings();
void inquiryAndCancel();
void transferMenu();
void atmMenu();
void historyInquiry();

char buffer[BUFF_SIZE];
