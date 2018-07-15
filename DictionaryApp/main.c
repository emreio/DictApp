#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "FileOperations.h"
#include <locale.h>
#include <stdbool.h>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
   //define something for Windows (64-bit only)
#else
   //define something for Windows (32-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
// linux
#elif __unix__ // all unices not caught above
// Unix
#elif defined(_POSIX_VERSION)
// POSIX
#else
#   error "Unknown compiler"
#endif

void externalFunc()
{
	printf("i am external \n");
}

const char* InitialFileName = "sozluk.txt";
const char* TurkishDictFileName = "turkce.txt";
const char* EnglishDictFileName = "ingilize.txt";
const char* TurkishLocaleName = "Turkish";

typedef struct
{
	char *key;
	char *value;
}Dictionary;


int compare(const void *p, const void *p1)
{
	Dictionary v1 = *(Dictionary *)p;
	Dictionary v2 = *(Dictionary *)p1;

	return strcmp(v1.key, v2.key);
}

int main()
{
	setlocale(LC_ALL, TurkishLocaleName);

	int res = strcmp("emreee", "emreee");

	printf("%d ", res);

	getchar();

	return;

	int lineCount = 0;

	FILE *file = openFileForRead(InitialFileName);
	FILE *file1 = createNewFileForWrite(TurkishDictFileName);
	FILE *file2 = createNewFileForWrite(EnglishDictFileName);

	if (file == NULL)
	{
		perror("Error opening file");
		getchar();
		exit(-1);
	}

	lineCount = getLinesCount(file);

	Dictionary* dictionary = malloc(sizeof(Dictionary) * lineCount);

	int i = 0;
	char *buffer[256];
	char *dictionaryLine;
	char *token1;
	int tokenLength = 0;

	while (!feof(file))
	{
		fgets(buffer, 256, file);
		dictionaryLine = malloc(strlen(buffer) + 1);
		strcpy(dictionaryLine, buffer);
		token1 = strtok(dictionaryLine, " ");
		tokenLength = strlen(token1);

		if (token1[tokenLength - 1] == '\n')
			token1[tokenLength - 1] = '\0';

		dictionary[i].key = malloc(tokenLength + 1);
		strcpy(dictionary[i].key, token1);

		while (token1 != NULL)
		{
			token1 = strtok(NULL, " ");

			if (token1 == NULL)
				break;

			tokenLength = strlen(token1);

			if (token1[tokenLength - 1] == '\n')
				token1[tokenLength - 1] = '\0';

			dictionary[i].value = malloc(tokenLength + 1);
			strcpy(dictionary[i].value, token1);
		}

		i++;
	}


	for (int j = 0; j < lineCount; j++)
	{
		printf("%s - %s\n", dictionary[j].key, dictionary[j].value);
	}

	qsort(dictionary, 3, sizeof(Dictionary), compare);

	printf("after sort \n");

	for (int j = 0; j < lineCount; j++)
	{
		if (j == lineCount - 1)
		{

			fputs(dictionary[j].key, file1);
			fputs(dictionary[j].value, file2);
		}

		else
		{
			fputs(strcat(dictionary[j].key, "\n"), file1);
			fputs(strcat(dictionary[j].value, "\n"), file2);
		}
	}

	fclose(file1);
	fclose(file2);
	fclose(file);

	printf("sözlükler oluþturuldu. \n");


	char searchString[100];

	scanf("%s", searchString);




	getchar();
}


int main11()
{
	int c;
	int eof;
	int lines = 0;
	setlocale(LC_ALL, "Turkish");

	FILE* file = createNewFileForWrite(InitialFileName);

	fputs("\n þemsi paþa pasajý", file);

	fclose(file);

	FILE *	newfile = openFileForAppend(InitialFileName);

	if (newfile == NULL)
	{
		perror("Error opening file");
	}

	fputs("\n merhaba dünya", newfile);

	fclose(newfile);

	file = openFileForRead(InitialFileName);

	int linesCount = getLinesCount(file);

	printf("lines count: %d ", lines);

	fseek(file, 0, SEEK_SET);

	if (-1)
	{
		printf("true");
	}

	while (1) {
		c = fgetc(file);
		eof = feof(file);
		if (eof) {
			break;
		}
		printf("%d - %c \n", c, c);
	}

	char *str[256];

	fseek(file, 0, SEEK_SET);

	while (1)
	{
		fgets(str, 256, file);
		printf("%s \n", str);

		if (feof(file))
			break;
	}


	fseek(file, 0, SEEK_SET);

	while (!feof(file))
	{
		c = fgetc(file);
		if (c == '\n')
		{
			lines++;
		}
	}

	printf("lines count %d \n", lines);
	fclose(file);

	getchar();
}


int main1()
{
	__int16 testI = 1;
	printf("%d\n", testI);
	printf("%p\n", &testI);

	printf("%d\n", sizeof(testI));
	printf("%d\n", sizeof(__int16));


	printf("%p\n", &testI + 1);
	printf("%p\n", &testI + 2);

	test(testI);

	printf("%d\n", testI);
	printf("%p\n", &testI);

	getchar();
	char *path = getenv("HOME");
	//printf(path);

#ifdef __APPLE__
	printf("platform : osx \n");
#else
	printf("not osx \n");
	getchar();
#endif
	int i = 321;
	char* p;
	void(*fun_ptr)();

	p = &i;
	printf("%d\n", *p);

	printf("Size of int: %d\n", sizeof(int));
	printf("Size of char: %d\n", sizeof(char));
	printf("Size of int: %d\n", sizeof(int));
	printf("Size of long: %d\n", sizeof(long));
	printf("Size of pointer: %d\n", sizeof(p));

	Func1();
	fun_ptr = &externalFunc;

	callExternalFunction(fun_ptr);
	getchar();
	return 0;
}

int test(long **testI)
{
	int deneme = 5;
	int *deneme2 = &deneme;
	*(deneme2 + 2) = 4;

	printf("%d\n", testI);
	printf("%p\n", &testI);
	testI = 12;

}


