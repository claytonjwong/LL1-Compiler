//////////////////////////////////////////////////////////////
//
// programmers: Jose Gifford and Clayton Wong
// lex_utils.c
// description: utilities used by lexical analyzer
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//

#include <lex_utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
//
// end header files
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// Error(char* msg)
//
// param msg is a string of characters to be printed in
// the error message
//
// description: prints msg to stderr and exits the program
//
void Error(char* msg)
{
	fprintf(stderr, msg);
	exit(1);
}
//
// end Error(char*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// isNumber(char c)
//
// param c is the character in query
//
// description: finds if c is a number
//
// returns: TRUE if c is a number, FALSE otherwise
//
Bool isNumber(char c)
{
	if ((c >= '0')
	 && (c <= '9'))
	{
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}
//
// end isNumber(char) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// isLetter(char c)
//
// param c is the character in query
//
// description: finds if c is a letter
//
// returns: TRUE if c is a letter, FALSE otherwise
//
Bool isLetter(char c)
{
	if (	((c >= 'A')	&& (c <= 'Z'))
	|| (c == '_')	)
	{
		return TRUE;
	}

	else
	if ((c >= 'a')
	 && (c <= 'z'))
	{
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}
//
// end isLetter(char) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// isTerminal(char c)
//
// param c is the character in query
//
// description: finds if c is a terminal
//
// returns: TRUE if c is a terminal, FALSE otherwise
//
Bool isTerminal(char c)
{
	return !isNumber(c) && !isLetter(c);
}
//
// end isTerminal(char) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// isWhitespace(char c)
//
// param c is the character in query
//
// description: finds if c is a whitespace character
//
// returns: TRUE is c is whitespace, FALSE otherwise
Bool isWhitespace(char c)
{
	if (c == ' '
	 || c == '\t'
	 || c == '\n')
	{ return TRUE; }
	else return FALSE;
}
//
// end isWhitespace(char) function
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//
// IsValidWord(Token*)
//
// checks is the token's name is a valid word
// for IDENTIFIER tokens
//
// param tokenToCheck is the token which should be an IDENTIFIER
// to have its name checked for validity
//
//
// returns TRUE if the IDENTIFIER tokenToCheck's name
// is a valid name, FALSE otherwise
//
// a valid name is based upon 2 things
//
// 1. the name must be either letters or numbers, or the underscore
// 2. the name must begin with a letter
//
Bool IsValidWord(Token* tokenToCheck)
{
	if (tokenToCheck->symbol != IDENTIFIER)
		return TRUE;

	char nameOfToken[13];

	strcpy(nameOfToken, tokenToCheck->name);

	char curr;
	int i=0;

	while(1)
	{
		curr = nameOfToken[i];

		if (curr == '\0')
			break;

		if (	(i == 0 && curr == '_')
		||		(i == 0 && isNumber(curr))
		   )
		{	return FALSE;  }

		else
		if (	(! isLetter(curr))
		&&		(! isNumber(curr))
		   )
		{	return FALSE;  }

		i++;
	}

	return TRUE;
}
//
// end CheckValidWord(Token*) function
//////////////////////////////////////////////////////////////
