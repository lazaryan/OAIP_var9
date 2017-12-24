#define _CRT_SECURE_NO_WARNINGS 

//---стандартные библиотеки
#include <stdio.h> 

//---мои библиотеки
#include "source.h"
#include "Parametrs.h"
#include "information.h"

void main(void) {
	system("chcp 1251");
	system("cls");

	FILE	*input, 
		*clienFile, 
		*servicesFile, 
		*infooSevicesFile, 
		*output;
	Param parametrs;
	InfoForServices information;

	//---открываем файлы для работы
	input			= fopen(INPUT_FILE,		"r");	addFile(input ,			INPUT_FILE);
	clienFile		= fopen(FILE_INFO_ON_CLIENT,	"rt");	addFile(clienFile ,		FILE_INFO_ON_CLIENT);
	servicesFile		= fopen(FILE_SERVICES,		"rt");	addFile(servicesFile ,		FILE_SERVICES);
	infooSevicesFile	= fopen(FILE_INFO_ON_SERVICS,	"rt");	addFile(infooSevicesFile ,	FILE_INFO_ON_SERVICS);
	output			= fopen(OUTPUT_FILE,		"wt");	addFile(output ,		OUTPUT_FILE);

	//---Получаем параметры
	addParametrs(input, &parametrs);
	//---Получаем информацию о нужных услугах
	addServices(servicesFile, &parametrs);
	//---информация об оказаннх услугах и парсинг клиентов
	addInfoForServices(infooSevicesFile, clienFile, output, &parametrs , &information);

	fclose(input);
	fclose(clienFile);
	fclose(servicesFile);
	fclose(infooSevicesFile);
	fclose(output);
}

void addFile(FILE *ft , char *nameFile) {
	if (ft == NULL) {
		fprintf(stderr, "Ошибка открытия %s файла", nameFile);
		exit(1);
	}
}