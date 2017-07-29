//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// description: symbol table ADT, used to keep track of
// declared and temporary variables
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <symtab.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// CreateSymtab()
//
// description: creates a new symbol table
//
SymTab* CreateSymTab()
{
	SymTab* st = (SymTab*)malloc(sizeof(SymTab));
	st->head = NULL;
	return st;
}

void InsertSymTab(SymTab** st, char* name, char dtype, int length)
{
	if ((*st)->head == NULL)
	{
		(*st)->head = (SymTabNode*)malloc(sizeof(SymTabNode));
		(*st)->head->name = strdup(name);
		(*st)->head->dtype = dtype;
		(*st)->head->length = length;
		(*st)->head->value = 0;
		(*st)->head->next = NULL;

	}

	else
	{
		SymTabNode* itr = (*st)->head;

		while(itr->next != NULL)
			itr=itr->next;

		itr->next = (SymTabNode*)malloc(sizeof(SymTabNode));
		itr = itr->next;
		itr->name = strdup(name);
		itr->dtype = dtype;
		itr->length = length;
		itr->value = 0;
		itr->next = NULL;
	}

	if (dtype == 'a')
	{
		int i;
		for (i=1; i < length; i++)
		{
			InsertSymTab(st, "", 'i', 1);
		}
	}
}
//
// end CreateSymTab() function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// GetName(SymTab* st, int index)
//
// description: returns the name of the element at param index
//
char* GetName(SymTab* st, int index)
{
	SymTabNode* itr = st->head;

	int i = 0;

	while(1)
	{
		if (itr == NULL)
			return "NOT FOUND";

		if (i == index)
			return strdup(itr->name);

		i++;
		itr=itr->next;
	}
}
//
// end GetName(SymTab*, int) function
//////////////////////////////////////////////////////////////


int GetPlace(SymTab* st, char* name)
{
	SymTabNode* itr = st->head;

	int i = 0;

	while(1)
	{
		if (itr==NULL)
			break;

		if (strcmp(itr->name, name) == 0)
			return i;
		else
		{
			itr = itr->next;
			i++;
		}
	}

	fprintf(stderr, "place not found!\n");
	exit(1);
	return -999;
}

//////////////////////////////////////////////////////////////
//
// GetVal(SymTab* st, char* name, int offset)
//
// description: returns the value of the element given its name
// and the offset, which is optional -- used with arrays
//
int GetVal(SymTab* st, char* name, int offset)
{
	SymTabNode* itr = st->head;

	while(1)
	{
		if (itr == NULL)
			break;
		else
		if (strcmp(itr->name, name) == 0)
		{
			if (offset == 0)
				return itr->value;
			else
			{
				while (offset > 0 && itr != NULL)
				{
					itr = itr->next;
					offset--;
				}

				if (itr != NULL)
					return itr->value;
			}
		}

		itr = itr->next;
	}

	fprintf(stderr, "Name not found in symbol table\n");
	exit(1);

	return -999;
}
//
// end GetVal(SymTab*, char*, int) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SetVal(SymTab** st, char* name, int offset, int value)
//
// description: modifies the element of the symbol table
// whose name is param name, offset is used with arrays.
//
void SetVal(SymTab** st, char* name, int offset, int value)
{
	SymTabNode* itr = (*st)->head;

	while(itr != NULL)
	{
		if (strcmp(itr->name, name) == 0)
		{
			int i=0;

			while (i < offset && itr != NULL)
			{
				i++;
				itr = itr->next;
			}

			if (itr != NULL)
				itr->value = value;

			break;
		}

		itr = itr->next;
	}
}
//
// end SetVal(SymTab**, char*, int, int) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// PrintSymTab(SymTab* st)
//
// description: prints the symbol table
//
void PrintSymTab(SymTab* st)
{
	SymTabNode* itr = st->head;

	int i = 0;

	printf("index:\tname\tdtype\tvalue\tlength\n");

	while(itr != NULL)
	{
		printf("%d:\t%s\t%c\t%d\t%d\n", i, itr->name, itr->dtype, itr->value, itr->length);
		itr = itr->next;
		i++;
	}
}
//
// end PrintSymTab(SymTab*) function
//////////////////////////////////////////////////////////////
