#define _CRT_SECURE_NO_WARNINGS 

#define	MAX_LENGTH_NAME 30
#define	MAX_LENGTH_NUMBER_CUR 20
#define	MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION 40
#define LENGTH_DATE 10
#define	MAX_LENGTH_PHONE 15
#define	MAX_LENGTH_OFFICEGIBDD 60

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale>

struct cur {
	char	name[MAX_LENGTH_NAME] = "";
	char	NumberCur[MAX_LENGTH_NUMBER_CUR] = "";
	char	NumberTechnicalCertificate[MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION] = "";
	char	date[LENGTH_DATE] = "";
	char	phone[MAX_LENGTH_PHONE] = "";
	char	OfficeGIBDD[MAX_LENGTH_OFFICEGIBDD] = "";
};

void AddWord				(char *Buf_struct, char *name, int position, int code_arg);

void ChoiceStruct			(char *Buf_struct, struct cur *Auto);
void AddElemetsStruct		(char *Buf_struct, struct cur *Auto);

void ErrorEnterWord			(char* word, int size, int code_arg);

void EntryFile				(FILE *file, struct cur Auto);

void CheckNumberOrChar		(char* word, int code_arg);
void NumberSwitch			(char *word, int code_arg);

void EnterStruct			(struct cur *Auto);

void ChoiceRequest			(int *request);

void ErrorFile				(FILE *file);

void CheckName				(char* word);
void CheckDate				(char* word);
void CheckPhone				(char *word);
void CheckOfficeGIBDD		(char *word);

void EnterNumber			(int *n);
void EnterStructs			(int *n);

void EntryStruct			();
void FormStruct				();
void FormRequest			();

int StringLength			(char *StringText);

int CountTab				(char *Buf_struct);
int PositionTub				(char *Buf_struct);

void main() {
	system("chcp 1251");
	system("cls");

	int request = 0;

	printf("Выберете, что нужно сделать:\n");
	ChoiceRequest(&request);

	switch (request) {
	case 1:
		EntryStruct();
		break;
	case 2:break;
	case 3:break;
	case 4:
		exit(0);
	default:break;
	}

	_getch();
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
	printf("4)Завершение работы программы\n");
}

void FormStruct() {
	printf("Введите структуру в форме:\n");
	printf("\tимя(без инициалов)\n");
	printf("\tномер автомобиля\n");
	printf("\tномер техпаспорта\n");
	printf("\tдата рождения(в виде дд:мм:гггг)\n");
	printf("\tтелефон\n");
	printf("\tотделение регистрации ГИБДД\n");

	printf("Все элементы разделять табуляцией\n\n");
}

void ChoiceRequest(int *request) {
	FormRequest();

	scanf("%d", request);

	if (*request <= 0 || *request > 4 || getchar() != '\n') {
		printf("Ошибка. Повторите ввод:\n");
		while (getchar() != '\n');
		ChoiceRequest(request);
	}

}

void EnterStructs(int *n) {
	struct cur *Auto = (struct cur *)malloc(sizeof(struct cur *) * *n);

	FormStruct();
	FILE *file = fopen("StructFile.txt", "a");
	for (int i = 0; i < *n; i++) {
		printf("Введите %d структуру:\n", i + 1);
		EnterStruct(&Auto[i]);
		EntryFile(file, Auto[i]);
	}
	fclose(file);
}

void ErrorFile(FILE *file) {
	if (file == NULL) {
		printf("Ошибка. Файл не найден. Прекращение рабботы программы!");
		_getch();
		exit(0);
	}
}

void EntryFile(FILE *file , struct cur Auto) {
	fprintf(file, "%s\t", Auto.name);
	fprintf(file, "%s\t", Auto.NumberCur);
	fprintf(file, "%s\t", Auto.NumberTechnicalCertificate);
	fprintf(file, "%s\t", Auto.date);
	fprintf(file, "%s\t", Auto.phone);
	fprintf(file, "%s\0\n", Auto.OfficeGIBDD);
}

