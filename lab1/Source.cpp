#define _CRT_SECURE_NO_WARNINGS

#define DECIMETERS_IN_PALM 0.984252
#define PALM_IN_MILES 9.52381e-5

#include <stdio.h>
#include <conio.h>
#include <locale>

int EnterNumber();

void main(void) {
	system("chcp 1251");
	system("cls");

	int number;
	printf("Введите колличество дециметров: ");
	number = EnterNumber();

	printf("%d дециметров- это %.3f ладоней %.6f верст", number, number * DECIMETERS_IN_PALM, number * DECIMETERS_IN_PALM * PALM_IN_MILES);

	_getch();
}

int EnterNumber() {
	int number;
	scanf("%d", &number);

	if (getchar() != '\n') {
		printf("Ошибка ввода. Повторите попытку: ");
		EnterNumber();
	}

	return number;
}