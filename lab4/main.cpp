/*
Лазарян Сергей Каренович
Лабораторная работа №4
Вариант 9
Задание: Написать программу, которая в считываемом файле выберет слова с нечетным количеством букв и запишет их в новый файд.
*/

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale>

#include "Source.h"
#include "common.h"


void main() {
	system("chcp 1251");
	system("cls");

	FILE *SourceFile, *NewFile;
	char word[MAX_LENGTH] = "";


	SourceFile	= fopen(SOURCE_FILE, "r");
	CheckSourceFile(SourceFile , SOURCE_FILE);

	NewFile		= fopen(OUTPUT_FILE, "w");
	CheckSourceFile(NewFile , OUTPUT_FILE);


	while (!feof(SourceFile)) {
		fscanf(SourceFile, "%s", word);
		CheckWord(word, NewFile);
	}

	fclose(NewFile);
	fclose(SourceFile);
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
