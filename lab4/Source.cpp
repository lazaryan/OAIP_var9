/*
Лазарян Сергей Каренович
Лабораторная работа №4
Вариант 9
Задание: Написать программу, которая в считываемом файле выберет слова с нечетным количеством букв и запишет их в новый файд.
*/

#define _CRT_SECURE_NO_WARNINGS 

#define CHECK_CODE_SYMBOL	(((int)word[i] >=65	&& (int)word[i] <= 90)	||\
				((int)word[i] >= 97	&& (int)word[i] <= 122) ||\
				((int)word[i] >= -64	&& (int)word[i] <= -1)) 

#define MAX_LENGTH		255

#define SOURCE_FILE		"SourceFile.txt"

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale>

void CheckSourceFile		(FILE* SourceFile);
void EnterWord			(char *word, FILE *NewFile);
void CheckWord			(char *word, FILE *NewFile);
void ParsingFile		(FILE* SourceFile, FILE *NewFile);
void GetWord			(char *StringText, int PositionFinishSymbol, int finish, FILE *NewFile);

int StringLength		(char *StringText);

void main() {
	system("chcp 1251");
	system("cls");

	FILE *SourceFile	= fopen(SOURCE_FILE, "r");
	FILE *NewFile		= fopen("NewFile.txt", "w");

	CheckSourceFile(SourceFile);
	ParsingFile(SourceFile,NewFile);

	fclose(NewFile);
	fclose(SourceFile);
}

void CheckSourceFile(FILE* SourceFile) {
	if (SourceFile == NULL) {
		printf("Ошибка. Файл не найден");
		_getch();
		exit(0);
	}
}

void ParsingFile(FILE* SourceFile, FILE *NewFile) {
	char word[MAX_LENGTH] = "";

	while (!feof(SourceFile)) {
		fscanf(SourceFile, "%s", word);
		CheckWord(word, NewFile);
	}
}

void GetWord(char *StringText, int PositionFinishSymbol, int finish, FILE *NewFile) {
	char *word = (char*)calloc(PositionFinishSymbol + 1, sizeof(char*));

	for (int i = 0; i < PositionFinishSymbol; i++)
		word[i] = StringText[i];

	!finish ? CheckWord(word, NewFile) : EnterWord(word, NewFile);
}

void CheckWord(char *word, FILE *NewFile) {
	int length = StringLength(word);

	for (int i = 0; i < length; i++) {
		if (!CHECK_CODE_SYMBOL) {
			GetWord(word, i, 1, NewFile);

			word = word + i + 1;
			i = -1;
			length = StringLength(word);
		}

		if (i == (length - 1))
			EnterWord(word, NewFile);
	}
}

int StringLength(char *StringText) {
	int i;
	for (i = 0; StringText[i]; i++);
	return i;
}

void EnterWord(char *word, FILE *NewFile) {
	if (strlen(word) % 2 != 0)
		fprintf(NewFile,"%s ", word);
}