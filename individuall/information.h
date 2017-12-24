#ifndef _INFORMATION_
#define _INFORMATION_

#include "Parametrs.h"
#include "source.h"


typedef struct {
	long long phone;
	int code;
	Date usingStartDate;
	Time usingStartTime;
	char duration[MAX_LENGTH_USING];
}InfoForServices;

typedef struct {
	People name;//имя человека
	int phone;//телефон
	Date startDate;//дата заключения договора
	Date finishDate;//дата окончания договора
	int debt;//задолжность
	int credit;//допустимый кредит
}Client;//Информация о клиенте


void addInfoForServices(FILE *fi,FILE *fs, FILE *fo , Param *parametrs, InfoForServices *information);
long long addPhone(char * text);
Time addTime(char *text);
int ChackDate(Date newDate, Date dateStart, Date dateFinish);
int ChackCode(int code, Param parametrs);
void parsingClient(FILE *fs, FILE *fo, InfoForServices InfoForService);
void addMiddle(char *newMiddle, char *middle);
#endif