void EnterNumber(int *n) {
	scanf("%d", n);

	if (*n <= 0 || getchar() != '\n') {
		printf("Ошибка ввода. Повторите попытку: ");
		while (getchar() != '\n');
		EnterNumber(n);
	}
}

void EntryStruct() {
	int n = 0;

	printf("Введите колличество вводимых структур: ");

	EnterNumber(&n);
	EnterStructs(&n);
}

void EnterStruct(struct cur *Auto) {
	int length_struct = MAX_LENGTH_NAME +
						MAX_LENGTH_NUMBER_CUR +
						MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION +
						LENGTH_DATE +
						MAX_LENGTH_PHONE +
						MAX_LENGTH_OFFICEGIBDD + 5;

	char *Buf_struct = (char*)malloc(sizeof(char*)*length_struct);

	fgets(Buf_struct, length_struct, stdin);

	ChoiceStruct(Buf_struct , Auto);
	AddElemetsStruct(Buf_struct, Auto);
}

void ChoiceStruct(char *Buf_struct , struct cur *Auto) {
	if (CountTab(Buf_struct) != 5) {
		printf("Неправильный ввод структуры. Повторите попытку:\n");
		EnterStruct(Auto);
	}
}

int CountTab(char *Buf_struct) {
	int count = 0,
		length = StringLength(Buf_struct);

	for (int i = 0; i < length; i++) {
		if (Buf_struct[i] == '\t') count++;
	}

	return count;
}

void AddElemetsStruct(char *Buf_struct, struct cur *Auto) {
	int position = PositionTub(Buf_struct);
	AddWord(Buf_struct, Auto -> name, position , 1);
	Buf_struct = Buf_struct + position + 1;

	position = PositionTub(Buf_struct);
	AddWord(Buf_struct, Auto->NumberCur, position , 2);
	Buf_struct = Buf_struct + position + 1;

	position = PositionTub(Buf_struct);
	AddWord(Buf_struct, Auto->NumberTechnicalCertificate, position , 3);
	Buf_struct = Buf_struct + position + 1;

	position = PositionTub(Buf_struct);
	AddWord(Buf_struct, Auto->date, position , 4);
	Buf_struct = Buf_struct + position + 1;

	position = PositionTub(Buf_struct);
	AddWord(Buf_struct, Auto->phone, position , 5);
	Buf_struct = Buf_struct + position + 1;

	AddWord(Buf_struct, Auto->OfficeGIBDD, StringLength(Buf_struct) , 6);

}

int PositionTub(char *Buf_struct) {
	int length = StringLength(Buf_struct);

	for (int i = 0; i < length; i++) {
		if (Buf_struct[i] == '\t') return i;
	}
}

void AddWord(char *Buf_struct, char *word, int position, int code_arg) {
	for (int i = 0; i < MAX_LENGTH_NAME; i++)
		word[i] = '\0';

	for (int i = 0; i < position; i++)
		word[i] = Buf_struct[i];

	NumberSwitch(word, code_arg);
}

void CheckName(char* word) {
	int length = StringLength(word);

	for (int i = 0; i < length; i++) {
		if (!(((int)word[i] >= 65 && (int)word[i] <= 90)	||
			((int)word[i] >= 97 && (int)word[i] <= 122)		||
			((int)word[i] >= -64 && (int)word[i] <= -1)		||
			word[i] =='\n' || word[i] =='\0'
			)) {
			printf("Ошибка ввода имени. Повторите попытку: ");
			ErrorEnterWord(word , MAX_LENGTH_NAME , 1);
			break;
		}
	}
}

void CheckNumberOrChar(char* word , int code_arg) {
	int length = StringLength(word);

	for (int i = 0; i < length; i++) {
		if (!(((int)word[i] >= 65 && (int)word[i] <= 90) ||
			((int)word[i] >= 97 && (int)word[i] <= 122) ||
			((int)word[i] >= 48 && (int)word[i] <= 57) ||
			word[i] == '\n' || word[i] == '\0'
			)) {
			printf("Ошибка ввода номера автомобиля. Повторите попытку: ");

			switch (code_arg) {
			case 2:
				ErrorEnterWord(word, MAX_LENGTH_NUMBER_CUR, 2);
				break;
			case 3:
				ErrorEnterWord(word, MAX_LENGTH_NUMBER_TECHNICALCERTIFICATION, 3);
				break;
			}
			break;
		}
	}
}

