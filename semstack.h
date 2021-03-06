//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// description: semantic stack definitions and declarations
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// structure Attribute
//
typedef struct
{
	int gElement;
	int length;
	int value;
	char* index;
	int place;
	char type;
	char* name;
	char* code;
	char* begin;
	char* after;
} Attribute;
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// structure SemStackNode
//
typedef struct sem_stack_node
{
	Attribute* attr;
	struct sem_stack_node* next;
} SemStackNode;
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// structure SemStack
//
typedef struct
{
	SemStackNode* head;
} SemStack;
///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// function declarations
//
SemStack* CreateSemStack();
void SemPush(SemStack** s, Attribute toPush);
SemStackNode* GetPtrTo(SemStack** s, int index);
void SemPop(SemStack** s);
void SemPopTo(SemStack** s, int index);
void PrintSemStack(SemStack* s);
int SemStackSize(SemStack* s);
Attribute InitAttr(int symbol);
//////////////////////////////////////////////////////////////
