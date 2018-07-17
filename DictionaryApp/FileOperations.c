#include "FileOperations.h"
#include <locale.h>

FILE* openFileForRead(char* fileName)
{
	FILE* file = NULL;

	file = fopen(fileName, "r");

	return file;
}

FILE* createNewFileForWrite(char* fileName)
{
	FILE* file = NULL;
	file = fopen(fileName, "w");

	return file;
}

FILE* openFileForAppend(char* fileName)
{
	FILE* file = fopen(fileName, "a");

	return file;
}

int getLinesCount(FILE* file)
{
	if (file == NULL) return -1;
	int lineCount = 0;
	char *lineS[256];
	char *readLine;
	while (!feof(file))
	{
		readLine = fgets(lineS, 256, file);
		if (readLine != NULL)
			lineCount++;
	}

	fseek(file, 0, SEEK_SET);

	return lineCount;
}
