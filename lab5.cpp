#define _CRT_SECURE_NO_WARNINGS 

/*Константы длины*/
#define	MAX_LENGTH_NAME								35
#define	MAX_LENGTH_NUMBER_CUR						20
#define	MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION	40
#define LENGTH_DATE									12
#define	MAX_LENGTH_PHONE							25
#define	MAX_LENGTH_OFFICEGIBDD						60

/*Константы для проверок ввода*/
#define MAX_LENGTH_STRING				MAX_LENGTH_NAME+							\
										MAX_LENGTH_NUMBER_CUR+						\
										MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION+	\
										LENGTH_DATE+								\
										MAX_LENGTH_PHONE+							\
										MAX_LENGTH_OFFICEGIBDD

#define CODE_ENGLESH_SYMBOL_SMALL		((int)word[i] >= 65		&& (int)word[i] <= 90)
#define CODE_ENGLESH_SYMBOL_BIGG		((int)word[i] >= 97		&& (int)word[i] <= 122)
#define CODE_RUSSIAN_SYMBOL				((int)word[i] >= -64	&& (int)word[i] <= -1)
#define CODE_NUMBER_SYMBOL				((int)word[i] >= 48		&& (int)word[i] <= 57)
#define FINISH_SYMBOL					word[i] == '\n' || word[i] == '\0'

#define CODE_ENGLESH_SYMBOL				CODE_ENGLESH_SYMBOL_SMALL	||\
										CODE_ENGLESH_SYMBOL_BIGG

#define CHECK_NAME						CODE_ENGLESH_SYMBOL ||\
										CODE_RUSSIAN_SYMBOL	||\
										FINISH_SYMBOL

#define CODE_NUMBER_OR_SYMBOL			CODE_ENGLESH_SYMBOL ||\
										CODE_NUMBER_SYMBOL	||\
										FINISH_SYMBOL

#define CHECK_CODE_DATE					(((int)word[0] >= 48	&& (int)word[0] <= 57) &&\
										((int)word[1] >= 48		&& (int)word[1] <= 57) &&\
										((int)word[3] >= 48		&& (int)word[3] <= 57) &&\
										((int)word[4] >= 48		&& (int)word[4] <= 57) &&\
										((int)word[6] >= 48		&& (int)word[6] <= 57) &&\
										((int)word[7] >= 48		&& (int)word[7] <= 57) &&\
										((int)word[8] >= 48		&& (int)word[8] <= 57) &&\
										((int)word[9] >= 48		&& (int)word[9] <= 57) &&\
										((word[2] 	== '.'		&& word[5] == '.')	||\
										(word[2] 	== ':'		&& word[5] == ':')	||\
										(word[2] 	== ' '		&& word[5] == ' ')))

#define CHECK_OFFICE_GIBDD				CODE_ENGLESH_SYMBOL_SMALL	||\
										CODE_ENGLESH_SYMBOL_BIGG	||\
										CODE_RUSSIAN_SYMBOL			||\
										CODE_NUMBER_SYMBOL			||\
										(FINISH_SYMBOL || word[i] == ' ')

/*библиотеки*/
#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale>

struct car {
	char	name						[MAX_LENGTH_NAME];
	char	NumberCur					[MAX_LENGTH_NUMBER_CUR];
	char	NumberTechnicalCertificate	[MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION];
	char	date						[LENGTH_DATE];
	char	phone						[MAX_LENGTH_PHONE];
	char	OfficeGIBDD					[MAX_LENGTH_OFFICEGIBDD];
};

/*функции*/

/*общие*/
void EnterNumberOrSymbol				(char *word, int max_length);
void ChoiceFunction						(int request);
void EnterOfficeGIBDD					(char *word);
void EnterPhone							(char *word);
void EnterName							(char *word);
void EnterDate							(char *word);
void FormStructText						();
void FormRequest						();
void FormStruct							();

int StringLength						(char *StringText);
int СhoiceRequest						(int max);

