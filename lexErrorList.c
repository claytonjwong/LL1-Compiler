#include <lex.h>
#include <lex_utils.h>
#include <lexErrorList.h>
#include <stdlib.h>
#include <string.h>

typedef struct lexErrorNode
{
	int line,position;
	char message[50];
	struct lexErrorNode *next;

}*lexErrorNode_ptr;


static lexErrorNode_ptr errorHead = NULL;


void lexErrorNodeInsert(int line, int position, char* message)
{
	lexErrorNode_ptr temp;
	if (errorHead == NULL)
	{
		errorHead = (lexErrorNode_ptr) malloc(sizeof(struct lexErrorNode));
		CASSERT(errorHead != NULL, "Out of memory!");
		strcpy(lexErrorNodePtrMessage(errorHead),message);
		lexErrorNodePtrLine(errorHead) = line;
		lexErrorNodePtrPostion(errorHead) = position;
		Next(errorHead) = NULL;

		return;
	}
	temp = errorHead;
	for(temp=errorHead;Next(temp)!=NULL;temp=Next(temp));

	Next(temp) = (lexErrorNode_ptr) malloc(sizeof(struct lexErrorNode));
	CASSERT(Next(temp) != NULL, "Out of memory!");

	strcpy(lexErrorNodePtrMessage(Next(temp)),message);
	lexErrorNodePtrLine(Next(temp)) = line;
	lexErrorNodePtrPostion(Next(temp)) = position;
	Next(Next(temp))=NULL;
	return;
}

void lexErrorPrintList(FILE* stream)
{
	int errorLine = 0;
	char buf;
	lexErrorNode_ptr temp = errorHead;

	while(temp!=NULL)
	{
		buf = getc(stream);
		fprintf(stdout,"%d ",errorLine);
		while(buf!='\n' && buf != EOF)
		{
			fprintf(stdout,"%c",buf);
			buf = getc(stream);
		}
		if(buf=='\n')
		{
			fprintf(stdout,"%c",buf);
			if(lexErrorNodePtrLine(temp) == errorLine + 1) // NICE OBO coding
			{
				fprintf(stdout,"\t%d %s\n",lexErrorNodePtrPostion(temp),lexErrorNodePtrMessage(temp)) ;
				temp=Next(temp);
			}
			errorLine++;

		}
		else if(buf == EOF)
			return;
	}
	while(buf!=EOF)
	{
		buf = getc(stream);
		fprintf(stdout,"%d ",errorLine);
		while(buf!='\n' && buf != EOF)
		{
			fprintf(stdout,"%c",buf);
			buf = getc(stream);
		}
		if(buf=='\n')
		{
			fprintf(stdout,"%c",buf);
			errorLine++;
		}
	}
}
