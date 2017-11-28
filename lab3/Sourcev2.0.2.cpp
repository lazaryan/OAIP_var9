/*
Лазарян Сергей Каренович
Лабораторная работа №3
Вариант 9
Задание: Написать программу, которая во вводимом с клавиатуры тексте выберет слова с нечетным количеством букв и выведет результат на экран.
*/

#define _CRT_SECURE_NO_WARNINGS 
#define CHECK_CODE_SYMBOL (((int)word[i] >= 65 && (int)word[i] <= 90) ||((int)word[i] >= 97 && (int)word[i] <= 122) ||((int)word[i] >= 128 && (int)word[i] <= 175) ||((int)word[i] >= 224 && (int)word[i] <= 247) ||((int)word[i] < 0))
#define MAX_LENGTH 255

#include <stdio.h> 
#include <conio.h>
#include <locale>

void CheckWord		(char *word);
void EnterWord		(char *word);
void ParsingString	(char *StringText);
void GetWord		(char *StringText, int PositionFinishSymbol, int finish);

int StringLength	(char *StringText);
int SearchSymbol	(char *StringText , int NumberSymbol);

void main() {
	system("chcp 1251");
	system("cls");

	char StringText[MAX_LENGTH] = "";

	printf("Введите строку:\n");
	fgets(StringText, MAX_LENGTH, stdin);

	ParsingString(StringText);

	_getch();
}

void ParsingString(char *StringText) {
	int PositionSpace;

	while (SearchSymbol(StringText, (int)(' ')) != NULL) {
		PositionSpace = SearchSymbol(StringText, (int)(' '));

		GetWord(StringText, PositionSpace, 0);
		StringText = StringText + PositionSpace + 1;
	}

	GetWord(StringText, StringLength(StringText), 0);
}

void GetWord(char *StringText, int PositionFinishSymbol, int finish) {
	char *word = (char*)calloc(PositionFinishSymbol + 1, sizeof(char*));

	for (int i = 0; i < PositionFinishSymbol; i++)
		word[i] = StringText[i];

	!finish ? CheckWord(word) : EnterWord(word);
}

void CheckWord(char *word) {
	int length = StringLength(word);

	for (int i = 0; i < length; i++) {
		if (!CHECK_CODE_SYMBOL) {
			GetWord(word, i, 1);

			word = word + i + 1;
			i = -1;
			length = StringLength(word);
		}

		if (i == (length - 1))
			EnterWord(word);
	}
}

void EnterWord(char *word) {
	if (strlen(word) % 2 != 0)
		printf("%s ", word);
}

int SearchSymbol(char *StringText, int NumberSymbol) {
	int length = StringLength(StringText);

	for (int i = 0; i < length; i++)
		if ((int)(StringText) == NumberSymbol)
			return i;

	return NULL;
}

int StringLength(char *StringText) {
	int i;
	for (i = 0; StringText[i]; i++);
	return i;
}