/*1 запрос*/
void EnterWord							(char *word, int max_length, int *length);
void EntryFile							(FILE *file, struct car Auto);
void EnterStruct						(struct car *Auto);
void EnterStructs						();

int EnterCountStructs					();

/*2 запрос*/
void PassingFile						(int request, char *search_text);
void StringCopy							(char *new_text, char *text);
void SearchText							();

int SearchPunct							(char *text_file, int request, char *search_text);
int PositionTub							(char *word);
/*3 запрос*/
void OutputStruct						();

/*4 запрос*/
void SortingFile();
/*код*/
int main() {
	system("chcp 1251");
	system("cls");

	int request = 0;

	printf("Выбирете тип запроса:\n");
	FormRequest();

	printf("Ввод: ");
	request = СhoiceRequest(5);
	ChoiceFunction(request);

	
	getchar();
	return 1;
}

int StringLength(char *StringText) {
	int i;
	for (i = 0; StringText[i]; i++);
	return i;
}

void FormRequest() {
	printf("1)Внесение структуры в файл\n");
	printf("2)Поиск структуры в файле\n");
	printf("3)Вывод стуктур на экран\n");
	printf("4)Сортировка данных в файле\n");
	printf("5)Завершение работы программы\n");
}

int СhoiceRequest(int max) {
	int		request = 0;
	bool	error	= true;

	do {
		scanf("%d", &request);

		if (getchar() != '\n') {
			printf("Ошибка ввода. Повторите попытку: ");
			while (getchar() != '\n');
		}
		else (request < 1 || request > max) ? printf("Ошибка. Данный запрос отсутствует. Повторите попытку: ") : error = false;

	} while (error);

	return request;
}

void ChoiceFunction(int request) {
	switch (request) {
	case 1:
		EnterStructs();
		break;
	case 2:
		SearchText();
		break;
	case 3:
		OutputStruct();
		break;
	case 4:
		SortingFile();
		break;
	case 5:
		exit(0);
	}
}

void EnterStructs() {
	int count = 0;

	printf("Введите количество структур: ");
	count = EnterCountStructs();

	struct car *Auto = (struct car *)malloc(sizeof(struct car *) * count);
	
	FormStruct();

	FILE *StructFile = fopen("StructFile.txt", "a");
	if (StructFile == NULL) {
		StructFile = fopen("StructFile.txt", "w");
	}

	for (int i = 0; i < count; i++) {
		printf("Ввод %d структуры:\n", i + 1);
		EnterStruct(&Auto[i]);
		EntryFile(StructFile, Auto[i]);
	}
	fclose(StructFile);

	printf("Будет еще запрос?(1-да; 2-нет)\n");
	printf("Ввод: ");
	int request = СhoiceRequest(2);
	if (request == 1) {
		FormRequest();
		printf("Ввод: ");
		request = СhoiceRequest(5);
		ChoiceFunction(request);
	}
	else exit(0);
}

void EntryFile(FILE *file, struct car Auto) {
	fprintf(file, "%s\t", Auto.name);
	fprintf(file, "%s\t", Auto.NumberCur);
	fprintf(file, "%s\t", Auto.NumberTechnicalCertificate);
	fprintf(file, "%s\t", Auto.date);
	fprintf(file, "%s\t", Auto.phone);
	fprintf(file, "%s\n\0", Auto.OfficeGIBDD);
}

int EnterCountStructs() {
	int		count = 0;
	bool	error = true;

	do {
		scanf("%d", &count);

		if (getchar() != '\n' ) {
			printf("Ошибка ввода. Повторите попытку: ");
			while (getchar() != '\n');
		}
		else (count < 1) ? printf("Ошибка. Количество элементов положиельно. Повторите попытку: ") : error = false;

	} while (error);

	return count;
}

void FormStruct() {
	printf("Введите структуру в форме:\n");
	FormStructText();
}

void FormStructText() {
	printf("\t1)имя(без инициалов)\n");
	printf("\t2)номер автомобиля\n");
	printf("\t3)номер техпаспорта\n");
	printf("\t4)дата рождения(в виде дд:мм:гггг)\n");
	printf("\t5)телефон\n");
	printf("\t6)отделение регистрации ГИБДД\n");
}

