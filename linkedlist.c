//////////////////////////////////////////////////////////////
//
// programmer: Jose Gifford
// description: this is a linked list ADT
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <lex.h>
#include <lex_utils.h>
#include <linkedlist.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// global variable declarations
//
Node_ptr head;
static int count=-1;
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// Insert(Token* datum)
//
// description: appends token to end of list
//
void Insert(Token* datum)
{
	count++;
	Node_ptr temp;
	if (head == NULL)
	{
		head = (Node_ptr) malloc(sizeof(struct Node));
		CASSERT(head != NULL, "Out of memory!");
		Datum(head)=*datum;
		Next(head)=NULL;
		return;
	}
	temp = head;
	for(temp=head;Next(temp)!=NULL;temp=Next(temp));

	Next(temp) = (Node_ptr) malloc(sizeof(struct Node));
	CASSERT(Next(temp) != NULL, "Out of memory!");
	Datum(Next(temp))=*datum;
	Next(Next(temp))=NULL;
	return;

}
//
// end Insert(Token*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// PrintList()
//
// prints the tokens in the list
//
void PrintList()
{
	Node_ptr temp = head;
	int i=0;
	while (temp!=NULL)
	{

		fprintf(stdout,"%d\t",i);
		char symbol[50];

		switch(TSymbol( Datum(temp) ))
		{
			case  IDENTIFIER:
			strcpy(symbol,"IDENTIFIER");
			break;

			case  NUMBER:
			strcpy(symbol,"NUMBER");
			break;

			case  PROGSYM:
			strcpy(symbol,"PROGSYM");
			break;

			case  BEGPROGSYM:
			strcpy(symbol,"BEGPROGSYM");
			break;

			case  ENDPROGSYM:
			strcpy(symbol,"ENDPROGSYM");
			break;

			case  ARRAYSYM:
			strcpy(symbol,"ARRAYSYM");
			break;

			case  OFSYM:
			strcpy(symbol,"OFSYM");
			break;

			case  INTSYM:
			strcpy(symbol,"INTSYM");
			break;

			case  IFSYM:
			strcpy(symbol,"IFSYM");
			break;

			case  THENSYM:
			strcpy(symbol,"THENSYM");
			break;

			case  ELSESYM:
			strcpy(symbol,"ELSESYM");
			break;

			case  ENDIFSYM:
			strcpy(symbol,"ENDIFSYM");
			break;

			case  WHILESYM:
			strcpy(symbol,"WHILESYM");
			break;

			case  LOOPSYM:
			strcpy(symbol,"LOOPSYM");
			break;

			case  ENDLOOPSYM:
			strcpy(symbol,"ENDLOOPSYM");
			break;

			case  READSYM:
			strcpy(symbol,"READSYM");
			break;

			case  WRITESYM:
			strcpy(symbol,"WRITESYM");
			break;

			case  EOFSYM:
			strcpy(symbol,"EOFSYM");
			break;

			case  NOTSYM:
			strcpy(symbol,"NOTSYM");
			break;

			case  ANDSYM:
			strcpy(symbol,"ANDSYM");
			break;

			case  ORSYM:
			strcpy(symbol,"ORSYM");
			break;

			case  TRUESYM:
			strcpy(symbol,"TRUESYM");
			break;

			case  FALSESYM:
			strcpy(symbol,"FALSESYM");
			break;

			case  SEMISYM:
			strcpy(symbol,"SEMISYM");
			break;

			case  COMMASYM:
			strcpy(symbol,"COMMASYM");
			break;

			case  COLONSYM:
			strcpy(symbol,"COLONSYM");
			break;

			case  ASSIGNSYM:
			strcpy(symbol,"ASSIGNSYM");
			break;

			case  EQUALSYM:
			strcpy(symbol,"EQUALSYM");
			break;

			case  LPARSYM:
			strcpy(symbol,"LPARSYM");
			break;

			case  RPARSYM:
			strcpy(symbol,"RPARSYM");
			break;

			case  NOTEQSYM:
			strcpy(symbol,"NOTEQSYM");
			break;

			case  LTSYM:
			strcpy(symbol,"LTSYM");
			break;

			case  GTSYM:
			strcpy(symbol,"GTSYM");
			break;

			case  LESYM:
			strcpy(symbol,"LESYM");
			break;

			case  GESYM:
			strcpy(symbol,"GESYM");
			break;

			case  PLUSSYM:
			strcpy(symbol,"PLUSSYM");
			break;

			case  MINUSSYM:
			strcpy(symbol,"MINUSSYM");
			break;

			case  TIMESSYM:
			strcpy(symbol,"TIMESSYM");
			break;

			case  DIVSYM:
			strcpy(symbol,"DIVSYM");
			break;

			default:
			strcpy(symbol,"ERROR");
			break;
	}

	//
	// output information
	//
	fprintf(stdout,"%s",symbol);
	if(strcasecmp(symbol,"IDENTIFIER") == 0)
		fprintf(stdout," %s",TName(Datum(temp)) );
	else
	if (strcasecmp(symbol, "NUMBER") == 0)
		fprintf(stdout, " %d", TValue(Datum(temp)) );

	fprintf(stdout,"\n");
	temp = Next(temp);
	i++;
	}
}
//
// end PrintList() function
//////////////////////////////////////////////////////////////