void CheckDate(char* word){
	int length = StringLength(word);
	if (length != LENGTH_DATE) {
		printf("Ошибка ввода даты. Повторите попытку: ");
		ErrorEnterWord(word, LENGTH_DATE, 4);
	}
	else {
		if (!(	((int)word[0] >= 48		&& (int)word[0] <= 57) &&
				((int)word[1] >= 48		&& (int)word[1] <= 57) &&
				((int)word[3] >= 48		&& (int)word[3] <= 57) &&
				((int)word[4] >= 48		&& (int)word[4] <= 57) &&
				((int)word[6] >= 48		&& (int)word[6] <= 57) &&
				((int)word[7] >= 48		&& (int)word[7] <= 57) &&
				((int)word[8] >= 48		&& (int)word[8] <= 57) &&
				((int)word[9] >= 48		&& (int)word[9] <= 57) &&
				((word[2] == '.' && word[5] == '.') || (word[2] == ':' && word[5] == ':') || (word[2] == ' ' && word[5] == ' '))
			)) {
			printf("Ошибка ввода даты. Повторите попытку: ");
			ErrorEnterWord(word, LENGTH_DATE, 4);
		}
	}

}

void CheckPhone(char *word) {
	int length		= StringLength(word),
		brace_left	= 0,
		brace_right = 0;

	if (!(word[0] == '+' || ((int)word[0] >= 48 && (int)word[0] <= 57))) {
		printf("Ошибка ввода номера телефона. Повторите попытку: ");
		ErrorEnterWord(word, MAX_LENGTH_PHONE, 5);
	}
	for (int i = 1; i < length; i++) {
		if (word[i] == '(') brace_left++;
		else if(word[i] == ')')brace_right++;
		else if (!(((int)word[i] >= 48 && (int)word[i] <= 57) || word[i] == '(' || word[i] == ')' || word[i] == ' ' || word[i] == '\n' || word[i] == '\0')) {
			printf("Ошибка ввода номера телефона. Повторите попытку: ");
			ErrorEnterWord(word, MAX_LENGTH_PHONE, 5);
			break;
		}

		if (brace_left > 1 || brace_right > 1) {
			printf("Ошибка ввода номера телефона. Повторите попытку: ");
			ErrorEnterWord(word, MAX_LENGTH_PHONE, 5);
			break;
		}
	}

}

void CheckOfficeGIBDD(char *word) {
	int length = StringLength(word);

	for (int i = 0; i < length; i++) {
		if (!(((int)word[i] >= 65 && (int)word[i] <= 90) ||
			((int)word[i] >= 97 && (int)word[i] <= 122) ||
			((int)word[i] >= -64 && (int)word[i] <= -1) ||
			((int)word[0] >= 48 && (int)word[0] <= 57) ||
			(word[i] == '\n' || word[i] == '\0' || word[i] == ' ')
			)) {
			printf("Ошибка ввода отделения регистрации ГИБДД. Повторите попытку: ");
			ErrorEnterWord(word, MAX_LENGTH_OFFICEGIBDD, 6);
			break;
		}
	}
}

void ErrorEnterWord(char* word, int size ,int code_arg) {
	for (int i = 0; i < size; i++) {
		word[i] = '\0';
	}
	fgets(word, size, stdin);

	NumberSwitch(word, code_arg);
}

void NumberSwitch(char *word, int code_arg) {
	switch (code_arg) {
	case 1:
		CheckName(word);
		break;
	case 2:
		CheckNumberOrChar(word, 2);
		break;
	case 3:
		CheckNumberOrChar(word, 3);
		break;
	case 4:
		CheckDate(word);
		break;
	case 5:
		CheckPhone(word);
		break;
	case 6:
		CheckOfficeGIBDD(word);
		break;
	}
}