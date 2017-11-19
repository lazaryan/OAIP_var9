#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h> 
#include <conio.h>
#include <locale>

int EnterNumber();
void PrimeNumber(long long *data , int size);
bool BoolPrime(long long number);

void main(void) {
	system("chcp 1251");
	system("cls");

	int SizeArray;

	printf("Введите длину массива: ");
	SizeArray = EnterNumber();

	long long* data = (long long*)malloc(SizeArray * sizeof(long long*));
	for (int i = 0; i < SizeArray; i++) {
		printf("Введите %d элемент: ", i+1);
		data[i] = EnterNumber();
	}

	PrimeNumber(data , SizeArray);

	_getch();
}

int EnterNumber() {
	int number;
	scanf("%d", &number);

	if (getchar() != '\n') {
		printf("Ошибка вводаю Повторите попыку: ");
		number = EnterNumber();
	}

	return number;
}

void PrimeNumber(long long *data, int size) {
	for (int i = 0; i < size; i++)
		if (BoolPrime(data[i])) {
			printf("%d ", data[i]);
		}
}

bool BoolPrime(long long number) {
	for (long long i = 2; i <= sqrt(abs(number)); i++)
		if (number % i == 0) return false;

	return true;
}