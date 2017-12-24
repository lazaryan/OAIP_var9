#ifndef _PARAMETRS_
#define _PARAMETRS_

#include <stdio.h>
#include "source.h"

typedef struct {
	Services service1;
	Services service2;
	Services service3;
	Date startDate;
	Date finishDate;
}Param;

void addParametrs(FILE *ft, Param *parametrs);
void addServices(FILE *ft, Param *parametrs);
Date addDate(char *textDate);
int postitonComma(char *text);
void addNameServices(char *nameService, char *name);
float addPriseServices(char* text);
int addCodeServices(char *text);
void copyWord(char *unitServices, char *unit);
int postitonPoint(char *text);
double degree(int a, int b);

#endif

