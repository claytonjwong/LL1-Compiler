//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// interpreter.c
// description: this is a virtual machine environment which
// performs MINI_L intermediate code
//
//////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	////////////////////////////////////////
	// open input file (MINI_L intermediate code)
	//
	FILE* inFile = NULL;

	if (optind == argc - 1) // then there is an extra argument
	{
		inFile = fopen(argv[argc - 1], "r");

		if (inFile == NULL)
			Error("Unable to open input file.\n");
	}
	else
	{
		fprintf(stderr, "\n\nUsage: ml <input>\n");
		printf("\tinput\t\t\tthe MINI_L intermediate code file.\n\n\n");
	}

	return 0;
}
