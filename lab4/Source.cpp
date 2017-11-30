#define _CRT_SECURE_NO_WARNINGS 
#define CHECK_CODE_SYMBOL (((int)word[i] >= 65 && (int)word[i] <= 90) ||((int)word[i] >= 97 && (int)word[i] <= 122) ||((int)word[i] >= 128 && (int)word[i] <= 175) ||((int)word[i] >= 224 && (int)word[i] <= 247) ||((int)word[i] < 0))
#define MAX_LENGTH 255

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale>

void EnterWord		(char *word);
void CheckWord		(char *word);
void ParsingFile	(FILE* SourceFile);
void CheckSourceFile(FILE* SourceFile);
void GetWord		(char *StringText, int PositionFinishSymbol, int finish);

int StringLength(char *StringText);

void main() {
	system("chcp 1251");
	system("cls");

	FILE *SourceFile = fopen("SourceFile.txt", "r");
	FILE *NewFile = fopen("NewFile.txt", "w");fclose(NewFile);

	CheckSourceFile(SourceFile);
	ParsingFile(SourceFile);

	fclose(SourceFile);
}

void CheckSourceFile(FILE* SourceFile) {
	if (SourceFile == NULL) {
		printf("Ошибка. Файл не найден!");
		_getch();
		exit(0);
	}
}

void ParsingFile(FILE* SourceFile) {
	char word[MAX_LENGTH] = "";

	while (!feof(SourceFile)) {
		fscanf(SourceFile, "%s", word);
		CheckWord(word);
	}
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

int StringLength(char *StringText) {
	int i;
	for (i = 0; StringText[i]; i++);
	return i;
}

void EnterWord(char *word) {
	FILE *NewFile = fopen("NewFile.txt", "a");
	if (StringLength(word) % 2 != 0)
		fprintf(NewFile, "%s ", word);
	fclose(NewFile);
}
