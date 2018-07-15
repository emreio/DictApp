#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getStringPointer()
{
	char *pp = malloc(4 * sizeof(char));
	return pp;
}

void changeCharInString(char *pointer)
{
	if (pointer != NULL)
	{
		*(pointer + 4) = 'M';
	}


	//char *buffer[100];
	//char *buffer[100];
}

int *createIntPointer()
{
	int *p = malloc(sizeof(int));
	return p;
}

void Func1()
{
	char *word1 = "EMRE KANTAR";
	char *e;
	int index = word1;

	printf("%d \n", index);

	e = strchr(word1, 'X');

	if (e != NULL)
	{
		index = (int)(e - word1);
	}
	else
	{
		index = 0;
	}

	printf("Index : %d \n", index);

	char *p2 = NULL;
	p2 = getStringPointer();
	//int *p1 = 45;
	int *p1 = NULL;
	p1 = createIntPointer();
	*p1 = 5;

	FILE *myfile = fopen("deneme.txt", "r");

	if (myfile != NULL)
	{
		printf("dosya boþ deðil");
	}
	int i = 54;
	printf("pointer address %p\n", p1);
	printf("value : %d\n", *p1);

	p1 = &i;
	printf("pointer address : %p\n", p1);

	int myi = 54;

	printf("adres:  %p:", &myi);

	printf("value : %d\n", *p1);

	char *emre = "hello worldssss";
	char *word;
	word = malloc(12 * sizeof(char) + 1);
	strcpy(word, emre);
	if (p2 != NULL)
	{
		strcpy(p2, emre);
		*(p2 + 4) = 'E';
		printf(p2);
		printf("\n");
		changeCharInString(p2);
		printf(p2);
		printf("\n");
		*p2 = "naberrr";
		printf(p2);
		printf("\n");
	}
	printf("%p \n", word);
	printf(word);
	printf("\n");
}

void callExternalFunction(void(*func)())
{
	func();
}