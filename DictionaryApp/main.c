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
const char* TurkishLocaleName = "turkish";

typedef struct
{
	char *key;
	char *value;
}Dictionary;


int compare(const void *p, const void *p1)
{
	setlocale(LC_ALL, TurkishLocaleName);
	Dictionary v1 = *(Dictionary *)p;
	Dictionary v2 = *(Dictionary *)p1;

	return strcmp(v1.key, v2.key);
}

int main()
{
	setlocale(LC_ALL, TurkishLocaleName);

	char *searchKey;
	char line[100];
	int lang = -1;
	int num_ok;

	int lineCount = 0;

	FILE *dictionaryFile = openFileForRead(InitialFileName);
	FILE *turkishFile = createNewFileForWrite(TurkishDictFileName);
	FILE *englishFile = createNewFileForWrite(EnglishDictFileName);

	if (dictionaryFile == NULL)
	{
		perror("Error opening file");
		getchar();
		exit(-1);
	}

	lineCount = getLinesCount(dictionaryFile);
	printf("sozluk.txt'deki sat�r say�s�: %d \n", lineCount);
	Dictionary* dictionary = malloc(sizeof(Dictionary) * lineCount);

	int i = 0;
	char *buffer[256];
	char *dictionaryLine;
	char *token1;
	int tokenLength = 0;
	char *readline;
	char *readlineKey[256];
	char *readlineValue[256];

	while (!feof(dictionaryFile))
	{
		readline = fgets(buffer, 256, dictionaryFile);

		if (readline == NULL) continue;

		int _Strlen = strlen(buffer);

		dictionaryLine = malloc(_Strlen + 1);

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

	qsort(dictionary, lineCount, sizeof(Dictionary), compare);

	for (int j = 0; j < lineCount; j++)
	{
		if (j == lineCount - 1)
		{
			fputs(dictionary[j].key, turkishFile);
			fputs(dictionary[j].value, englishFile);
		}

		else
		{
			fputs(strcat(dictionary[j].key, "\n"), turkishFile);
			fputs(strcat(dictionary[j].value, "\n"), englishFile);
		}
	}

	printf("S�zl�k dosyalar� olu�turuldu. \n");

	fclose(turkishFile);
	fclose(englishFile);
	fclose(dictionaryFile);

	while (true)
	{
		int keyFileSearchIndex = 0;
		int valueFileSearchIndex = 0;

		printf("L�tfen arama yapmak istedi�iniz dil se�imini yap�n�z. 1: T�rk�e || 2: �ngilizce \n");

		fgets(line, sizeof line, stdin);
		num_ok = sscanf(line, "%d", &lang);

		if (!num_ok)
		{
			printf("Yanl�� se�im girdiniz. \n");
			continue;
		}

		if (lang == 1)
		{
			printf("T�rk�e se�tiniz. \n");
		}

		else if (lang == 2)
		{
			printf("�ngilizce se�tiniz. \n");
		}

		else
		{
			printf("Yanl�� se�im girdiniz. \n");
			continue;
		}

		printf("l�tfen aramak istedi�iniz kelimeyi giriniz: \n");

		fgets(line, sizeof line, stdin);

		int _len1 = strlen(line);

		searchKey = malloc(_len1);

		strcpy(searchKey, line);

		if (searchKey[_len1 - 1] == '\n')
			searchKey[_len1 - 1] = '\0';

		printf("girdi�iniz kelime : %s \n", searchKey);

		FILE* _keyFile;
		FILE* _valueFile;

		if (lang == 1)
		{
			_keyFile = openFileForRead(TurkishDictFileName);
			_valueFile = openFileForRead(EnglishDictFileName);
		}

		else
		{
			_keyFile = openFileForRead(EnglishDictFileName);
			_valueFile = openFileForRead(TurkishDictFileName);
		}


		if (_keyFile == NULL || _valueFile == NULL)
		{
			perror("dosya okunamad�, programdan ��k�l�yor.");
			break;
		}

		char *foundKey;
		char *foundValue;
		int keyFound = -1;

		while (!feof(_keyFile) && fgets(readlineKey, 256, _keyFile))
		{
			keyFound = -1;
			keyFileSearchIndex++;

			int _len = strlen(readlineKey);

			foundKey = malloc(_len);

			strcpy(foundKey, readlineKey);

			if (foundKey[_len - 1] == '\n')
				foundKey[_len - 1] = '\0';

			if (strcmp(foundKey, searchKey) == 0)
			{
				if (lang == 1)
				{
					printf("turkce.txt dosyas�nda arad���n�z %s kelimesi %d. kelimedir. \n", searchKey, keyFileSearchIndex);
				}

				else
				{
					printf("ingilizce.txt dosyas�nda arad���n�z %s kelimesi %d. kelimedir. \n", searchKey, keyFileSearchIndex);
				}

				while (!feof(_valueFile) && fgets(readlineValue, 256, _valueFile))
				{
					valueFileSearchIndex++;

					if (valueFileSearchIndex == keyFileSearchIndex)
					{
						int _len = strlen(readlineValue);

						foundValue = malloc(_len);

						strcpy(foundValue, readlineValue);

						if (foundValue[_len - 1] == '\n')
							foundValue[_len - 1] = '\0';

						printf("%s kelimesinin karsiligi %s'dir \n", foundKey, foundValue);

						break;
					}
				}
				keyFound = 1;
				break;
			}
		}
		if (keyFound == -1)
		{
			if (lang == 1)
			{
				printf("girdi�iniz %s kelimesi turkce.txt'de bulunamad�. \n", searchKey);
			}

			else
			{
				printf("girdi�iniz %s kelimesi ingilizce.txt'de bulunamad�. \n", searchKey);
			}
		}

		continue;
	}

	getchar();
}


