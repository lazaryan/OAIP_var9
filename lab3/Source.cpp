#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 512

#include <stdio.h> 
#include <conio.h>
#include <locale>

void main(void) {
	system("chcp 1251");
	system("cls");

	char	word[MAX_LENGTH] = "",
		str[MAX_LENGTH]  = "";
	
	printf("Введите строку:\n");
	do {
		scanf("%s", &word);
		if (strlen(word) % 2 != 0)
			strcat(str, strcat(word," "));
	} while (getchar() != '\n');

	printf("\n%s", str);
	_getch();
}
