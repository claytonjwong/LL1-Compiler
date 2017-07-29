#include <stdio.h>
#include <malloc.h>
#include <strings.h>

typedef struct idlist_node
{
	char* name;
	int value;
	struct idlist_node* next;
} IdListNode;

typedef struct
{
	IdListNode* head;
} IdList;


IdList* CreateList()
{
	IdList* newlist = (IdList*)malloc(sizeof(IdList));
	newlist->head = NULL;
	return newlist;
}


void InsertToList(IdList** list, char* name, int value)
{
	if ((*list)->head == NULL)
	{
		(*list)->head = (IdListNode*)malloc(sizeof(IdListNode));
		(*list)->head->name = strdup(name); //strcpy(l->head->idname, toInsert);
		(*list)->head->value = value;
		(*list)->head->next = NULL;
	}

	else
	{
		IdListNode* itr = (*list)->head;

		while (itr != NULL && itr->next != NULL)
			itr = itr->next;

		itr->next = (IdListNode*)malloc(sizeof(IdListNode));
		itr->next->name = strdup(name); //strcpy(itr->next->idname, toInsert);
		itr->next->value = value;
		itr->next->next = NULL;

	}
}

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
		(*list)->head->value = curr->value;
		curr = curr->next;
	}

	itr = (*list)->head;

	while(itr != NULL && itr->next != NULL)
		itr = itr->next;

	while(curr != NULL)
	{
		itr->next = (IdListNode*)malloc(sizeof(IdListNode));
		itr->next->name = curr->name;
		itr->next->value = curr->value;
		itr->next->next = NULL;
		itr = itr->next;
		curr = curr->next;
	}
}

int main()
{
	IdList* l = CreateList();

	InsertToList(&l, "hello", 1);
	InsertToList(&l, "hello", 2);
	InsertToList(&l, "hello", 3);

	IdList* l2 = CreateList();
	InsertToList(&l2, "there", 4);
	InsertToList(&l2, "buddy", 5);
	AppendToList(&l, l2);

	l2->head->name = "heinakin";
	printf("l2 head->name: %s\n", l2->head->name);


	IdListNode* itr = l->head;
	int i = 0;
	while(1)
	{
		if (itr == NULL)
			break;

		printf("%d: %s, %d\n", i, itr->name, itr->value);

		i++;
		itr = itr->next;

		if (itr == NULL)
			break;
	}

	return 0;
}
