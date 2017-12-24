#ifndef _SOURCE_
#define _SOURCE_

//---Константы

//имена файлов
#define INPUT_FILE "Param.ini"				//параметры вывода

#define FILE_INFO_ON_CLIENT "Client.txt"		//информация о клиентах
#define FILE_SERVICES "Services.txt"			//информация о услугах
#define FILE_INFO_ON_SERVICS "infoServices.txt"		//информация об оказываемых услугах

#define OUTPUT_FILE "Report.txt"			//выходной файл

//числовые константы
#define MAX_LENGTH_FOR_PEOPLE 30
#define MAX_LENGTH_NAME_SERVICES 40
#define MAX_LENGTH_UNIT 15
#define MAX_LENGTH_USING 10
#define MAX_LENGTH_DATE 11

#define MAX_LENGTH_PHONE 15
#define MAX_LENGTH_TIME 9

//---Структуры

//мини
typedef struct {
	char firstName[MAX_LENGTH_FOR_PEOPLE];//имя
	char lasttName[MAX_LENGTH_FOR_PEOPLE];//фамилия
	char middleName[MAX_LENGTH_FOR_PEOPLE];//отчество
}People;//человек

typedef struct {
	int day;//день
	int month;//месяц
	int year;//год
}Date;//дата

typedef struct {
	int hours;
	int minutes;
	int seconds;
}Time;

//составные


typedef struct {
	char nameServices[MAX_LENGTH_NAME_SERVICES];//наименование услуги
	int code;//код услуги
	double prise;//цена услуги
	char unit[MAX_LENGTH_UNIT];//единица измерения
}Services;




//---Функции для главного файла
void addFile(FILE *ft, char *nameFile);


#endif