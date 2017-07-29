//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// description: this is a list ADT, which stores the basic
// information for IDENTIFIERS, and temporaries
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <idlist.h>
#include <stdlib.h>
#include <strings.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// CreateList()
//
// description: this function creates a new list by allocating
// memory dynamically for the list and returns a pointer to
// that list
//
IdList* CreateList()
{
	IdList* newlist = (IdList*)malloc(sizeof(IdList));
	newlist->head = NULL;
	return newlist;
}
//
// end function CreateList()
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// InsertToList(IdList** list , char* name, char type, int length)
//
// description: this function inserts a new element at the end
// of the list
//
void InsertToList(IdList** list, char* name, char type, int length, char* index, char* code)
{
	if ((*list)->head == NULL)
	{
		(*list)->head = (IdListNode*)malloc(sizeof(IdListNode));
		(*list)->head->name = strdup(name); //strcpy(l->head->idname, toInsert);
		(*list)->head->type = type;
		(*list)->head->length = length;
		(*list)->head->index = index;
		(*list)->head->code = code;
		(*list)->head->next = NULL;
	}

	else
	{
		IdListNode* itr = (*list)->head;

		while (itr != NULL && itr->next != NULL)
			itr = itr->next;

		itr->next = (IdListNode*)malloc(sizeof(IdListNode));
		itr->next->name = strdup(name); //strcpy(itr->next->idname, toInsert);
		itr->next->type = type;
		itr->next->length = length;
		itr->next->index = index;
		itr->next->code = code;
		itr->next->next = NULL;
	}
}
//
// end function InsertToList(IdList**, char*, char, int)
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// AppendToList(IdList** list, IdList* toAppend)
//
// description: this function appends param toAppend to the
// end of param list
//
void AppendToList(IdList** list, IdList* toAppend)
{
	IdListNode* itr;
	IdListNode* curr = toAppend->head;

	if (toAppend == NULL || toAppend->head == NULL)
		return;

	if ((*list)->head == NULL)
	{
		(*list)->head = (IdListNode*)malloc(sizeof(IdListNode));
		(*list)->head->name = curr->name;
		curr = curr->next;
	}

	itr = (*list)->head;

	while(itr != NULL && itr->next != NULL)
		itr = itr->next;

	while(curr != NULL)
	{
		itr->next = (IdListNode*)malloc(sizeof(IdListNode));
		itr->next->name = curr->name;
		itr->next->next = NULL;
		itr = itr->next;
		curr = curr->next;
	}
}
//
// end function AppendToList(IdList**, IdList*)
//////////////////////////////////////////////////////////////
