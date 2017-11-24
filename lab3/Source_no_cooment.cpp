#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 255

#include <stdio.h> 
#include <conio.h>
#include <locale>

void ParsingString(char *StringText);
void CheckWord(char *word);
void EnterWord(char *word);
void GetWord(char *StringText, int position1, int position2 , int finish);

int main()
{
	system("chcp 1251");
	system("cls");

	char StringText[MAX_LENGTH] = "";

	printf("¬ведите текст:\n");
	fgets(StringText, MAX_LENGTH, stdin);

	ParsingString(StringText);
	_getch();
	return 0;
}

void ParsingString(char *StringText)
{
	int position1 = 0,
		position2,
		length = strlen(StringText);

	for (int i = 0; i < length; i++)
	{
		if (StringText[i] == ' ' || StringText[i] == '\n' || StringText[i] == '\0')
		{
			position2 = i - 1;
			GetWord(StringText, position1, position2 , 0);
			position1 = i + 1;
		}
	}
}

void GetWord(char *StringText, int position1, int position2, int finish)
{
	int length = position2 - position1 + 1;
	char word[MAX_LENGTH] = "";

	for (int i = 0; i < length; i++)
	{
		word[i] = StringText[position1 + i];
	}
	if (!finish)
	{
		CheckWord(word);
	}
	else
	{
		EnterWord(word);
	}
}

void CheckWord(char *word)
{
	int length = strlen(word),
		position1 =0,
		position2;

	for (int i = 0; i < length; i++)
	{
		if (!(
			((int)word[i] >= 65 && (int)word[i] <= 90) ||
			((int)word[i] >= 97 && (int)word[i] <= 122) ||
			((int)word[i] >= 128 && (int)word[i] <= 175) ||
			((int)word[i] >= 224 && (int)word[i] <= 247) ||
			((int)word[i] < 0)
			)) 
		{
			position2 = i - 1;
			GetWord(word, position1, position2,1);
			position1 = i + 1;
		}
		
		if ((i == (length - 1)) && position1 == 0)
		{
			EnterWord(word);
			break;
		}

		if (word[i + 1] == '\0')
		{
			position2 = i;
			GetWord(word, position1, position2 , 1);
		}
	}
}

void EnterWord(char *word)
{
	if (strlen(word) % 2 == 1)
	{
		printf("%s ", word);
	}
}
