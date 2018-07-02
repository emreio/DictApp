#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

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

int main()
{

	char *path = getenv("HOME");
	//printf(path);

     #ifdef __APPLE__
	 printf("platform : osx \n");
	 #else
	 printf("not osx \n");
	 #endif
return 7;
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
