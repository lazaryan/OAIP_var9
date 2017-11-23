#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 255

#include <stdio.h> 
#include <conio.h>
#include <locale>
#include <string.h>

void AddWord(char *str);
void CheckString(char *word);
void ParsingString(char *str, char *word, int pos1, int pos2);

void main(void) {
	system("chcp 1251");
	system("cls");

	char str[MAX_LENGTH] = "";

	printf("Введите строку:\n");

	fgets(str, MAX_LENGTH, stdin);
	AddWord(str);

	_getch();
}

void AddWord(char *str) {
	char word[MAX_LENGTH] = "";
	int leight = strlen(str),
	    pos1 = 0,
	    pos2;

	for (int i = 0; i < leight; i++)
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0') {
			pos2 = i;

			ParsingString(str, word, pos1, pos2);
			if (strlen(word) % 2 != 0)
				CheckString(word);

			pos1 = pos2 + 1;
		}
}

void ParsingString(char *str, char *word, int pos1, int pos2) {
	int leight = strlen(word);

	for (int i = 0; i < leight; i++)
		word[i] = '\0';

	char *ptr = str;
	ptr = ptr + pos1;
	pos2 = pos2 - pos1;

	strncpy(word, ptr, pos2);
}

void CheckString(char *word) {
	char newWord[MAX_LENGTH] = "";
	int leight = strlen(word),
	    pos1 =0,
	    pos2;

	for (int i = 0; i < leight; i++) {
		if ((i == (leight-1)) && pos1 == 0) {
			printf("%s ", word);
			break;
		}

		if (!(
			((int)word[i] >= 65	&& (int)word[i] <= 90)	||
			((int)word[i] >= 97	&& (int)word[i] <= 122) ||
			((int)word[i] >= 128	&& (int)word[i] <= 175) ||
			((int)word[i] >= 224	&& (int)word[i] <= 247)
			)) {
				pos2 = i  - pos1;
				ParsingString(word, newWord, pos1, pos2);
				if(strlen(newWord) % 2 != 0)
					printf("%s ", newWord);

				pos1 = i + 1;
		}

		if (word[i+1] == '\0') {
			pos2 = i+1;

			ParsingString(word, newWord, pos1, pos2);
			if (strlen(newWord) % 2 != 0)
				printf("%s ", newWord);
		}
	}
}
