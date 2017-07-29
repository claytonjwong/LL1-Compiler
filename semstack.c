//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// description: this is a stack ADT, which is optimized
// for use of a semantic stack for a LL(1) parser
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <semstack.h>
//////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// CreateSemStack()
//
// description: this creates and initializes a semantic stack
// and returns a pointer to it
//
SemStack* CreateSemStack()
{
	SemStack* s = (SemStack*)malloc(sizeof(SemStack));
	s->head = NULL;
	return s;
}
//
// end CreateSemStack() function
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// SemPush(SemStack**, Attribute)
//
// description: pushes the attribute param toPush onto
// the top of the semantic stack param s
//
void SemPush(SemStack** s, Attribute toPush)
{
	//
	// case: first item pushed onto an empty stack
	//
	if ((*s)->head == NULL)
	{
		(*s)->head = (SemStackNode*)malloc(sizeof(SemStackNode));
		(*s)->head->attr = (Attribute*)malloc(sizeof(Attribute));
		(*s)->head->attr->gElement = toPush.gElement;
		(*s)->head->attr->length = toPush.length;
		(*s)->head->attr->name = strdup(toPush.name);
		(*s)->head->attr->code = strdup(toPush.code);
		(*s)->head->next = NULL;
	}

	//
	// case: additional item pushed onto a stack with
	// elements, make new item the head of the stack
	// and set it to point to the old head of the stack
	//
	else
	{
		SemStackNode* temp = (SemStackNode*)malloc(sizeof(SemStackNode));
		temp->attr = (Attribute*)malloc(sizeof(Attribute));
		temp->attr->gElement = toPush.gElement;
		temp->attr->length = toPush.length;
		temp->attr->name = strdup(toPush.name);
		temp->attr->code = strdup(toPush.code);

		SemStackNode* itr = (*s)->head;

		while(itr->next != NULL)
			itr=itr->next;

		itr->next = temp;
		temp->next = NULL;
	}

}
//
// end SemPush(SemStack**, Attribute) function
///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// GetPtrTo(SemStack** s, int index)
//
// description: returns a pointer to the node of the semantic
// stack which is in place "index"
//
// NOTE: the semantic stack's bottom most element is at index
// 1 not at index 0 for readability purposes
//
SemStackNode* GetPtrTo(SemStack** s, int index)
{
	int i = 0;
	SemStackNode* itr = (*s)->head;

	index--; // this will make the semantic stack
			 // seem to start at 1

	if (index < 0)
		return NULL;

	while(i < index)
	{
		if (itr == NULL)
			return NULL;
		if (itr == NULL || itr->next == NULL)
			return NULL;

		itr = itr->next;
		i++;
	}

	return itr;
}
//
// end GetPtrTo(SemStack**, int) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SemPop(SemStack** s)
//
// description: pops off the top element of the stack, by
// deallocating its memory and setting it to NULL
//
void SemPop(SemStack** s)
{
	if ((*s)->head == NULL)
	{
		return;
	}
	else
	if ((*s)->head->next == NULL)
	{
			free((void*)(*s)->head);
			(*s)->head = NULL;
	}
	else
	{
		SemStackNode* itr = (*s)->head;

		if (itr != NULL && itr->next != NULL
						&& itr->next->next != NULL)
		{
			while(itr->next->next != NULL)
			{
				itr = itr->next;
			}
		}

		free((void*)itr->next);
		itr->next = NULL;
	}
}
//
// end SemPop(SemStack**) function
//////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// SemPopTo(SemStack** s, int index)
//
// description: pops top elements off the stack up to
// and including the element at position param index
//
void SemPopTo(SemStack** s, int index)
{
	//
	// pop all the stack elements
	//
	if (index <= 0)
		index = 1;

	//
	// pop elements until index is reached,
	// pop off element at index inclusive
	//
	while(GetPtrTo(s, index) != NULL)
		SemPop(s);
}
//
// end SemPopTo(SemStack**, int) function
//////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// PrintSemStack(SemStack* s)
//
// description: prints the semantic stack, the top of the stack
// is the last element to be printed (highest #)
//
void PrintSemStack(SemStack* s)
{
	SemStackNode* itr;
	int i = 1;
	while(1)
	{
		itr = GetPtrTo(&s, i);

		if (itr == NULL)
			break;

		printf("         %d:\t %d\t%s\n", i, itr->attr->gElement, itr->attr->name);
		//printf("length   %d: %d\n", i, itr->attr->length);
		//printf("name     %d: %s\n", i, itr->attr->name);
		//printf("type     %d: %c\n", i, itr->attr->type);
		printf("code     %d: %s\n", i, itr->attr->code);
		i++;
	}
}
//
// end PrintSemStack(SemStack*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SemStackSize(SemStack* s)
//
// description: returns the size of the stack
//
int SemStackSize(SemStack* s)
{
	int size = 0;

	SemStackNode* itr = s->head;

	while(1)
	{
		if (itr == NULL)
			break;

		itr=itr->next;
		size++;
	}

	return size;
}
//
// end SemStackSize(SemStack*) function
//////////////////////////////////////////////////////////////
