#define _CRT_SECURE_NO_WARNINGS 

#include "Parametrs.h"

void addParametrs(FILE *ft, Param *parametrs) {
	char buffDate[MAX_LENGTH_DATE];

	fgets(parametrs->service1.nameServices, MAX_LENGTH_NAME_SERVICES, ft);
	fgets(parametrs->service2.nameServices, MAX_LENGTH_NAME_SERVICES, ft);
	fgets(parametrs->service3.nameServices, MAX_LENGTH_NAME_SERVICES, ft);

	parametrs->service1.nameServices[strlen(parametrs->service1.nameServices) - 1] = '\0';//убираем\n
	parametrs->service2.nameServices[strlen(parametrs->service2.nameServices) - 1] = '\0';
	parametrs->service3.nameServices[strlen(parametrs->service3.nameServices) - 1] = '\0';

	fscanf(ft, "%s", buffDate);
	parametrs->startDate = addDate(buffDate);

	fscanf(ft, "%s", buffDate);
	parametrs->finishDate = addDate(buffDate);
}

Date addDate(char *textDate) {
	Date date;

	date.day	= ((int)textDate[0] - (int)('0')) * 10 + ((int)textDate[1] - (int)('0'));
	date.month	= ((int)textDate[3] - (int)('0')) * 10 + ((int)textDate[4] - (int)('0'));
	date.year	= ((int)textDate[6] - (int)('0')) * 1000 + ((int)textDate[7] - (int)('0'))*100 
				+ ((int)textDate[8] - (int)('0')) * 10 + ((int)textDate[9] - (int)('0'));

	return date;
}

void addServices(FILE *ft, Param *parametrs) {
	Services newServices;
	char name[MAX_LENGTH_NAME_SERVICES],
		code[5],
		prise[7],
		unit[MAX_LENGTH_UNIT];
	int comma = 0;

	while (!feof(ft)) {
		fscanf(ft, "%s %s %s %s\n", name, code, prise, unit);
		//---получаем данные
		for (int i = 0; i < MAX_LENGTH_NAME_SERVICES; i++)
			newServices.nameServices[i] = '\0';
		addNameServices(newServices.nameServices, name);//Получаем имя услуги

		code[strlen(code) - 1] = '\0';
		newServices.code = addCodeServices(code);//получаем ее код

		prise[strlen(prise) - 1] = '\0';
		newServices.prise = addPriseServices(prise);//цена услуги

		
		for (int i = 0; i < MAX_LENGTH_UNIT; i++)
			newServices.unit[i] = '\0';
		copyWord(newServices.unit, unit);//связанная величина

		//---проверяем их по имени
		if (!strcmp(parametrs->service1.nameServices, newServices.nameServices)) {
			parametrs->service1.code = newServices.code;
			parametrs->service1.prise = newServices.prise;
			for (int i = 0; i < MAX_LENGTH_UNIT; i++)
				parametrs->service1.unit[i] = '\0';
			copyWord(parametrs->service1.unit, newServices.unit);
		}
		if (!strcmp(parametrs->service2.nameServices, newServices.nameServices)) {
			parametrs->service2.code = newServices.code;
			parametrs->service2.prise = newServices.prise;
			for (int i = 0; i < MAX_LENGTH_UNIT; i++)
				parametrs->service2.unit[i] = '\0';
			copyWord(parametrs->service2.unit, newServices.unit);
		}
		if (!strcmp(parametrs->service3.nameServices, newServices.nameServices)) {
			parametrs->service3.code = newServices.code;
			parametrs->service3.prise = newServices.prise;
			for (int i = 0; i < MAX_LENGTH_UNIT; i++)
				parametrs->service3.unit[i] = '\0';
			copyWord(parametrs->service3.unit, newServices.unit);
		}
	}
}

int postitonComma(char *text) {
	int length = strlen(text);
	for (int i = 0; i < length; i++)
		if (text[i] == ',')
			return i;
	return NULL;
}

void addNameServices(char *nameService, char *name) {
	int length = strlen(name);
	for (int i = 0; i < length - 1; i++)
		nameService[i] = name[i];
}

int addCodeServices(char *text) {
	int length = strlen(text),
		count = 0;
	for (int i = 0; i < length; i++) {
		count = (count * 10) + ((int)text[i] - (int)('0'));
	}
	return count;
}

float addPriseServices(char* text) {
	double	prise	= 0;
	int	comma	= postitonPoint(text),
		length	= strlen(text);
	for (int i = 0; i < length; i++) {
		
		if (i != comma) {
			prise = prise + (degree(10, comma - i))*((int)text[i] - (int)('0'));
		}
		
	}
	return prise;
}

void copyWord(char *unitServices, char *unit) {
	int length = strlen(unit);
	for (int i = 0; i < length; i++)
		unitServices[i] = unit[i];
}

int postitonPoint(char *text) {
	int length = strlen(text);
	for (int i = 0; i < length; i++)
		if (text[i] == '.')
			return i;
	return NULL;
}

double degree(int a, int b) {
	double c = 1;
	if (b > 0)
		for (int i = 0; i < b - 1; i++)
			c = c * a;
	else
		for (int i = 0; i < abs(b); i++)
			c = c / a;
	return c;
}