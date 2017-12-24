#define _CRT_SECURE_NO_WARNINGS 

#include "information.h"

void addInfoForServices(FILE *fi, FILE *fs, FILE *fo, Param *parametrs, InfoForServices *information) {
	InfoForServices newInfoForService;
	char phone[MAX_LENGTH_PHONE],
		code[5],
		date[MAX_LENGTH_DATE +1];
	Time	timeStart[MAX_LENGTH_TIME];
	int time = 0;

	while (!feof(fi)) {
		fscanf(fi, "%s %s %s %s %s", phone, code, date, timeStart , &newInfoForService.duration);
		phone[strlen(phone) - 1] = '\0';
		newInfoForService.phone = addPhone(phone);//Получаем телефон
		
		code[strlen(code) - 1] = '\0';
		newInfoForService.code = addCodeServices(code);//получаем код

		date[strlen(date) - 1] = '\0';
		newInfoForService.usingStartDate = addDate(date);//получаем дату
		
		newInfoForService.usingStartTime = addTime(timeStart);//время начала

		if (!(ChackDate(newInfoForService.usingStartDate , 
			parametrs->startDate , 
			parametrs->finishDate)&&ChackCode(newInfoForService.code, *parametrs))) {
			parsingClient(fs , fo , newInfoForService);
		}
		
	}


}

long long addPhone(char * text) {
	long long phone = 0;
	int length = strlen(text);
	for (int i = 0; i < length; i++)
		phone = (phone * 10) + ((int)(text[i]) - (int)('0'));
	return phone;
}

Time addTime(char *text) {
	Time time;

	time.hours	= ((int)text[0] - (int)('0')) * 10 + ((int)text[1] - (int)('0'));
	time.minutes	= ((int)text[3] - (int)('0')) * 10 + ((int)text[4] - (int)('0'));
	time.seconds	= ((int)text[6] - (int)('0')) * 10 + ((int)text[7] - (int)('0'));

	return time;
}

int ChackDate(Date newDate, Date dateStart, Date dateFinish) {
	if (newDate.year<dateStart.year || newDate.year >dateFinish.year) {
		return 0;
	}
	else if (newDate.year == dateStart.year) {
		if (newDate.month < dateStart.month) {
			return 0;
		}
		else if (newDate.month == dateStart.month) {
			if (newDate.day >= dateStart.day) return 1; else return 0;
		}
		else return 1;
	}
	else if (newDate.year == dateFinish.year) {
		if (newDate.month > dateFinish.month) {
			return 0;
		}
		else if (newDate.month == dateFinish.month) {
			if (newDate.day <= dateStart.day) return 1; else return 0;
		}
		else return 1;
	}
	else return 1;
}

int ChackCode(int code, Param parametrs) {
	if (code == parametrs.service1.code ||
		code == parametrs.service2.code ||
		code == parametrs.service3.code) {
		return 1;
	}
	else return 0;
}

void parsingClient(FILE *fs, FILE *fo, InfoForServices InfoForService) {
	Client human;
	char	middle[MAX_LENGTH_FOR_PEOPLE],
		phone[MAX_LENGTH_PHONE],
		startDate[MAX_LENGTH_DATE + 1],
		finishDate[MAX_LENGTH_DATE + 1],
		sizeDept[10];

	while (!feof(fs)) {
		fscanf(fs, "%s %s %s %s %s %s %s %d", human.name.firstName, human.name.lasttName, middle, phone, startDate, finishDate, sizeDept, &human.credit);
		
		middle[strlen(middle) - 1] = '\0';
		for (int i = 0; i < MAX_LENGTH_FOR_PEOPLE; i++)
			human.name.middleName[i] = '\0';
		addMiddle(human.name.middleName, middle);

		phone[strlen(phone) - 1] = '\0';
		human.phone = addPhone(phone);
		
		if (human.phone == InfoForService.phone)
			fprintf(fo, "%s %s %s\n", human.name.firstName, human.name.lasttName, human.name.middleName);
	}
}

void addMiddle(char *newMiddle, char *middle) {
	int length = strlen(middle);
	for (int i = 0; i < length; i++)
		newMiddle[i] = middle[i];
}
