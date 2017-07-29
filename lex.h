///////////////////////////////////////////////////////
//
// programmer: Jose Gifford and Clayton Wong
// lex.h
// description: this bad boy has the declarations
// for the lexical analysis phase of the MINI_L complier
//
///////////////////////////////////////////////////////

#ifndef _LEX_H_
#define _LEX_H_
///////////////////////////////////////////////////////
// header files
//
#include <stdio.h>
//
// end header files
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Symbol enumerator
//
typedef enum
{IDENTIFIER, NUMBER, PROGSYM, BEGPROGSYM, ENDPROGSYM, ARRAYSYM, OFSYM, INTSYM, IFSYM, THENSYM, ELSESYM, 	ENDIFSYM, WHILESYM, LOOPSYM, ENDLOOPSYM, READSYM, WRITESYM, EOFSYM, NOTSYM, ANDSYM, ORSYM, TRUESYM, FALSESYM, SEMISYM, COMMASYM, COLONSYM, ASSIGNSYM, EQUALSYM, LPARSYM, RPARSYM, NOTEQSYM, LTSYM, GTSYM, LESYM, GESYM, PLUSSYM, MINUSSYM, TIMESSYM, DIVSYM} Symbol;
//
// end Symbol enum
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// reservedWord array
//
#define numReservedWord 21

// end reservedWord array
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// defintion for the maximum length of a token's name
//
#define ID_MAX_LENGTH	13
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// definition for the size of the buffers
#define SIZE_OF_BUF 10
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// begin transition table definitions
//
//
// table dimensions
//
#define N_TRANS_TABLE_ROW	26
#define N_TRANS_TABLE_COL 	19
//
// transition table states
//
#define STATE_ERROR		-1
#define STATE_START 	0
#define STATE_ID 		1
#define STATE_NUM		2
#define STATE_LT		3
#define STATE_GT		4
#define STATE_COLON	 	5
#define STATE_MINUS	 	6
#define ACCEPT_ID		7
#define ACCEPT_NUM		8
#define ACCEPT_LT		9
#define ACCEPT_GT		10
#define ACCEPT_COLON	11
#define ACCEPT_NOTEQ 	12
#define ACCEPT_LE		13
#define ACCEPT_GE		14
#define ACCEPT_ASSIGN	15
#define ACCEPT_SEMI	 	16
#define ACCEPT_COMMA	17
#define ACCEPT_EQUAL	18
#define ACCEPT_LPAR	 	19
#define ACCEPT_RPAR	 	20
#define ACCEPT_PLUS	 	21
#define ACCEPT_MINUS	22
#define ACCEPT_TIMES	23
#define ACCEPT_DIV		24
#define ACCEPT_COMMENT  25
//
// transition table inputs
//
#define INPUT_LETTER 	0
#define INPUT_NUM		1
#define INPUT_LT		2
#define INPUT_GT		3
#define INPUT_COLON	 	4
#define INPUT_EQUAL	 	5
#define INPUT_LPAR		6
#define INPUT_RPAR		7
#define INPUT_SEMI		8
#define INPUT_COMMA	 	9
#define INPUT_PLUS		10
#define INPUT_MINUS	 	11
#define INPUT_TIMES	 	12
#define INPUT_DIV		13
#define INPUT_SPACE	 	14
#define INPUT_TAB		15
#define INPUT_NEWLINE	16
#define INPUT_OTHER	 	17
#define ACCEPT_INPUT	18
//
// end transition table definitions
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// Token structure
//
typedef struct
{
	Symbol symbol;
	int value;
	char name[ID_MAX_LENGTH];
} Token;
// end Token structure
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// begin Jose's definitions
//
#define TSymbol(x)  (x.symbol)
#define TValue(x)  	(x.value)
#define TName(x)	(x.name)
//
// end Jose's defintions
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// function declarations
//
void InitBuffs();
void LoadBuffer(FILE* stream);
Token* GetToken(FILE* stream);
void CheckReservedWord(Token* tokenToCheck);
void SetupTransitionTable();
void Error(char* msg);
void SetTokenSymbol(Token *t, int state);
void SetTokenValue(Token *t);
void InitializeLexicalAnalysis(FILE* stream);


//
// end function declarations
///////////////////////////////////////////////////////


#define Next(x)         ((x)->next)
#define ERROR(msg) { fprintf(stderr, "%s\n", (msg)); exit(-1); }
#define CASSERT(cond, msg) { if (!(cond)) ERROR(msg); }


//////////////////////////////////////////////////////////////
// Bool enumerator
//
typedef enum { FALSE, TRUE } Bool;
//////////////////////////////////////////////////////////////

#define lexErrorNodePtrMessage(x) 	(x->message)
#define lexErrorNodePtrLine(x)	 	(x->line)
#define lexErrorNodePtrPostion(x) 	(x->position)
#define Datum(x)     	(x->datum)

//////////////////////////////////////////////////////////////
// Node_ptr structure
//
typedef struct Node
{
	Token datum;
	struct Node *next;
}*Node_ptr;



#endif
