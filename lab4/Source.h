#ifndef _SOURCE_
#define _SOURCE_

//---���������
#define MAX_LENGTH		255

#define SOURCE_FILE		"SourceFile.txt"
#define OUTPUT_FILE		"NewFile.txt"

//---���������� ������� ����
#define CHECK_CODE_SYMBOL	(((int)word[i] >=65	&& (int)word[i] <= 90)	||\
				((int)word[i] >= 97	&& (int)word[i] <= 122) ||\
				((int)word[i] >= -64	&& (int)word[i] <= -1))

//---���������� ������� �������
void CheckWord(char *word, FILE *NewFile);
void GetWord(char *StringText, int PositionFinishSymbol, int finish, FILE *NewFile);


#endif
