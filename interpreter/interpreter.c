//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// interpreter.c
// description: this is a virtual machine environment which
// performs MINI_L intermediate code
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <symtab.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// global constant definitions
//
#define 	MAX_LINE_LEN	80
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// CodeElement structure
//
typedef struct code_element
{
	char* code;
	struct code_element* next;
} CodeElement;
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// CodeArrayElement
//
typedef struct code_array
{
	CodeElement* head;
} CodeArray;
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// AssimilateCodeToArray(FILE* stream, CodeArray** ca)
//
// description: reads a line at a time from stream, and inserts
// that line read as a string element in ca
//
void AssimilateCodeToArray(FILE* stream, CodeArray** ca)
{
	char buf[MAX_LINE_LEN];

	CodeElement* curr = NULL;

	while(fgets(buf, MAX_LINE_LEN, stream) != NULL)
	{

		if ((*ca)->head == NULL)
		{
			(*ca)->head = (CodeElement*)malloc(sizeof(CodeElement));
			(*ca)->head->code = (char*)malloc(sizeof(char) * strlen(buf) + 1);
			(*ca)->head->code = strcpy((*ca)->head->code, buf);
			(*ca)->head->next = NULL;

			curr = (*ca)->head;
		}

		else
		{
			curr->next = (CodeElement*)malloc(sizeof(CodeElement));
			curr = curr->next;
			curr->code = (char*)malloc(sizeof(char) * strlen(buf) + 1);
			curr->code = strcpy(curr->code, buf);
			curr->next = NULL;
		}
	}
}
//
// end AssimilateCodeToArray(FILE*, CodeArray**) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// IsLabel(char* codeLine)
//
// description: param codeLine is a line of MINI_L
// intermediate code.  returns -1 if the param codeLine
// is a not a label, or is the label "Start"
// returns the value of the label otherwise.
//
// i.e.: given codeLine = ": L23", returns integer val 23
//
int IsLabel(char* codeLine)
{
	char* code = strdup(codeLine);

	char* tok = strtok(code, " \t");

	if (strcmp(tok, ":") == 0)
	{
		tok = strtok(NULL, " \t\nL");

		if (strcmp(tok, "Start") == 0)
			return -1;

		return (int)strtol(tok, NULL, 10);
	}
	else
		return -1;
}
//
// end IsLabel(char*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// PerformCode(CodeArray* ca)
//
// description: interprets and performs the intermediate code
// which is stored in param ca
//
void PerformCode(CodeArray* ca)
{
	CodeElement* pc = ca->head;
	SymTab* st = CreateSymTab();

	while(pc != NULL)
	{
		char* curr = strdup(pc->code);
		char* op = strtok(curr, " \t");

		if (strcmp(op, ".") == 0)
		{
			char* name = strtok(NULL, " \t\n");
			InsertSymTab(&st, name, 'i', 0);
		}
		else
		if (strcmp(op, ".[]") == 0)
		{
			char* name = strtok(NULL, " \t,");
			char* sLength = strtok(NULL, " \n");
			int iLength = (int)strtol(sLength, NULL, 10);

			InsertSymTab(&st, name, 'a', iLength);
		}
		else
		if (strcmp(op, "=") == 0)
		{
			char* dst = strtok(NULL, " \t,");
			char* src = strtok(NULL, " \n");

			//
			// immediate value
			//
			if (GetPlace(st, src) == -1)
			{
				int immVal = (int)strtol(src, NULL, 10);
				SetVal(&st, dst, 0, immVal);
			}
			else
			{
				int srcVal = GetVal(st, src, 0);
				SetVal(&st, dst, 0, srcVal);
			}
		}
		else
		if (strcmp(op, "=[]") == 0)
		{
			char* dst = strtok(NULL, " \t,");
			char* src = strtok(NULL, " \t,");
			char* sIndex = strtok(NULL, " \n");

			//
			// immediate value
			//
			if (GetPlace(st, sIndex) == -1)
			{
				int iIndex = (int)strtol(sIndex, NULL, 10);
				int srcVal = GetVal(st, src, iIndex);
				SetVal(&st, dst, 0, srcVal);
			}
			else
			{
				int iIndex = GetVal(st, sIndex, 0);
				int srcVal = GetVal(st, src, iIndex);
				SetVal(&st, dst, 0, srcVal);
			}
		}
		else
		if (strcmp(op, "[]=") == 0)
		{
			char* dst = strtok(NULL, " \t,");
			char* sIndex = strtok(NULL, " \t,");
			char* src = strtok(NULL, " \n");

			int iIndex;
			int srcVal;

			//
			// immediate value for index
			//
			if (GetPlace(st, sIndex) == -1)
			{
				iIndex = (int)strtol(sIndex, NULL, 10);
			}
			else
			{
				iIndex = GetVal(st, sIndex, 0);
			}

			//
			// immediate value for src
			//
			if (GetPlace(st, src) == -1)
			{
				srcVal = (int)strtol(src, NULL, 10);
			}
			else
			{
				srcVal = GetVal(st, src, 0);
			}

			SetVal(&st, dst, iIndex, srcVal);
		}
		else
		if(strcmp(op, ".<") == 0)
		{
			char* dst = strtok(NULL, " \n");

			printf("%s ?= ", dst);

			char buf[MAX_LINE_LEN];

			fgets(buf, MAX_LINE_LEN, stdin);

			char *end;
			int val = (int)strtol(buf, &end, 10);

			if (strcmp(end, "\n") != 0)
			{
				fprintf(stderr, "Invalid number input.\n");
				exit(1);
			}
			else
			{
				SetVal(&st, dst, 0, val);
			}
		}
		else
		if (strcmp(op, ".[]<") == 0)
		{
			char* dst = strtok(NULL, " \t,");
			char* sIndex = strtok(NULL, " \n");

			int iIndex;

			//
			// immediate value for index
			//
			if (GetPlace(st, sIndex) == -1)
			{
				iIndex = (int)strtol(sIndex, NULL, 10);
			}
			else
			{
				iIndex = GetVal(st, sIndex, 0);
			}

			printf("%s[%d] ?= ", dst, iIndex);

			char buf[MAX_LINE_LEN];

			fgets(buf, MAX_LINE_LEN, stdin);

			char *end;
			int val = (int)strtol(buf, &end, 10);

			if (strcmp(end, "\n") != 0)
			{
				fprintf(stderr, "Invalid number input.\n");
				exit(1);
			}
			else
			{
				SetVal(&st, dst, iIndex, val);
			}
		}
		else
		if (strcmp(op, ".>") == 0)
		{
			char* src = strtok(NULL, " \n");

			int srcVal = GetVal(st, src, 0);

			printf("%s: %d\n", src, srcVal);
		}
		else
		if (strcmp(op, ".[]>") == 0)
		{
			char* src = strtok(NULL, " \t,");
			char* sIndex = strtok(NULL, " \n");

			int iIndex;
			int srcVal;

			//
			// immediate value for index
			//
			if (GetPlace(st, sIndex) == -1)
			{
				iIndex = (int)strtol(sIndex, NULL, 10);
			}
			else
			{
				iIndex = GetVal(st, sIndex, 0);
			}

			srcVal = GetVal(st, src, iIndex);

			printf("%s[%d]: %d\n", src, iIndex, srcVal);
		}
		else
		if (strcmp(op, "+") == 0
		||  strcmp(op, "-") == 0
		||  strcmp(op, "*") == 0
		||  strcmp(op, "/") == 0
		||  strcmp(op, "%") == 0
		||  strcmp(op, "<") == 0
		||  strcmp(op, "<=") == 0
		||  strcmp(op, "!=") == 0
		||  strcmp(op, "==") == 0
		||  strcmp(op, ">=") == 0
		||  strcmp(op, ">") == 0
		||  strcmp(op, "||") == 0
		||  strcmp(op, "&&") == 0)
		{
			char* dst = strtok(NULL, " \t,");
			char* src1 = strtok(NULL, " \t,");
			char* src2 = strtok(NULL, " \n");

			int src1Val;
			int src2Val;
			int val;

			//
			// immediate src1 value
			//
			if (GetPlace(st, src1) == -1)
			{
				src1Val = (int)strtol(src1, NULL, 10);
			}
			else
			{
				src1Val = GetVal(st, src1, 0);
			}

			//
			// immediate src2 value
			//
			if (GetPlace(st, src2) == -1)
			{
				src2Val = (int)strtol(src2, NULL, 10);
			}
			else
			{
				src2Val = GetVal(st, src2, 0);
			}

			if (strcmp(op, "+") == 0)
			{
				val = src1Val + src2Val;
			}
			else
			if (strcmp(op, "-") == 0)
			{
				val = src1Val - src2Val;
			}
			else
			if (strcmp(op, "*") == 0)
			{
				val = src1Val * src2Val;
			}
			else
			if (strcmp(op, "/") == 0)
			{
				val = src1Val / src2Val;
			}
			else
			if (strcmp(op, "%") == 0)
			{
				val = src1Val % src2Val;
			}
			else
			if (strcmp(op, "<") == 0)
			{
				if (src1Val < src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, "<=") == 0)
			{
				if (src1Val <= src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, "!=") == 0)
			{
				if (src1Val != src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, "==") == 0)
			{
				if (src1Val == src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, ">=") == 0)
			{
				if (src1Val >= src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, ">") == 0)
			{
				if (src1Val > src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, "||") == 0)
			{
				if (src1Val || src2Val)
					val = 1;
				else
					val = 0;
			}
			else
			if (strcmp(op, "&&") == 0)
			{
				if (src1Val && src2Val)
					val = 1;
				else
					val = 0;
			}

			SetVal(&st, dst, 0, val);
		}
		else
		if (strcmp(op, "!") == 0)
		{
			char* dst = strtok(NULL, " \t,");
			char* src = strtok(NULL, " \n");

			int srcVal;
			int val;

			//
			// immediate src value
			//
			if (GetPlace(st, src) == -1)
			{
				srcVal = (int)strtol(src, NULL, 10);
			}
			else
			{
				srcVal = GetVal(st, src, 0);
			}

			if (srcVal == 0)
				val = 1;
			else
				val = 0;

			SetVal(&st, dst, 0, val);
		}
		else
		if (strcmp(op, ":=") == 0)
		{
			char* label = strtok(NULL, " \tL\n");
			int labelNum = (int)strtol(label, NULL, 10);

			CodeElement* temp = ca->head;

			while (IsLabel(temp->code) != labelNum)
			{
				temp = temp->next;
			}

			pc = temp;
			continue;
		}
		else
		if (strcmp(op, "?:=") == 0)
		{
			char* label = strtok(NULL, " \tL,");
			char* pred = strtok(NULL, " \n");

			int labelNum = (int)strtol(label, NULL, 10);
			int predVal = GetVal(st, pred, 0);

			if (predVal)
			{
				CodeElement* temp = ca->head;

				while(IsLabel(temp->code) != labelNum)
				{
					temp = temp->next;
				}

				pc = temp;
				continue;
			}
		}

		pc = pc->next;
	}
}
//
// end PerformCode(CodeArray*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// main
//
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
			fprintf(stderr, "Unable to open input file.\n");
	}
	else
	{
		fprintf(stderr, "Usage: ml <input>\n");
		exit(1);
	}

	CodeArray* ca = (CodeArray*)malloc(sizeof(CodeArray));
	ca->head = NULL;

	AssimilateCodeToArray(inFile, &ca);

	PerformCode(ca);

	return 0;
}
//
// end main function
//////////////////////////////////////////////////////////////