void EnterStruct(struct car *Auto) {
	printf("\tВведите имя: ");
	EnterName(Auto->name);

	printf("\tВведите номер автомобиля: ");
	EnterNumberOrSymbol(Auto->NumberCur , MAX_LENGTH_NUMBER_CUR);

	printf("\tВведите номер техпаспорта: ");
	EnterNumberOrSymbol(Auto->NumberTechnicalCertificate , MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION);

	printf("\tВведите дату рождения: ");
	EnterDate(Auto->date);

	printf("\tВведите номер телефона: ");
	EnterPhone(Auto->phone);

	printf("\tВведите отделение регистрации ГИБДД: ");
	EnterOfficeGIBDD(Auto->OfficeGIBDD);
}

void EnterName(char *word) {
	int length = 0;
	EnterWord(word, MAX_LENGTH_NAME, &length);

	for (int i = 0; i < length; i++) {
		if (!(CHECK_NAME)) {
			printf("\tОшибка ввода имени. Повторите попытку: ");
			EnterName(word);
			break;
		}
	}
}

void EnterNumberOrSymbol(char *word , int max_length) {
	int length = 0;
	EnterWord(word, max_length, &length);

	for (int i = 0; i < length; i++) {
		if (!(CODE_NUMBER_OR_SYMBOL)) {
			printf("\tОшибка ввода. Повторите попытку: ");
			EnterNumberOrSymbol(word , max_length);
			break;
		}
	}
}

void EnterDate(char *word) {
	int length = 0;
	EnterWord(word, LENGTH_DATE, &length);

	if (!(CHECK_CODE_DATE)) {
		printf("\tОшибка ввода даты. Повторите попытку: ");
		EnterDate(word);
	}
}

void EnterPhone(char *word) {
	int length		= 0,
		brace_left	= 0,
		brace_right = 0;

	EnterWord(word, MAX_LENGTH_PHONE, &length);
	if (!(word[0] == '+' || ((int)word[0] >= 48 && (int)word[0] <= 57))) {
		printf("\tОшибка ввода номера телефона. Повторите попытку: ");
		EnterPhone(word);
	}
	for (int i = 1; i < length; i++) {
		if (word[i] == '(') brace_left++;
		else if (word[i] == ')')brace_right++;
		else if (!	(CODE_NUMBER_SYMBOL || word[i] == '(' || word[i] == ')' || word[i] == ' ' || FINISH_SYMBOL) || 
					(word[i] == ')' && brace_left == 0)) {
			printf("\tОшибка ввода номера телефона. Повторите попытку: ");
			EnterPhone(word);
			break;
		}

		if (brace_left > 1 || brace_right > 1) {
			printf("\tОшибка ввода номера телефона. Повторите попытку: ");
			EnterPhone(word);
			break;
		}
	}
}

void EnterOfficeGIBDD(char *word) {
	int length = 0;
	EnterWord(word, MAX_LENGTH_OFFICEGIBDD, &length);

	for (int i = 0; i < length; i++) {
		if (!(CHECK_OFFICE_GIBDD)) {
			printf("\tОшибка ввода отделения регистрации ГИБДД. Повторите попытку: ");
			EnterOfficeGIBDD(word);
			break;
		}
	}
}

void EnterWord(char *word, int max_length, int *length) {
	for (int i = 0; i < max_length; i++)
		word[i] = '\0';

	fgets(word, max_length, stdin);

	*length = StringLength(word);

	word[*length - 1] = '\0';

}

