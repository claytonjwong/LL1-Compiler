//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// gen.c
// description: contains functions to generate intermediate
// code, which is a very long string, which gets concatentated
// together
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <strings.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SmartCat(char* a, char *b)
//
// description: this function works like strcat in the
// standard C library, however it first makes sure there
// is enough space in the destination for the concatentation
// of the things a and b into c, then returns c
//
char* SmartCat(char* a, char* b)
{
	char* c = (char*)malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
	if (c == NULL)
	{
		fprintf(stderr, "Out of memory.\n");
		exit(1);
	}

	c = strcpy(c, a);
	c = strcat(c, b);

	free((void*)a);

	return c;
}
//
// end SmartCat(char*, char*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// Gen(int n, ...)
//
// description: takes a variable amount of string arguments,
// and concatenates them into a single string, which is
// then returned
//
char* Gen(int n, ...)
{
	va_list ap;
	va_start(ap,n);
	char* result = "";

	int i = 0;

	while (i < n)
	{
		result = SmartCat(result, va_arg(ap, char*));
		i++;
	}

	va_end(ap);

	return result;
}
//
// end Gen(int, ...) function
//////////////////////////////////////////////////////////////
