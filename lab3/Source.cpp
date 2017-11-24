#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 255 //максимальная длина вводимой строки(проще ввести строку , потом с ней работать)

#include <stdio.h> 
#include <conio.h>
#include <locale>

void ParsingString(char *StringText);//функция поиска слов
//аргументы: наша строка
void CheckWord(char *word);//функция анализа слова на всякие символы (вдруг написали "Петя,который" вместо "Петя , который")
//аргументы: слово для анализа
void EnterWord(char *word);//функция проверки количества букв и соответственно вывод , если оно нечетно
//аргументы: конечное слово , у которого проверяем длину
void GetWord(char *StringText, int position1, int position2 , int finish);
//функция вытаскивания слова из строки
//аргументы:
//1)наша строка
//2)Позиция первой буквы слова
//3)Позиция последней буквы слова
//4)Дальше обьясню , это чтобы не писать 2 одинаковые функции , отличные одной строчкой

int main()
{
	system("chcp 1251");
	system("cls");//подключаем русские букавки

	char StringText[MAX_LENGTH] = "";//это наша строка в которой максимум MAX_LENGTH(сейчас 255) символов

	printf("Введите строку:\n");
	fgets(StringText, MAX_LENGTH, stdin);//ввод слова
	//fgets принимает 3 аргумента: 1)Переменная строки 
	//2)Сколько маексимум символов считать(если ввели больше , то они просто не обработаются и при этом ничего не сломается)
	//3)Способ ввода(stdio - клава)
	
	ParsingString(StringText);//начинаем работать с нашей строкой 
	_getch();//задержка консоли
	return 0;
}

void ParsingString(char *StringText)
{
	int 	position1 = 0,//позиция первой буквы слова
		position2,//позиция последней буквы слова
		length = strlen(StringText);//длина строки

	for (int i = 0; i < length; i++)//проходим по каждому символу нашей строки
	{
		if (StringText[i] == ' ' || StringText[i] == '\n' || StringText[i] == '\0')
		{//если встретили один из этих символов , значит слово закончилось
			position2 = i - 1;//соответственно , если на i позиции стоит пробел,
			// то на позиции i-1 стоит последняя буква слова
			GetWord(StringText, position1, position2 , 0);//зная позиции слова идем его получать
			position1 = i + 1;//соответственно новое слово начнется с i+1 позиции
		}
	}
}

void GetWord(char *StringText, int position1, int position2, int finish)
{
	int length = position2 - position1 + 1;//считаем длину слова
	char word[MAX_LENGTH] = "";//если выделять динамически , получается дичь, поэтому я сделал слова 
	//с максимальной длиной
	
	for (int i = 0; i < length; i++)//в этом цикле собираем наше слово в переменную word
	{
		word[i] = StringText[position1 + i];//Надеюсь тут понятно почему все так
	}//а теперь о том , зачем у функции 4 аргумент
	if (!finish)//если мы только получили слово и не проверяли его на посторонии символы ,
	{//то соответственно мы вызываем функцию проверки(CheckWord)
		CheckWord(word);
	}
	else//если же мы уже проверили наше слово и в случае чего получили новые слова(без лишних символов)
	{//то отправляем наше слово на проверку длины
		EnterWord(word);
	}
}

void CheckWord(char *word)//а теперь самая жуткая функция
{
	int 	length = strlen(word),//длина нашего слова
		position1 =0,//в нашем слове могут быть знаки препинания , т.е. полученное ранее слово может оказаться не одним словом
		position2;//а несколькими(вдруг написали "Петя,который" вместо "Петя , который")
	//поэтому так же создаем 2 переменные для поиска первоой и последней позиции слова

	for (int i = 0; i < length; i++)//проверяем каждый символ нашего слова
	{
		if (!(
			((int)word[i] >= 65 	&& (int)word[i] <= 90) 	|| //это страшное условие проверяет наш символ
			((int)word[i] >= 97 	&& (int)word[i] <= 122) || //является ли он сторонним символом
			((int)word[i] >= 128 	&& (int)word[i] <= 175) || //(int)word[i] - номер нашего символа в таблице ASCII
			((int)word[i] >= 224 	&& (int)word[i] <= 247) || //т.е. все эти строки - проверка на то , что наш символ
			((int)word[i] < 0)//русская или английская буква. Соответственно НЕ это условие - это любой другой знак
			)) 
		{
			position2 = i - 1;//позиция последней буквы нашего слова
			GetWord(word, position1, position2,1);//в нашем слове нет сторонних символов , поэтому мы собираем слово 
			//и отправляем его на проверку
			position1 = i + 1;//соответственно смотрим позицию первого символа нового слова
		}
		
		if ((i == (length - 1)) && position1 == 0)//если мы дошли до последнего символа и при этом 
		{//не менялась позиция первого символа- значит в слове небыло ничего , кроме слов
			EnterWord(word);//поэтому отправляем слово на проверку
			break;//выход из цикла , чтобы не попасть в следующее условие
		}//можно было поставить else if(word[i + 1] == '\0') , но я не хотел связывать эти 2 условия
		//поэтому break
		if (word[i + 1] == '\0')//это условие , если мы дошли до конца изначального слова и при этом 
		{//встречались посторонние символы
			position2 = i;//соответственно начало слова получили ранее(стр 98) и получаем позицию последнего
			GetWord(word, position1, position2 , 1);//так же собираем его и потом проверяем его длину
		}
	}
}

void EnterWord(char *word)
{
	if (strlen(word) % 2 == 1)//если количество букв в нашем слове нечетно , то соответственно вывод его на экран
	{
		printf("%s ", word);
	}
}