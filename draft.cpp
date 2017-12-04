#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 255

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale>

struct cur {
	char name[MAX_LENGTH];
	int NumberCur;
	int NumberTechnicalCertificate;
	char date[MAX_LENGTH];
	int phone;
	char OfficeGIBDD[MAX_LENGTH];
};

void EnterText(cur* Auto);
void EnterName(char* name);
void EnterWord(char* name);

int StringLength(char *StringText);

void main() {
	system("chcp 1251");
	system("cls");

	struct cur Auto;

	printf("Введите вашу структуру:\n");
	EnterText(&Auto);
	printf("%s", Auto.name);

	_getch();
}

void EnterText(cur* Auto) {
	EnterName(Auto -> name);
}

void EnterName(char* name) {
	int length = 0;
	fgets(name, MAX_LENGTH, stdin);
	//EnterWord(name);

	length = StringLength(name);
	for (int i = 0; i < length - 1; i++) {
		if (!((int)name[i] == 32 || (int)name[i] == 44 || (int)name[i] == 46 ||
			((int)name[i] >= 65		&& (int)name[i] <= 90)	||
			((int)name[i] >= 97		&& (int)name[i] <= 122) ||
			((int)name[i] >= -47	&& (int)name[i] <= 0)	||
			((int)name[i] >= -115	&& (int)name[i] <= -99)
			)) {
			printf("Ошибка ввода имени.Повторите попытку: ");
			EnterName(name);
		}
	}
}

void EnterWord(char* word) {
	char c = ' ';
	int i = 0;
	while (c != '\t' && c != '\n') {
		c = getchar();
		word[i] = c;
		i++;
		if (i == MAX_LENGTH) {
			printf("Слишком большой текст. Повторите ввод: ");
			for (int j = 0; j < i; j++) word[j] = '\0';
			while (getchar() != '\n');
			EnterName(word);
		}
	}
}

int StringLength(char *StringText) {
	int i;
	for (i = 0; StringText[i]; i++);
	return i;
}