/*3 запрос*/
void OutputStruct() {
	FILE *StructFile = fopen("StructFile.txt", "r");
	if (StructFile == NULL) {
		printf("Файл не найден. Будут производиться другие запросы?(1-да; 2-нет)\n");
		printf("Ввод: ");
		int request = СhoiceRequest(2);
		if (request == 1) {
			FormRequest();
			request = СhoiceRequest(5);
			ChoiceFunction(request);
		}
		else exit(0);
	}
	else {
		char text_file[MAX_LENGTH_STRING] = "";
		while (fgets(text_file, MAX_LENGTH_STRING + 10, StructFile) != NULL)
			printf("%s\n", text_file);
		printf("Будет еще запрос?(1-да; 2-нет)\n");
		printf("Ввод: ");
		int request = СhoiceRequest(2);
		if (request == 1) {
			FormRequest();
			printf("Ввод: ");
			request = СhoiceRequest(5);
			ChoiceFunction(request);
		}
		else exit(0);
	}
	fclose(StructFile);
}

/*2 запрос*/
void SearchText() {
	printf("Выберете критерий поиска:\n");
	FormStructText();
	printf("Ввод: ");

	int request = СhoiceRequest(6);

	printf("Введите текст для поиска: ");
	char search_text[MAX_LENGTH_OFFICEGIBDD] = "";
	switch (request) {
	case 1: 
		EnterName(search_text);
		break;
	case 2:
		EnterNumberOrSymbol(search_text, MAX_LENGTH_NUMBER_CUR);
		break;
	case 3:
		EnterNumberOrSymbol(search_text, MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION);
		break;
	case 4:
		EnterDate(search_text);
		break;
	case 5:
		EnterPhone(search_text);
		break;
	case 6:
		EnterOfficeGIBDD(search_text);
		break;
	}

	PassingFile(request , search_text);
	printf("Будет еще запрос?(1-да; 2-нет)\n");
	printf("Ввод: ");
	request = СhoiceRequest(2);
	if (request == 1) {
		FormRequest();
		printf("Ввод: ");
		request = СhoiceRequest(5);
		ChoiceFunction(request);
	}
	else exit(0);
}

void PassingFile(int request , char *search_text) {
	FILE *StructFile = fopen("StructFile.txt", "r");
	if (StructFile == NULL) {
		printf("Файл не найден. Будут производиться другие запросы?(1-да; 2-нет)\n");
		printf("Ввод: ");
		int request = СhoiceRequest(2);
		if (request == 1) {
			FormRequest();
			request = СhoiceRequest(5);
			ChoiceFunction(request);
		}
		else exit(0);
	}
	else {
		char	text_file		[MAX_LENGTH_STRING]	= "",
				buf_text_file	[MAX_LENGTH_STRING]	= "";
		int		coincidence							= 0,
				count								= 0;

		while (fgets(text_file, MAX_LENGTH_STRING + 10, StructFile) != NULL) {
			text_file[StringLength(text_file) - 1] = '\0';

			StringCopy(buf_text_file , text_file);
			coincidence = SearchPunct(text_file , request , search_text);

			if (coincidence) {
				printf("%s\n", buf_text_file);
				count++;
			}
		}

		if (!count) printf("Совпадений не найдено!\n");
	}
}

void StringCopy(char *new_text, char *text) {
	for (int i = 0; i < MAX_LENGTH_STRING; i++)
		new_text[i] = '\0';

	int length = StringLength(text) ;
	for (int i = 0; i < length; i++)
		new_text[i] = text[i];
}

int SearchPunct(char *text_file, int request , char *search_text) {
	int length			= StringLength(text_file),
		position_tub	= 0,
		coincidence		= 1;

	for (int i = 0; i < (request - 1); i++) {
		position_tub = PositionTub(text_file);
		text_file = text_file + position_tub + 1;
	}

	for (int i = 0; search_text[i] != '\n' || search_text[i] != '\0'; i++) {
		if ((search_text[i] == '\n' || search_text[i] == '\0') && i > 0 ) {
			break;
		}

		if (text_file[i] != search_text[i] || ((search_text[i] == '\n' || search_text[i] == '\0') && i < StringLength(search_text))) {
			coincidence = 0;
			break;
		}
	}

	if (coincidence)  return 1; else return 0;
}

int PositionTub(char *word) {
	int length = StringLength(word);

	for (int i = 0; i < length; i++)
		if (word[i] == '\t')
			return i;

	return NULL;
}

/*4 запрос*/
void SortingFile() {

}