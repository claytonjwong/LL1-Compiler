
//////////////////////////////////////////////////////////////
//
// programmers: Jose Gifford and Clayton Wong
// lex.c
// description: this is the lexical analyzer for the MINI_L complier
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// NOTE: array for identifiers needs to be length 13, even though
//       the longest identifier can be of length 8 because the
//		 beginprogram reserved word is length 12.
//
//  modifications performed to this size
//  in Token structure, GetToken function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <lex.h>
#include <lexErrorList.h>
#include <linkedlist.h>
#include <lex_utils.h>
//
// end header files
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// var line keeps track of the current line number
//
static int line = 1;

//////////////////////////////////////////////////////////////
// var currPos keeps track of the current position in the line
//
static int currPos = 1;

//////////////////////////////////////////////////////////////
// list or reserved words
//
char* reservedWord[] = { 	"program",
							"beginprogram",
							"endprogram",
							"array",
							"of",
							"integer",
							"if",
							"then",
							"else",
							"endif",
							"while",
							"loop",
							"endloop",
							"read",
							"write",
							"eof",
							"not",
							"and",
							"or",
							"true",
							"false"
				     	};


//////////////////////////////////////////////////////////////
// transition table -- shows what state to go to next
//
static int table[N_TRANS_TABLE_ROW][N_TRANS_TABLE_COL];
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// buffers
//
char buf1[SIZE_OF_BUF];
char buf2[SIZE_OF_BUF];
//
// current buffer
Bool isCurrFirstBuf;
//
//
// var fwd points to the end of the token in the buffer
char* fwd;
//
// end buffers
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// InitializeLexicalAnalysis(FILE* stream)
//
// param stream in the input file stream, which should be a
// source code file written in the MINI_L language
//
// description: this function itializes our double buffer,
// makes a call to setup the transition table based upon
// the finite automata of the MINI_L language syntax, and
// continues to parse tokens from the input file stream
// until the end of file is reached.
//
void InitializeLexicalAnalysis(FILE* stream)
{
	InitBuffs();
	LoadBuffer(stream);
	SetupTransitionTable();
}
//
// end InitializeLexicalAnalysis(FILE*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// InitBuffs()
//
// description: allocates memory for buffers, and initializes
// fwd to point to index 0 of buff1, sets isCurrFirstBuf to TRUE
//
void InitBuffs()
{
	fwd = buf1;

	isCurrFirstBuf = TRUE;
}
//
// end InitBuffs() function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// LoadBuffer(FILE* stream)
//
// param stream in the input file stream, which should be a
// source code file written in the MINI_L language
//
// description: loads the appropriate buffer with new data from
// the input stream and keeps track of the current buffer
// adds EOF to the end of the buffer to indicate the end of
// the buffer
//
void LoadBuffer(FILE* stream)
{
	int i;
	if (! isCurrFirstBuf)
	{
		//
		// input data from the stream
		//
		for (i=0; i < SIZE_OF_BUF - 2; i++)
			buf1[i] = getc(stream);

		//
		// add EOF and NULL to the end of the buffer
		//
		buf1[SIZE_OF_BUF - 2] = EOF;
		buf1[SIZE_OF_BUF - 1] = '\0';

		//
		// set current buffer to first
		//
		isCurrFirstBuf = TRUE;

		//
		// set fwd to point to the beginning
		// of the first buffer
		//
		fwd=&buf1[0];
	}

	else
	{
		//
		// input data from the stream
		//
		for (i=0; i < SIZE_OF_BUF - 2; i++)
			buf2[i] = getc(stream);

		//
		// add EOF and NULL to the end of the buffer
		//
		buf2[SIZE_OF_BUF - 2] = EOF;
		buf2[SIZE_OF_BUF - 1] = '\0';

		//
		// set current buffer to second
		//
		isCurrFirstBuf = FALSE;

		//
		// set fwd to point to the beginning
		// of the second buffer
		//
		fwd=&buf2[0];
	}
}
//
// end LoadBuffer(FILE*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// readComment(FILE* stream)
//
// param stream in the input file stream, which should be a
// source code file written in the MINI_L language
//
// description: this function reads, and disregards all
// characters, until the newline character is found, once
// the newline character is found, that is the end of the comment,
// then the function returns
//
void readComment(FILE* stream)
{
	//
	// continue through the input stream until the newline
	// character is found
	//
	while(*fwd != '\n')
	{
		fwd++;

		if (*fwd == EOF)
		{
			int i;

			//
			// see if it is the end of the file input stream
			// if so, exit
			//
			if (isCurrFirstBuf)
			{
				for(i=0; i<SIZE_OF_BUF - 2; i++)
					if(buf1[i]==EOF)
						return;
			}

			else
			{
				for(i=0; i<SIZE_OF_BUF - 2; i++)
					if(buf2[i]==EOF)
						return;
			}

			//
			// if its not the end of the file input stream,
			// and just the end of the buffer, load next
			// buffer
			//
			LoadBuffer(stream);
		}
	}
}
//
// end readComment(FILE*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SetTokenSymbol(Token *t, int state)
//
// param t is a pointer to the Token whose symbol is to be
// modified according to param state
//
// param state is the current state (which should be an
// accepting state), which the token was found to be in
//
// description: sets the token's symbol according to its state
// if the current token is in an error state,
// default token symbol to IDENTIFIER
//
void SetTokenSymbol(Token *t, int state)
{
	switch(state)
	{
		case ACCEPT_ID:
			t->symbol = IDENTIFIER;
			break;

		case ACCEPT_NUM:
			t->symbol = NUMBER;
			break;

		case ACCEPT_LT:
			t->symbol = LTSYM;
			break;

		case ACCEPT_GT:
			t->symbol = GTSYM;
			break;

		case ACCEPT_COLON:
			t->symbol = COLONSYM;
			break;

		case ACCEPT_NOTEQ:
			t->symbol = NOTEQSYM;
			break;

		case ACCEPT_LE:
			t->symbol = LESYM;
			break;

		case ACCEPT_GE:
			t->symbol = GESYM;
			break;

		case ACCEPT_ASSIGN:
			t->symbol = ASSIGNSYM;
			break;

		case ACCEPT_SEMI:
			t->symbol = SEMISYM;
			break;

		case ACCEPT_COMMA:
			t->symbol = COMMASYM;
			break;

		case ACCEPT_EQUAL:
			t->symbol = EQUALSYM;
			break;

		case ACCEPT_LPAR:
			t->symbol = LPARSYM;
			break;

		case ACCEPT_RPAR:
			t->symbol = RPARSYM;
			break;

		case ACCEPT_PLUS:
			t->symbol = PLUSSYM;
			break;

		case ACCEPT_MINUS:
			t->symbol = MINUSSYM;
			break;

		case ACCEPT_TIMES:
			t->symbol = TIMESSYM;
			break;

		case ACCEPT_DIV:
			t->symbol = DIVSYM;
			break;

		default:
			t->symbol = IDENTIFIER;
			break;
	}
}
//
// end SetTokenSymbol(Token*, int) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SetTokenValue(Token* t)
//
// param t is a pointer to the token which should be a NUMBER
//
// description: sets a token of symbol type NUMBER's value
// from its name
//
// ex: name: "100" of type string, then value: 100 of type int
//
void SetTokenValue(Token* t)
{
	if (t->symbol == NUMBER)
		t->value = (int)strtol(t->name, NULL, 10);
}
//
// end SetTokenValue(Token*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// GetToken(FILE* stream)
//
// param stream in the input file stream, which should be a
// source code file written in the MINI_L language
//
// description: reads characters from the file input stream
// through the buffers, which fwd points to.  These characters
// are then decifered through the transition table via state.
// Once the current state is an accepting state, the token
// has been found, and its symbol and value are set accordingly
//
// returns: a pointer to the next token read in
// from the file input stream
//
Token* GetToken(FILE* stream)
{
	Token* t = malloc(sizeof(Token));
	int currState = STATE_START;
	int charCount = 0;

	////////////////////////////////////////////////
	// BEGIN INPUT TOKEN
	//
	// continue to read until there is an error, or
	// the current state is an accepting state
	//
	while (currState != STATE_ERROR
	    && table[currState][ACCEPT_INPUT] == FALSE)
	{
		//
		// make sure the length of the token's name is within
		// acceptable domain boundry
		//
		if(charCount > ID_MAX_LENGTH)
		{
			lexErrorNodeInsert(line,
				currPos - strlen(t->name) - 1,
				"INVALID TOKEN ERROR, MAX LENGTH EXCEEDED\n");

			//
			// ignore the rest of the line
			//
			readComment(stream);

			//
			// start parsing tokens again
			//
			return GetToken(stream);
		}

		//
		// check to see if we are at the end of the input file stream
		// or just at the end of the buffer
		//
		if (*fwd == EOF)
		{
			int i;

			//
			// check for end of input file stream
			//
			if (isCurrFirstBuf)
			{
				for(i=0; i<SIZE_OF_BUF - 2; i++)
					if(buf1[i]==EOF)
						return NULL;
			}
			else
			{
				for(i=0; i<SIZE_OF_BUF - 2; i++)
					if(buf2[i]==EOF)
						return NULL;
			}

			//
			// if not at the end of input file stream
			// then we are at the end of a buffer
			// load next buffer and continue from
			// top of loop
			//
			LoadBuffer(stream);
			continue;
		}

		//////////////////////////////////////////////////////
		// begin input possibilities
		//
		if (! isWhitespace(*fwd))
			t->name[charCount] = *fwd;
		if (isLetter(*fwd))
			currState = table[currState][INPUT_LETTER];
		else
		if (isNumber(*fwd))
			currState = table[currState][INPUT_NUM];
		else
		if (*fwd == '<')
			currState = table[currState][INPUT_LT];
		else
		if (*fwd == '>')
			currState = table[currState][INPUT_GT];
		else
		if (*fwd == ':')
			currState = table[currState][INPUT_COLON];
		else
		if (*fwd == '=')
			currState = table[currState][INPUT_EQUAL];
		else
		if (*fwd == '(')
			currState = table[currState][INPUT_LPAR];
		else
		if (*fwd == ')')
			currState = table[currState][INPUT_RPAR];
		else
		if (*fwd == ';')
			currState = table[currState][INPUT_SEMI];
		else
		if (*fwd == ',')
			currState = table[currState][INPUT_COMMA];
		else
		if (*fwd == '+')
			currState = table[currState][INPUT_PLUS];
		else
		if (*fwd == '-')
		{
			currState = table[currState][INPUT_MINUS];

			if (currState == ACCEPT_COMMENT)
			{
				//
				// ignore the rest of the line
				//
				readComment(stream);

				//
				// start parsing tokens again
				//
				return GetToken(stream);
			}
		}
		else
		if (*fwd == '*')
			currState = table[currState][INPUT_TIMES];
		else
		if (*fwd == '/')
			currState = table[currState][INPUT_DIV];
		else
		if (*fwd == ' ')
			currState = table[currState][INPUT_SPACE];
		else
		if (*fwd == '\t')
			currState = table[currState][INPUT_TAB];
		else
		if (*fwd == '\n')
		{
			line++;
			currPos = 1;
			currState = table[currState][INPUT_NEWLINE];
		}
		else
		{
			currState = STATE_ERROR;

			lexErrorNodeInsert(line,
				currPos - strlen(t->name),
				"INVALID SYMBOL ERROR\n");

			//
			// ignore the rest of the line
			//
			readComment(stream);

			//
			// start parsing tokens again
			//
			return GetToken(stream);
		}

		//
		// end input possibilities
		//////////////////////////////////////////////////////


		//
		// NON-ACCEPTING STATE
		// increment the character count if fwd is not pointing
		// to whitespace, and increment fwd no matter what
		//
		if (table[currState][ACCEPT_INPUT] == FALSE)
		{
			//
			// only increment character count with non-white space
			//
			if (! isWhitespace(*fwd))
				charCount++;

			fwd++;

			if (currState != STATE_ERROR)
				currPos++;
		}

		//
		// ACCEPTING STATE
		// increment forward accordingly and set NULL character
		// and string delminiator accordingly
		//
		else
		{
			//
			// if the current character pointed to by fwd is
			// a terminal and the terminal IS NOT appended to
			// the end of another token, then increment fwd
			//
			if (isTerminal(*fwd) && charCount == 0)
				fwd++;

			//
			// if the current character pointed to by fwd is
			// a terminal and the terminal IS appended to
			// the end of another token, then set to end
			// of string character (\0)
			//
			else
				t->name[charCount] = '\0';

			//
			// increment fwd if LE, GE, ASSIGN, or NOTEQ is found
			//
			// EX: this makes it so that when "<=" is the input,
			// only LESYM is found, not both LESYM and EQUALSYM
			//
			if (currState == ACCEPT_LE
			 || currState == ACCEPT_GE
			 || currState == ACCEPT_ASSIGN
			 || currState == ACCEPT_NOTEQ)
			{ fwd++; }
		}
	}
	//
	// END INPUT TOKEN
	////////////////////////////////////////////////


	//
	// set token symbol according to accepting state
	//
	SetTokenSymbol(t, currState);

	//
	// set token value if the token is a NUMBER
	//
	if (t->symbol == NUMBER)
		SetTokenValue(t);

	//
	// see if the token is a reserved word if
	// token is an IDENTIFER
	//
	// AND
	//
	// make sure the token's name is valid
	//
	if (t->symbol == IDENTIFIER)
	{
		CheckReservedWord(t);

		if (! IsValidWord(t))
			lexErrorNodeInsert(line,
				currPos - strlen(t->name),
				"INVALID TOKEN ERROR\n");
	}

	//
	// return token
	//
	return t;
}
//
// end GetToken(FILE*) function
//////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////
//
// CheckReservedWord(Token* tokenToCheck)
//
// param tokenToCheck points to the token which should be
// an identifier, that will be checked to see if it
// is a reserved word,
//
// description: if tokenToCheck points to a token which
// has a name that is a reserved word, its symbol will be set
// according to that reserved word
//
void CheckReservedWord(Token* tokenToCheck)
{
	//
	// make sure the tokenToCheck is an IDENTIFIER
	//
	if (tokenToCheck->symbol != IDENTIFIER)
		return;

	char nameOfToken[ID_MAX_LENGTH];
	strcpy(nameOfToken, tokenToCheck->name);

	int x;

	for (x=0; x < numReservedWord; x++)
	{
		if (strcmp(nameOfToken, reservedWord[x]) == 0)
		{

			if (strcmp(reservedWord[x], "beginprogram") == 0)
				tokenToCheck->symbol = BEGPROGSYM;
			else
			if (strcmp(reservedWord[x], "program") == 0)
				tokenToCheck->symbol = PROGSYM;
			else
			if (strcmp(reservedWord[x], "endprogram") == 0)
				tokenToCheck->symbol = ENDPROGSYM;
			else
			if (strcmp(reservedWord[x], "array") == 0)
				tokenToCheck->symbol = ARRAYSYM;
			else
			if (strcmp(reservedWord[x], "of") == 0)
				tokenToCheck->symbol = OFSYM;
			else
			if (strcmp(reservedWord[x], "integer") == 0)
				tokenToCheck->symbol = INTSYM;
			else
			if (strcmp(reservedWord[x], "if") == 0)
				tokenToCheck->symbol = IFSYM;
			else
			if (strcmp(reservedWord[x], "then") == 0)
				tokenToCheck->symbol = THENSYM;
			else
			if (strcmp(reservedWord[x], "else") == 0)
				tokenToCheck->symbol = ELSESYM;
			else
			if (strcmp(reservedWord[x], "endif") == 0)
				tokenToCheck->symbol = ENDIFSYM;
			else
			if (strcmp(reservedWord[x], "while") == 0)
				tokenToCheck->symbol = WHILESYM;
			else
			if (strcmp(reservedWord[x], "loop") == 0)
				tokenToCheck->symbol = LOOPSYM;
			else
			if (strcmp(reservedWord[x], "endloop") == 0)
				tokenToCheck->symbol = ENDLOOPSYM;
			else
			if (strcmp(reservedWord[x], "read") == 0)
				tokenToCheck->symbol = READSYM;
			else
			if (strcmp(reservedWord[x], "write") == 0)
				tokenToCheck->symbol = WRITESYM;
			else
			if (strcmp(reservedWord[x], "eof") == 0)
				tokenToCheck->symbol = EOFSYM;
			else
			if (strcmp(reservedWord[x], "not") == 0)
				tokenToCheck->symbol = NOTSYM;
			else
			if (strcmp(reservedWord[x], "and") == 0)
				tokenToCheck->symbol = ANDSYM;
			else
			if (strcmp(reservedWord[x], "or") == 0)
				tokenToCheck->symbol = ORSYM;
			else
			if (strcmp(reservedWord[x], "true") == 0)
				tokenToCheck->symbol = TRUESYM;
			else
			if (strcmp(reservedWord[x], "false") == 0)
				tokenToCheck->symbol = FALSESYM;
		}
	}
}
//
// end CheckReservedWord(Token*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// SetupTransitionTable()
//
// description:  makes the transition table for the finite
// state machine transitions,
//
// rows are current state
// columns are the possible input characters
//
void SetupTransitionTable()
{
	int x;
	int y;

	///////////////////////////////////////////////////////
	//
	// STATE START
	//
	table[STATE_START][INPUT_LETTER] 	= STATE_ID;
	table[STATE_START][INPUT_NUM]		= STATE_NUM;
	table[STATE_START][INPUT_LT]		= STATE_LT;
	table[STATE_START][INPUT_GT]		= STATE_GT;
	table[STATE_START][INPUT_COLON]		= STATE_COLON;
	table[STATE_START][INPUT_MINUS]		= STATE_MINUS;
	table[STATE_START][INPUT_EQUAL]		= ACCEPT_EQUAL;
	table[STATE_START][INPUT_LPAR]		= ACCEPT_LPAR;
	table[STATE_START][INPUT_RPAR] 		= ACCEPT_RPAR;
	table[STATE_START][INPUT_SEMI]		= ACCEPT_SEMI;
	table[STATE_START][INPUT_COMMA]		= ACCEPT_COMMA;
	table[STATE_START][INPUT_PLUS]		= ACCEPT_PLUS;
	table[STATE_START][INPUT_TIMES]		= ACCEPT_TIMES;
	table[STATE_START][INPUT_DIV]		= ACCEPT_DIV;
	table[STATE_START][INPUT_SPACE]		= STATE_START;
	table[STATE_START][INPUT_TAB]		= STATE_START;
	table[STATE_START][INPUT_NEWLINE]	= STATE_START;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// STATE_ID
	//
	table[STATE_ID][INPUT_LETTER]	= STATE_ID;
	table[STATE_ID][INPUT_NUM]		= STATE_ID;
	//
	// other inputs besides letters or numbers
	//
	for (x = INPUT_LT; x <= INPUT_NEWLINE; x++)
		table[STATE_ID][x]	= ACCEPT_ID;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// STATE_NUM
	//
	table[STATE_NUM][INPUT_LETTER]		= STATE_ERROR;
	table[STATE_NUM][INPUT_NUM]			= STATE_NUM;
	//
	// other inputs besides numbers
	//
	for (x = INPUT_LT; x <= INPUT_NEWLINE; x++)
		table[STATE_NUM][x] = ACCEPT_NUM;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// STATE_LT
	//
	// accept LT for all inputs besides > and =
	//
	for (x = INPUT_LETTER; x <= INPUT_NEWLINE; x++)
		table[STATE_LT][x] = ACCEPT_LT;
	//
	table[STATE_LT][INPUT_GT] = ACCEPT_NOTEQ;
	table[STATE_LT][INPUT_EQUAL] = ACCEPT_LE;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// STATE_GT
	//
	// accept GT for all inputs besides =
	//
	for (x = INPUT_LETTER; x <= INPUT_NEWLINE; x++)
		table[STATE_GT][x] = ACCEPT_GT;
	//
	table[STATE_GT][INPUT_EQUAL] = ACCEPT_GE;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// STATE_COLON
	//
	// accept colon for all inputs besides =
	//
	for (x = INPUT_LETTER; x <= INPUT_NEWLINE; x++)
		table[STATE_COLON][x] = ACCEPT_COLON;
	//
	table[STATE_COLON][INPUT_EQUAL] = ACCEPT_ASSIGN;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// STATE_MINUS
	//
	// accept minus for all inputs besides -
	//
	for (x = INPUT_LETTER; x <= INPUT_NEWLINE; x++)
		table[STATE_MINUS][x] = ACCEPT_MINUS;
	//
	table[STATE_MINUS][INPUT_MINUS] = ACCEPT_COMMENT;
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////
	//
	// ACCEPTING STATES
	//
	// set all accepting state row's ACCEPT_INPUT column to TRUE
	// set all others to FALSE
	//
	for (y = STATE_START; y <= STATE_MINUS; y++)
		table[y][ACCEPT_INPUT] = FALSE;
	//
	for (y = ACCEPT_ID; y <= ACCEPT_COMMENT; y++)
		table[y][ACCEPT_INPUT] = TRUE;
	///////////////////////////////////////////////////////

}
//
// end SetupTransitionTable() function
//////////////////////////////////////////////////////////////
