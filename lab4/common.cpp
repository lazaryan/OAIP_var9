#include <stdio.h>
#include <locale>
#include <conio.h>

int StringLength(char *StringText) {
	int i;
	for (i = 0; StringText[i]; i++);
	return i;
}

void EnterWord(char *word, FILE *NewFile) {
	if (StringLength(word) % 2 != 0)
		fprintf(NewFile, "%s ", word);
}

void CheckSourceFile(FILE* SourceFile, char *NameFile) {
	if (SourceFile == NULL) {
		printf("Ошибка открытия файла %s.", NameFile);
		_getch();
		exit(1);
	}
}