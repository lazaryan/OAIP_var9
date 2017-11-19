/*
Лазарян Сергей Каренович
Лабораторная работа №2
Вариант 9
Задание: Написать программу, которая выводит на экран простые числа. Массив и его длина вводится пользователем.
*/

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h> 
#include <conio.h>
#include <locale>

int		EnterNumber();
bool	BoolPrime(long long number);
void	PrimeNumber(long long *data, int size);
void	EnterArrayAndSearchPrimeNumber(int SizeArray);

void main(void) {
	system("chcp 1251");
	system("cls");

	int SizeArray;

	printf("Введите количество чисел: ");
	SizeArray = EnterNumber();

	EnterArrayAndSearchPrimeNumber(SizeArray);

	_getch();
}

void EnterArrayAndSearchPrimeNumber(int SizeArray) {
	long long* data = (long long*)malloc(SizeArray * sizeof(long long*));

	for (int i = 0; i < SizeArray; i++) {
		printf("Введите %d число: ", i + 1);
		data[i] = EnterNumber();
	}

	PrimeNumber(data, SizeArray);
}

int EnterNumber() {
	int number;
	scanf("%d", &number);

	if (getchar() != '\n') {
		printf("Ошибка ввода. Повторите попытку: ");
		while (getchar() != '\n');
		number = EnterNumber();
	}

	return number;
}

void PrimeNumber(long long *data, int size) {
	for (int i = 0; i < size; i++)
		if (BoolPrime(data[i]))
			printf("%d ", data[i]);
}

bool BoolPrime(long long number) {
	for (long long i = 2; i <= sqrt(abs(number)); i++)
		if (number % i == 0) return false;

	return true;
}