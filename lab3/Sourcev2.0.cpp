/*
Лазарян Сергей Каренович
Лабораторная работа №3
Вариант 9
Задание: Написать программу, которая во вводимом с клавиатуры тексте выберет слова с нечетным количеством букв и выведет результат на экран.
*/

#define _CRT_SECURE_NO_WARNINGS 
#define CHECK_CODE_SYMBOL (((int)word[i] >= 65 && (int)word[i] <= 90) ||((int)word[i] >= 97 && (int)word[i] <= 122) ||((int)word[i] >= 128 && (int)word[i] <= 175) ||((int)word[i] >= 224 && (int)word[i] <= 247) ||((int)word[i] < 0))
//вынес проверку кода символа в отдельную константу
#define MAX_LENGTH 255

#include <stdio.h> 
#include <conio.h>
#include <locale>
#include <string.h>

void CheckWord		(char *word);//функция проверки на наличие посторонних символов
void EnterWord		(char *word);//функция проверки длины слова
void ParsingString	(char *StringText); // функция поиска слов по пробелам
void GetWord		(char *StringText, int PositionFinishSymbol, int finish);//функция сборки слова

void main() {
	system("chcp 1251");
	system("cls");

	char StringText[MAX_LENGTH] = "";//Наша изначальная строка

	printf("Введите строку:\n");
	fgets(StringText, MAX_LENGTH, stdin);//вводим ее (считает максимум MAX_LENGTH символов)

	ParsingString(StringText);//отправляем нашу строку на дольнейшую обработку(поиск слов)

	_getch();
}

void ParsingString(char *StringText) {//функция поиска слов
	char *PositionSpace;//указатель на позицию пробела в памяти

	while (strchr(StringText, (int)(' ')) != NULL) {//пока есть пробелы
		PositionSpace = strchr(StringText, (int)(' '));//запоминаем позицию пробела

		GetWord(StringText, PositionSpace - StringText , 0);//позиция пробела минус позиция первого символа строки - номер пробела в слове
		//здесь мы отправляем нашу строку на сборку отдельного слова
		StringText = StringText + (PositionSpace - StringText) + 1;//убираем это слово из строки(работаем по принцыпу сокращения строки)
	}

	GetWord(StringText, strlen(StringText) - 1, 0);//это когда закончились пробелы, т.е. последнее слово
}

void GetWord(char *StringText, int PositionFinishSymbol , int finish) {//функция сборки слов
	char *word = (char*)calloc(PositionFinishSymbol + 1, sizeof(char*));//выделяем память для нашего слова
	//1 аргумент)Количество символов(взял на всякий + 1)
	//2 аргумент)Сколько весит каждый символ
	for (int i = 0; i < PositionFinishSymbol; i++)
		word[i] = StringText[i];//просто присваиванием собираем слово

	!finish ? CheckWord(word) : EnterWord(word);//Если слово еще не прошло проверку , то отправляем на нее , иначе уже в функцию вывода
}

void CheckWord(char *word) {//функция проверки нашего слова на наличие посоронних символов
	int length = strlen(word);//длина изначального слова

	for (int i = 0; i < length; i++) {//проходим по всем символам
		if (!CHECK_CODE_SYMBOL) {//если наш символ - не буква
			GetWord(word, i, 1);//отправляем слово на сборку и потом сразу в функцию проверки

			word = word + i + 1;//сокращаем наше слово (было фс.фыс стало фыс)
			i = -1;//счетчик колличества символов в слове(ставим -1 чтобы в конце круга он стал равен 0)
			length = strlen(word);//считаем новую длину слова
		}

		if (i == (length - 1))//если же в слове небыло посторонних символов , и мы дошли до конца , то отправляем в функцию проверки
			EnterWord(word);
	}
}

void EnterWord(char *word) {//функция выводв
	if (strlen(word) % 2 != 0)//если длина слова нечетна
		printf("%s ", word);//то выводим это слово
}