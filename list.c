//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// description: this is a list ADT
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <list.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// global variable declarations
//
List* listHead = NULL;

//////////////////////////////////////////////////////////////
//
// AddToList(int toAdd)
//
// description: adds param toAdd onto the end of the list
//
void AddToList(int toAdd)
{
	if (listHead == NULL)
	{
		listHead = (List*)malloc(sizeof(List));
		listHead->data = toAdd;
		listHead->next = NULL;
	}

	else
	{
		List* temp = listHead;

		int i = 0;

		while(1)
		{
			if (listHead->next == NULL)
			{
				listHead->next = (List*)malloc(sizeof(List));
				listHead->next->data = toAdd;
				listHead->next->next = NULL;
				break;
			}

			i++;

			listHead = listHead->next;
		}

		listHead = temp;
	}
}
//
// end function AddToList(int)
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// RemoveFromList()
//
// description: removes last element from the list
// and returns its value
//
int RemoveFromList()
{
	if (listHead == NULL)
		return -1;

	if (listHead->next == NULL)
	{
		int result = listHead->data;
		free((void*)listHead);
		listHead = NULL;
		return result;
	}

	List* itr = listHead;

	while(1)
	{
		if (itr->next->next == NULL)
		{
			int result = itr->next->data;
			itr->next = NULL;
			return result;
		}

		itr = itr->next;
	}
}
//
// end RemoveFromList()
//////////////////////////////////////////////////////////////
