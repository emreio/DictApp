#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

void externalFunc()
{
	printf("i am external \n");
}

int main()
{
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
