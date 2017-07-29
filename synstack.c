///////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// SynSynStack.c
// description: this bad boy is an ADT stack, which is
// much, much better than Jose's ADT linked list!
//
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// header files
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <synstack.h>
#include <list.h>

char* GetGEString(int);
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// Shift(SynStack**, int n, ...)
//
// description: pushes n params onto the top of the stack,
// in reverse order
//
void Shift(SynStack** s, int n, ...)
{
	va_list ap;
	va_start(ap, n);

	int i = 0;
	while (i < n)
	{
		AddToList(va_arg(ap, int));
		i++;
	}

	int var = RemoveFromList();

	while (var != -1)
	{
		SynPush(s, var);
		var = RemoveFromList();
	}

	va_end(ap);
}
//
// end Shift(SynStack*, int, ...) function
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// SynPush(SynStack**, int)
//
// description: pushes param toPush onto the top of the stack
//
void SynPush(SynStack** s, int toPush)
{
	//
	// case: first item pushed onto an empty stack
	//
	if (*s == NULL)
	{
		*s = (SynStack*)malloc(sizeof(SynStack));
		(*s)->gElement = toPush;
		(*s)->next = NULL;
	}

	//
	// case: additional item pushed onto a stack with
	// elements, make new item the head of the stack
	// and set it to point to the old head of the stack
	//
	else
	{
		SynStack* temp = (SynStack*)malloc(sizeof(SynStack));
		temp->gElement = toPush;
		temp->next = *s;
		*s = temp;
	}
}
//
// end SynPush(SynStack**, int) function
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// Match(SynStack**, int)
//
// description: pops param toMatch off of the top of the stack
// returns TRUE if the token was matched and sucessfully
// popped off the stack, FALSE otherwise
//
Bool Match(SynStack** s, int toMatch)
{
	//
	// if there is something to pop off
	// and it matches Token param toMatch
	//
	if (*s != NULL && (*s)->gElement == toMatch)
	{
		SynStack* temp = (*s)->next;
		free((void*)*s);
		*s = temp;
		return TRUE;
	}

	return FALSE;
}
//
// end Match(SynStack**, int) function
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// SynPop(SynStack** s)
//
// description: pops the top element off of the stack
//
void SynPop(SynStack** s)
{
	if (*s != NULL)
	{
		SynStack* temp = (*s)->next;
		free((void*)*s);
		*s = temp;
	}
}
//
// end SynPop(SynStack**) function
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// Peek(SynStack* s)
//
// description: returns the Token on the top of the stack,
// NULL if the stack is empty
//
int Peek(SynStack* s)
{
	if (s != NULL)
		return s->gElement;
	else
		return -1;
}
//
// end Peek(SynStack*) function
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
//
// PrintSynStack(SynStack* s)
//
// prints out contents of stack
//
void PrintSynStack(SynStack* s)
{
	SynStack* top = s;

	int i = 0;

	printf("**********************************************\n");
	printf("* SynStack contents (top of stack on the left)...\n*\n");

	while (top != NULL)
	{
		printf("%d:\t %d\t %s\n", i, top->gElement, GetGEString(top->gElement));
		top = top->next;
		i++;
	}
	printf("\n*\n");
	printf("**********************************************\n");
}
//
// end PrintSynStack(SynStack*) function
///////////////////////////////////////////////////////////
