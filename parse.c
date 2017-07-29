//////////////////////////////////////////////////////////////
//
// Programmer: Clayton Wong
//
// parse.c
//
// description: this file contains functions used for the
// MINI_L LL(1) parser
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// header files
//
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <parse.h>
#include <linkedlist.h>
#include <semstack.h>
#include <lex.h>
#include <idlist.h>
#include <gen.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// temp lists
//
static IdList* idList = NULL;
static IdList* varList = NULL;
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// ProduceToSynStack(SynStack**s, SemStack**, int prodNum, type_eop* eop, Bool printProd)
//
// description: replaces the nonterminal on the top of the
// stack with the production given from param prodNum by
// popping the top  of the stack off, and pushing the production
// onto the stack in reverse order
//
// NOTE: if the production -> @ then the non-terminal
// at the top of the stack is popped off, and nothing
// is shifted onto the stack
//
void ProduceToSynStack(SynStack** s, SemStack** s2, int prodNum, type_eop* eop, Bool printProd)
{
	//
	// pop top off
	//
	SynPop(s);

	//
	// push eop onto the syntax stack
	//
	PushEOP(s, eop);

	//
	// push production number onto the syntax stack
	//
	SynPush(s, prodNum + MARKER_OFFSET);

	//
	// Shift new production onto stack
	//
	switch(prodNum)
	{
		//
		// Program -> program id ; Block endprogram
		//
		case 0:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s %s %s\n",
					GetGEString(TGE_PROGRAM),
					GetGEString(TGE_ID),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_BLOCK),
					GetGEString(TGE_ENDPROGRAM)
				);
			}

			//
			// put production onto the syntax stack
			//
			Shift(s,
				  5,
				  TGE_PROGRAM, TGE_ID, TGE_SEMI, NGE_BLOCK, TGE_ENDPROGRAM);

			//
			// put production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_PROGRAM));
			SemPush(s2, InitAttr(TGE_ID));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_BLOCK));
			SemPush(s2, InitAttr(TGE_ENDPROGRAM));

			break;
		}

		//
		// Block -> Declaration ; Declarations beginprogram Statement ; Statements
		//
		case 1:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s %s %s %s %s\n",
					GetGEString(NGE_DECLARATION),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_DECLARATIONS),
					GetGEString(TGE_BEGINPROGRAM),
					GetGEString(NGE_STATEMENT),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_STATEMENTS)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  7,
				  NGE_DECLARATION, TGE_SEMI, NGE_DECLARATIONS,
				  TGE_BEGINPROGRAM, NGE_STATEMENT, TGE_SEMI,
				  NGE_STATEMENTS);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_DECLARATION));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_DECLARATIONS));
			SemPush(s2, InitAttr(TGE_BEGINPROGRAM));
			SemPush(s2, InitAttr(NGE_STATEMENT));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_STATEMENTS));

			break;
		}

		//
		// Declarations -> Declaration ; Declarations
		//
		case 2:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(NGE_DECLARATION),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_DECLARATIONS)
				);
			}

			//
			// push production onto the stack
			//
			Shift(s,
				  3,
				  NGE_DECLARATION, TGE_SEMI, NGE_DECLARATIONS);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_DECLARATION));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_DECLARATIONS));

			break;
		}

		//
		// Declarations -> @
		//
		case 3:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// Declaration -> id Ids : Type
		//
		case 4:
		{

			if (printProd == TRUE)
			{
				printf("%s %s %s %s\n",
					GetGEString(TGE_ID),
					GetGEString(NGE_IDS),
					GetGEString(TGE_COLON),
					GetGEString(NGE_TYPE)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_ID, NGE_IDS, TGE_COLON, NGE_TYPE);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_ID));
			SemPush(s2, InitAttr(NGE_IDS));
			SemPush(s2, InitAttr(TGE_COLON));
			SemPush(s2, InitAttr(NGE_TYPE));

			break;
		}

		//
		// Ids -> , id Ids
		//
		case 5:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_COMMA),
					GetGEString(TGE_ID),
					GetGEString(NGE_IDS)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  TGE_COMMA, TGE_ID, NGE_IDS);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_COMMA));
			SemPush(s2, InitAttr(TGE_ID));
			SemPush(s2, InitAttr(NGE_IDS));

			break;
		}

		//
		// Ids -> @
		//
		case 6:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// Type -> integer
		//
		case 7:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_INTEGER)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_INTEGER);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_INTEGER));

			break;
		}

		//
		// Type -> array ( num ) of integer
		//
		case 8:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s %s %s %s\n",
					GetGEString(TGE_ARRAY),
					GetGEString(TGE_LPAR),
					GetGEString(TGE_NUM),
					GetGEString(TGE_RPAR),
					GetGEString(TGE_OF),
					GetGEString(TGE_INTEGER)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  6,
				  TGE_ARRAY, TGE_LPAR, TGE_NUM, TGE_RPAR, TGE_OF, TGE_INTEGER);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_ARRAY));
			SemPush(s2, InitAttr(TGE_LPAR));
			SemPush(s2, InitAttr(TGE_NUM));
			SemPush(s2, InitAttr(TGE_RPAR));
			SemPush(s2, InitAttr(TGE_OF));
			SemPush(s2, InitAttr(TGE_INTEGER));

			break;
		}

		//
		// Statements -> Statement ; Statements
		//
		case 9:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(NGE_STATEMENT),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_STATEMENTS)
				);
			}

			//
			// push production onto syntax stack
			//
			Shift(s,
				  4,
				  NGE_STATEMENT, TGE_SEMI, M9_1, NGE_STATEMENTS);

			//
			// push production onto semantic stack
			//
			SemPush(s2, InitAttr(NGE_STATEMENT));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_STATEMENTS));

			break;
		}

		//
		// Statements -> @
		//
		case 10:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}


			break;
		}

		//
		// Statement -> Var := Exp
		//
		case 11:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(NGE_VAR),
					GetGEString(TGE_ASSIGN),
					GetGEString(NGE_EXP)
				);
			}

			//
			// push production onto syntax stack
			//
			Shift(s,
				  3,
				  NGE_VAR, TGE_ASSIGN, NGE_EXP);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_VAR));
			SemPush(s2, InitAttr(TGE_ASSIGN));
			SemPush(s2, InitAttr(NGE_EXP));

			break;
		}

		//
		// Statement -> if BExp the Statement ; Statements Else endif
		//
		case 12:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s %s %s %s %s %s\n",
					GetGEString(TGE_IF),
					GetGEString(NGE_BEXP),
					GetGEString(TGE_THEN),
					GetGEString(NGE_STATEMENT),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_STATEMENTS),
					GetGEString(NGE_ELSE),
					GetGEString(TGE_ENDIF)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
			      8,
			      TGE_IF, NGE_BEXP, TGE_THEN, NGE_STATEMENT, TGE_SEMI,
			      NGE_STATEMENTS, NGE_ELSE, TGE_ENDIF);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_IF));
			SemPush(s2, InitAttr(NGE_BEXP));
			SemPush(s2, InitAttr(TGE_THEN));
			SemPush(s2, InitAttr(NGE_STATEMENT));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_STATEMENTS));
			SemPush(s2, InitAttr(NGE_ELSE));
			SemPush(s2, InitAttr(TGE_ENDIF));

			break;
		}

		//
		// Statement -> while BExp loop Statement ; Statements endloop
		//
		case 13:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s %s %s %s %s\n",
					GetGEString(TGE_WHILE),
					GetGEString(NGE_BEXP),
					GetGEString(TGE_LOOP),
					GetGEString(NGE_STATEMENT),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_STATEMENTS),
					GetGEString(TGE_ENDLOOP)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  7,
				  TGE_WHILE, NGE_BEXP, TGE_LOOP, NGE_STATEMENT,
				  TGE_SEMI, NGE_STATEMENTS, TGE_ENDLOOP);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_WHILE));
			SemPush(s2, InitAttr(NGE_BEXP));
			SemPush(s2, InitAttr(TGE_LOOP));
			SemPush(s2, InitAttr(NGE_STATEMENT));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_STATEMENTS));
			SemPush(s2, InitAttr(TGE_ENDLOOP));

			break;
		}

		//
		// Statement -> read Vars
		//
		case 14:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(TGE_READ),
					GetGEString(NGE_VARS)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  2,
				  TGE_READ, NGE_VARS);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_READ));
			SemPush(s2, InitAttr(NGE_VARS));

			break;
		}

		//
		// Statement -> write Vars
		//
		case 15:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(TGE_WRITE),
					GetGEString(NGE_VARS)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  2,
				  TGE_WRITE, NGE_VARS);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_WRITE));
			SemPush(s2, InitAttr(NGE_VARS));

			break;
		}

		//
		// Else -> else Statement ; Statements
		//
		case 16:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s %s\n",
					GetGEString(TGE_ELSE),
					GetGEString(NGE_STATEMENT),
					GetGEString(TGE_SEMI),
					GetGEString(NGE_STATEMENTS)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_ELSE, NGE_STATEMENT, TGE_SEMI,
				  NGE_STATEMENTS);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_ELSE));
			SemPush(s2, InitAttr(NGE_STATEMENT));
			SemPush(s2, InitAttr(TGE_SEMI));
			SemPush(s2, InitAttr(NGE_STATEMENTS));

			break;
		}

		//
		// Else -> @
		//
		case 17:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// BExp -> RExp BExp_1
		//
		case 18:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(NGE_REXP),
					GetGEString(NGE_BEXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  NGE_REXP, M18_1, NGE_BEXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_REXP));
			SemPush(s2, InitAttr(NGE_BEXP_1));

			break;
		}

		//
		// BExp_1 -> and RExp BExp_1
		//
		case 19:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_AND),
					GetGEString(NGE_REXP),
					GetGEString(NGE_BEXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_AND, NGE_REXP, M19_1, NGE_BEXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_AND));
			SemPush(s2, InitAttr(NGE_REXP));
			SemPush(s2, InitAttr(NGE_BEXP_1));

			break;
		}

		//
		// BExp_1 -> or RExp BExp_1
		//
		case 20:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_OR),
					GetGEString(NGE_REXP),
					GetGEString(NGE_BEXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_OR, NGE_REXP, M20_1, NGE_BEXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_OR));
			SemPush(s2, InitAttr(NGE_REXP));
			SemPush(s2, InitAttr(NGE_BEXP_1));

			break;
		}

		//
		// BExp_1 -> @
		//
		case 21:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// RExp -> not RExp_1
		//
		case 22:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(TGE_NOT),
					GetGEString(NGE_REXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  2,
				  TGE_NOT, NGE_REXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_NOT));
			SemPush(s2, InitAttr(NGE_REXP_1));

			break;
		}

		//
		// RExp -> RExp_1
		//
		case 23:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(NGE_REXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  NGE_REXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_REXP_1));

			break;
		}

		//
		// RExp_1 -> Exp Comp Exp
		//
		case 24:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(NGE_EXP),
					GetGEString(NGE_COMP),
					GetGEString(NGE_EXP)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  NGE_EXP, NGE_COMP, NGE_EXP);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_EXP));
			SemPush(s2, InitAttr(NGE_COMP));
			SemPush(s2, InitAttr(NGE_EXP));

			break;
		}

		//
		// RExp_1 -> true
		//
		case 25:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_TRUE)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_TRUE);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_TRUE));

			break;
		}

		//
		// RExp_1 -> false
		//
		case 26:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_FALSE)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_FALSE);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_FALSE));

			break;
		}

		//
		// Comp -> =
		//
		case 27:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_EQUAL)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_EQUAL);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_EQUAL));

			break;
		}

		//
		// Comp -> <>
		//
		case 28:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_NOTEQUAL)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_NOTEQUAL);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_NOTEQUAL));

			break;
		}

		//
		// Comp -> <
		//
		case 29:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_LT)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_LT);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_LT));

			break;
		}

		//
		// Comp -> >
		//
		case 30:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_GT)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_GT);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_GT));

			break;
		}

		//
		// Comp -> <=
		//
		case 31:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_LE)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_LE);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_LE));

			break;
		}

		//
		// Comp -> >=
		//
		case 32:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_GE)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_GE);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_GE));

			break;
		}

		//
		// Exp -> Term Exp_1
		//
		case 33:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(NGE_TERM),
					GetGEString(NGE_EXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  NGE_TERM, M33_1, NGE_EXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_TERM));
			SemPush(s2, InitAttr(NGE_EXP_1));

			break;
		}

		//
		// Exp -> - Term Exp_1
		//
		case 34:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_MINUS),
					GetGEString(NGE_TERM),
					GetGEString(NGE_EXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_MINUS, NGE_TERM, M34_1, NGE_EXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_MINUS));
			SemPush(s2, InitAttr(NGE_TERM));
			SemPush(s2, InitAttr(NGE_EXP_1));

			break;
		}

		//
		// Exp_1 -> + Term Exp_1
		//
		case 35:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_PLUS),
					GetGEString(NGE_TERM),
					GetGEString(NGE_EXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_PLUS, NGE_TERM, M35_1, NGE_EXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_PLUS));
			SemPush(s2, InitAttr(NGE_TERM));
			SemPush(s2, InitAttr(NGE_EXP_1));

			break;
		}

		//
		// Exp_1 -> - Term Exp_1
		//
		case 36:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_MINUS),
					GetGEString(NGE_TERM),
					GetGEString(NGE_EXP_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_MINUS, NGE_TERM, M36_1, NGE_EXP_1);
			//Shift(s,
			//	  3,
			//	  TGE_MINUS, NGE_TERM, NGE_EXP_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_MINUS));
			SemPush(s2, InitAttr(NGE_TERM));
			SemPush(s2, InitAttr(NGE_EXP_1));

			break;
		}

		//
		// Exp_1 -> @
		//
		case 37:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// Term -> Factor Term_1
		//
		case 38:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(NGE_FACTOR),
					GetGEString(NGE_TERM_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  NGE_FACTOR, M38_1, NGE_TERM_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_FACTOR));
			SemPush(s2, InitAttr(NGE_TERM_1));

			break;
		}

		//
		// Term_1 -> * Factor Term_1
		//
		case 39:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_TIMES),
					GetGEString(NGE_FACTOR),
					GetGEString(NGE_TERM_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_TIMES, NGE_FACTOR, M39_1, NGE_TERM_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_TIMES));
			SemPush(s2, InitAttr(NGE_FACTOR));
			SemPush(s2, InitAttr(NGE_TERM_1));

			break;
		}

		//
		// Term_1 -> / Factor Term_1
		//
		case 40:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_DIV),
					GetGEString(NGE_FACTOR),
					GetGEString(NGE_TERM_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_DIV, NGE_FACTOR, M40_1, NGE_TERM_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_DIV));
			SemPush(s2, InitAttr(NGE_FACTOR));
			SemPush(s2, InitAttr(NGE_TERM_1));

			break;
		}

		//
		// Term_1 -> @
		//
		case 41:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// Factor -> Var
		//
		case 42:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(NGE_VAR)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  NGE_VAR);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_VAR));

			break;
		}

		//
		// Factor -> num
		//
		case 43:
		{
			if (printProd == TRUE)
			{
				printf("%s\n",
					GetGEString(TGE_NUM)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  1,
				  TGE_NUM);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_NUM));

			break;
		}

		//
		// Factor -> ( Exp )
		//
		case 44:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_LPAR),
					GetGEString(NGE_EXP),
					GetGEString(TGE_RPAR)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  TGE_LPAR, NGE_EXP, TGE_RPAR);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_LPAR));
			SemPush(s2, InitAttr(NGE_EXP));
			SemPush(s2, InitAttr(TGE_RPAR));

			break;
		}

		//
		// Vars -> Var Vars_1
		//
		case 45:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(NGE_VAR),
					GetGEString(NGE_VARS_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  NGE_VAR, M45_1, NGE_VARS_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(NGE_VAR));
			SemPush(s2, InitAttr(NGE_VARS_1));

			break;
		}

		//
		// Vars_1 -> , Var Vars_1
		//
		case 46:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_COMMA),
					GetGEString(NGE_VAR),
					GetGEString(NGE_VARS_1)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  4,
				  TGE_COMMA, NGE_VAR, M46_1, NGE_VARS_1);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_COMMA));
			SemPush(s2, InitAttr(NGE_VAR));
			SemPush(s2, InitAttr(NGE_VARS_1));

			break;
		}

		//
		// Vars_1 -> @
		//
		case 47:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		//
		// Var -> id Var_1
		//
		case 48:
		{
			if (printProd == TRUE)
			{
				printf("%s %s\n",
					GetGEString(TGE_ID),
					GetGEString(NGE_VAR_1)
				);
			}

			//
			// push production onto syntax stack
			//
			Shift(s,
				  2,
				  TGE_ID, NGE_VAR_1);

			//
			// push production onto semantic stack
			//
			SemPush(s2, InitAttr(TGE_ID));
			SemPush(s2, InitAttr(NGE_VAR_1));

			break;
		}

		//
		// Var_1 -> ( Exp )
		//
		case 49:
		{
			if (printProd == TRUE)
			{
				printf("%s %s %s\n",
					GetGEString(TGE_LPAR),
					GetGEString(NGE_EXP),
					GetGEString(TGE_RPAR)
				);
			}

			//
			// push production onto the syntax stack
			//
			Shift(s,
				  3,
				  TGE_LPAR, NGE_EXP, TGE_RPAR);

			//
			// push production onto the semantic stack
			//
			SemPush(s2, InitAttr(TGE_LPAR));
			SemPush(s2, InitAttr(NGE_EXP));
			SemPush(s2, InitAttr(TGE_RPAR));

			break;
		}

		//
		// Var_1 -> @
		//
		case 50:
		{
			if (printProd == TRUE)
			{
				printf("@\n");
			}

			break;
		}

		default:
			printf("prodNum: %d\n", prodNum);
			Error("Parse Error3.\n");
	}
}
//
// end ProduceToSynStack(SynStack**, SemStack**, int, type_eop*, Bool) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// InitializeParseTable()
//
// description: sets up the parse table according to the
// first and follow sets of the grammar for the MINI_L language
//
// NOTE: the rows of the table are nonterminals
// 		 the cols of the table are terminals
//
void InitializeParseTable()
{
	int t, n; // terminals and nonterminals

	//
	// set all to -1 to indicate error
	//
	for (n=0; n < N_NONTERMINAL; n++)
		for (t=0; t < N_TERMINAL; t++)
			parseTable[n][t] = -1;

	//
	// Program
	//
	parseTable[NGE_PROGRAM - NON_TERM_OFFSET][TGE_PROGRAM] = 0;

	//
	// Block
	//
	parseTable[NGE_BLOCK - NON_TERM_OFFSET][TGE_ID] = 1;

	//
	// Declarations
	//
	parseTable[(NGE_DECLARATIONS - NON_TERM_OFFSET)][(TGE_ID)] 					= 2;
	parseTable[(NGE_DECLARATIONS - NON_TERM_OFFSET)][(TGE_BEGINPROGRAM)] 		= 3;

	//
	// Declaration
	//
	parseTable[NGE_DECLARATION - NON_TERM_OFFSET][TGE_ID] = 4;

	//
	// Ids
	//
	parseTable[NGE_IDS - NON_TERM_OFFSET][TGE_COMMA] = 5;
	parseTable[NGE_IDS - NON_TERM_OFFSET][TGE_COLON] = 6;

	//
	// Type
	//
	parseTable[NGE_TYPE - NON_TERM_OFFSET][TGE_INTEGER] 	= 7;
	parseTable[NGE_TYPE - NON_TERM_OFFSET][TGE_ARRAY] 		= 8;

	//
	// Statements
	//
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_ID] 			= 9;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_IF] 			= 9;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_WHILE] 		= 9;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_READ] 			= 9;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_WRITE] 		= 9;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_ENDPROGRAM] 	= 10;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_ELSE] 			= 10;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_ENDLOOP] 		= 10;
	parseTable[NGE_STATEMENTS - NON_TERM_OFFSET][TGE_ENDIF] 		= 10;

	//
	// Statement
	//
	parseTable[NGE_STATEMENT - NON_TERM_OFFSET][TGE_ID] 		= 11;
	parseTable[NGE_STATEMENT - NON_TERM_OFFSET][TGE_IF] 		= 12;
	parseTable[NGE_STATEMENT - NON_TERM_OFFSET][TGE_WHILE] 		= 13;
	parseTable[NGE_STATEMENT - NON_TERM_OFFSET][TGE_READ] 		= 14;
	parseTable[NGE_STATEMENT - NON_TERM_OFFSET][TGE_WRITE] 		= 15;

	//
	// Else
	//
	parseTable[NGE_ELSE - NON_TERM_OFFSET][TGE_ELSE] 	= 16;
	parseTable[NGE_ELSE - NON_TERM_OFFSET][TGE_ENDIF] 	= 17;

	//
	// BExp
	//
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_ID] 		= 18;
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_NUM] 	= 18;
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_NOT] 	= 18;
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_LPAR] 	= 18;
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_MINUS] 	= 18;
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_TRUE]	= 18;
	parseTable[NGE_BEXP - NON_TERM_OFFSET][TGE_FALSE]	= 18;

	//
	// BExp_1
	//
	parseTable[NGE_BEXP_1 - NON_TERM_OFFSET][TGE_AND] 	= 19;
	parseTable[NGE_BEXP_1 - NON_TERM_OFFSET][TGE_OR]	= 20;
	parseTable[NGE_BEXP_1 - NON_TERM_OFFSET][TGE_THEN]	= 21;
	parseTable[NGE_BEXP_1 - NON_TERM_OFFSET][TGE_LOOP]	= 21;


	//
	// RExp
	//
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_NOT] 	= 22;
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_MINUS] 	= 23;
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_NUM]		= 23;
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_LPAR]	= 23;
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_ID]		= 23;
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_TRUE]	= 23;
	parseTable[NGE_REXP - NON_TERM_OFFSET][TGE_FALSE] 	= 23;

	//
	// RExp_1
	//
	parseTable[NGE_REXP_1 - NON_TERM_OFFSET][TGE_MINUS] 	= 24;
	parseTable[NGE_REXP_1 - NON_TERM_OFFSET][TGE_NUM]		= 24;
	parseTable[NGE_REXP_1 - NON_TERM_OFFSET][TGE_LPAR]		= 24;
	parseTable[NGE_REXP_1 - NON_TERM_OFFSET][TGE_ID]		= 24;
	parseTable[NGE_REXP_1 - NON_TERM_OFFSET][TGE_TRUE]		= 25;
	parseTable[NGE_REXP_1 - NON_TERM_OFFSET][TGE_FALSE] 	= 26;

	//
	// Comp
	//
	parseTable[NGE_COMP - NON_TERM_OFFSET][TGE_EQUAL]		= 27;
	parseTable[NGE_COMP - NON_TERM_OFFSET][TGE_NOTEQUAL]	= 28;
	parseTable[NGE_COMP - NON_TERM_OFFSET][TGE_LT]			= 29;
	parseTable[NGE_COMP - NON_TERM_OFFSET][TGE_GT]			= 30;
	parseTable[NGE_COMP - NON_TERM_OFFSET][TGE_LE]			= 31;
	parseTable[NGE_COMP - NON_TERM_OFFSET][TGE_GE]			= 32;

	//
	// Exp
	//
	parseTable[NGE_EXP - NON_TERM_OFFSET][TGE_MINUS]		= 34;
	parseTable[NGE_EXP - NON_TERM_OFFSET][TGE_NUM]			= 33;
	parseTable[NGE_EXP - NON_TERM_OFFSET][TGE_LPAR]			= 33;
	parseTable[NGE_EXP - NON_TERM_OFFSET][TGE_ID]			= 33;

	//
	// Exp_1
	//
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_PLUS]		= 35;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_MINUS]		= 36;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_SEMI]		= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_RPAR]		= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_EQUAL]		= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_NOTEQUAL]	= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_LT]			= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_GT]			= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_LE]			= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_GE]			= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_AND]		= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_OR]			= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_THEN]		= 37;
	parseTable[NGE_EXP_1 - NON_TERM_OFFSET][TGE_LOOP]		= 37;

	//
	// Term
	//
	parseTable[NGE_TERM - NON_TERM_OFFSET][TGE_NUM]		= 38;
	parseTable[NGE_TERM - NON_TERM_OFFSET][TGE_ID]		= 38;
	parseTable[NGE_TERM - NON_TERM_OFFSET][TGE_LPAR]	= 38;

	//
	// Term_1
	//
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_TIMES]		= 39;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_DIV]		= 40;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_PLUS]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_MINUS]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_SEMI]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_RPAR]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_EQUAL]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_NOTEQUAL]	= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_LT]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_GT]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_LE]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_GE]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_AND]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_OR]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_THEN]		= 41;
	parseTable[NGE_TERM_1 - NON_TERM_OFFSET][TGE_LOOP]		= 41;

	//
	// Factor
	//
	parseTable[NGE_FACTOR - NON_TERM_OFFSET][TGE_ID]		= 42;
	parseTable[NGE_FACTOR - NON_TERM_OFFSET][TGE_NUM]		= 43;
	parseTable[NGE_FACTOR - NON_TERM_OFFSET][TGE_LPAR]		= 44;

	//
	// Vars
	//
	parseTable[NGE_VARS - NON_TERM_OFFSET][TGE_ID]		= 45;

	//
	// Vars_1
	//
	parseTable[NGE_VARS_1 - NON_TERM_OFFSET][TGE_COMMA]	= 46;
	parseTable[NGE_VARS_1 - NON_TERM_OFFSET][TGE_SEMI]	= 47;

	//
	// Var
	//
	parseTable[NGE_VAR - NON_TERM_OFFSET][TGE_ID]		= 48;

	//
	// Var_1
	//
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_LPAR]		= 49;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_TIMES]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_DIV]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_ASSIGN]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_SEMI]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_RPAR]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_EQUAL]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_NOTEQUAL]	= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_LT]			= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_GT]			= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_LE]			= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_GE]			= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_AND]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_OR]			= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_THEN]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_ELSE]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_PLUS]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_MINUS]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_LOOP]		= 50;
	parseTable[NGE_VAR_1 - NON_TERM_OFFSET][TGE_COMMA]		= 50;
}
//
// end InitializeParseTable() function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// PrintParseTable()
//
// description: prints the parse table to standard output
//
void PrintParseTable()
{
	int i,n,t;

	t = N_TERMINAL;

	printf("\t\t");
	for (i=0; i < t; i++)
	{
		if (i < 10 && i != 0)
			printf(" ");

		printf(" %d", i);
	}

	printf("\n");

	for (n=0; n < N_NONTERMINAL; n++)
	{
		if (strcmp(GetGEString(n + NON_TERM_OFFSET), "Declarations") == 0)
			printf("Declarations\t");
		else
		if (strcmp(GetGEString(n + NON_TERM_OFFSET), "Declaration") == 0)
			printf("Declaration\t");
		else
		if (strcmp(GetGEString(n + NON_TERM_OFFSET), "Statements") == 0)
			printf("Statements\t");
		else
		if (strcmp(GetGEString(n + NON_TERM_OFFSET), "Statement") == 0)
			printf("Statement\t");
		else
			printf("%s\t\t", GetGEString(n + NON_TERM_OFFSET));

		for (t=0; t < N_TERMINAL; t++)
		{
			if (parseTable[n][t] < 10 && parseTable[n][t] != -1)
				printf(" ");
			printf("%d ", parseTable[n][t]);
		}

		printf("\n");
	}
}
//
// end PrintParseTable() function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// PerformSemanticRule(SemStack* semStack, SymTab* st, type_eop* eop,
//		int marker, SynStack* synStack)
//
// description: whenever a marker is on the top of the syntax
// stack, this function should be called to perform the semantics
// associated with that marker in the current production
//
void PerformSemanticRule(SemStack* semStack, SymTab* st, type_eop* eop,
	int marker, SynStack* synStack)
{
	//
	// apply semantic rule based upon which
	// end of production the marker stands for
	// i.e. M0 is at the end of production 0
	//
	switch(marker)
	{
		//
		// end of production...
		//
		// 0 Program -> program id ; Block endprogram
		//
		case M0:
		{
			SemStackNode* id = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* block = GetPtrTo(&semStack, (eop->right + 3));

			//
			// set output file name to id.name
			//
			char* fileName = id->attr->name;

			//
			// append output file extension to id.name
			//
			fileName = SmartCat(fileName, OUTPUT_EXTENSION);

			//
			// open the output file and write Block.code
			//
			FILE* outFile = NULL;
			outFile = fopen(fileName, "w");
			fprintf(outFile, "%s", block->attr->code);
			fclose(outFile);

			break;
		}

		//
		// end of production...
		//
		// 1 Block -> Declaration ; Declarations beginprogram Statement ; Statements
		//
		case M1:
		{
			SymTabNode* itr = st->head;
			SemStackNode* block = GetPtrTo(&semStack, (eop->left));
			SemStackNode* stmt = GetPtrTo(&semStack, (eop->right + 4));
			SemStackNode* stmts = GetPtrTo(&semStack, (eop->right + 6));

			//////////////////////////////////////////////
			//
			// append variable declarations
			// to block.code
			//
			while(itr != NULL)
			{
				//
				// array indices have no name, so
				// dont write those to code
				//
				if (strcmp(itr->name, "") != 0)
				{
					if (itr->dtype == 'a')
					{
						//
						// convert length of array from int to string
						//
						char tempBuff[MAX_NUM_LENGTH];

						if (sprintf(tempBuff, "%d", itr->length) < 0)
						{
							fprintf(stderr, "Error casting int to string.\n");
							exit(1);
						}


						block->attr->code = Gen(6, block->attr->code,
							".[]\t", itr->name, ", ", tempBuff, "\n");
					}
					else
					{
						block->attr->code = Gen(4, block->attr->code,
							".\t", itr->name, "\n");
					}
				}

				itr = itr->next;
			}

			//////////////////////////////////////////////
			//
			// append start label to block.code
			//
			block->attr->code = Gen(2, block->attr->code, ": Start\n");

			//////////////////////////////////////////////
			//
			// append statements to block.code
			//
			block->attr->code = Gen(3, block->attr->code, stmt->attr->code,
				stmts->attr->code);

			break;
		}

		//
		// end of production....
		//
		// Declaration -> id Ids : Type
		//
		case M4:
		{
			//
			SemStackNode* dtype = GetPtrTo(&semStack, (eop->right + 3));

			IdListNode* itr = idList->head;

			//
			// insert variables into the symbol table,
			// and remove from list
			//
			while(itr != NULL)
			{
				itr->type = dtype->attr->type;
				itr->length = dtype->attr->length;
				InsertSymTab(&st, itr->name, itr->type, itr->length);

				//IdListNode* freePtr = itr;
				//free((void*)freePtr);
				//freePtr = NULL;
				itr = itr->next;
			}

			//
			// re-initialize idList to a new empty list
			//
			idList = CreateList();

			break;
		}

		//
		// end of production...
		//
		// Type -> integer
		//
		case M7:
		{
			SemStackNode* dtype = GetPtrTo(&semStack, eop->left);

			dtype->attr->type = 'i';

			break;
		}

		//
		// end of production...
		//
		// Type -> array ( num ) of integer
		//
		case M8:
		{
			SemStackNode* dtype = GetPtrTo(&semStack, eop->left);
			SemStackNode* dlength = GetPtrTo(&semStack, (eop->right + 2));

			dtype->attr->type = 'a';
			dtype->attr->length = (int)strtol((dlength->attr->name), NULL, 10);

			break;
		}

		//
		// middle of production...
		//
		// Statements1 -> Statement ; Statements2
		//
		case M9_1:
		{
			SemStackNode* stmt = GetPtrTo(&semStack, eop->right);
			SemStackNode* stmts2 = GetPtrTo(&semStack, (eop->right + 2));

			stmts2->attr->code = stmt->attr->code;

			break;
		}

		//
		// end of production...
		//
		// Statements1 -> Statement ; Statements2
		//
		case M9:
		{
			SemStackNode* stmts1 = GetPtrTo(&semStack, eop->left);
			SemStackNode* stmts2 = GetPtrTo(&semStack, (eop->right + 2));

			stmts1->attr->code = SmartCat(stmts1->attr->code, stmts2->attr->code);

			break;
		}

		//
		// end of production...
		//
		// Statement -> Var := Exp
		//
		case M11:
		{
			SemStackNode* stmt = GetPtrTo(&semStack, (eop->left));
			SemStackNode* var = GetPtrTo(&semStack, (eop->right));
			SemStackNode* exp = GetPtrTo(&semStack, (eop->right + 2));

			if (var->attr->type == 'i' && exp->attr->type == 'i')
			{
				stmt->attr->code = Gen(7, stmt->attr->code, exp->attr->code,
					"=\t", var->attr->name, ", ", exp->attr->name, "\n");
			}
			else
			if (var->attr->type == 'a' && exp->attr->type == 'i')
			{
				stmt->attr->code = Gen(10, stmt->attr->code, var->attr->code,
					exp->attr->code, "[]=\t", var->attr->name, ", ",
					var->attr->index, ", ", exp->attr->name, "\n");
			}
			else
			if (var->attr->type == 'i' && exp->attr->type == 'a')
			{
				char* tempName = GetName(st, exp->attr->place);

				stmt->attr->code = Gen(7, stmt->attr->code, exp->attr->code,
					"=\t", var->attr->name, ", ", tempName, "\n");
			}
			else if
			(var->attr->type == 'a' && exp->attr->type == 'a')
			{
				char* tempName = GetName(st, exp->attr->place);

				stmt->attr->code = Gen(10, stmt->attr->code, exp->attr->code,
					var->attr->code,
					"[]=\t", var->attr->name, ", ", var->attr->index,
					", ", tempName, "\n");
			}

			break;
		}

		//
		// end of production...
		//
		// Statement1 -> if BExp then Statement2 ; Statements Else endif
		//
		case M12:
		{
			  SemStackNode* stmt1 = GetPtrTo(&semStack, eop->left);
			  SemStackNode* bexp = GetPtrTo(&semStack, (eop->right + 1));
			  SemStackNode* stmt2 = GetPtrTo(&semStack, (eop->right + 3));
			  SemStackNode* stmts = GetPtrTo(&semStack, (eop->right + 5));
			  SemStackNode* elsepart = GetPtrTo(&semStack, (eop->right + 6));

			  stmt2->attr->begin = NewLabel();
			  elsepart->attr->begin = NewLabel();
			  elsepart->attr->after = NewLabel();

			  stmt1->attr->code = Gen(25, stmt1->attr->code,
			  	bexp->attr->code,
			  	"?:=\t", stmt2->attr->begin, ", ", bexp->attr->name, "\n",
			  	":=\t", elsepart->attr->begin, "\n",
			  	": ", stmt2->attr->begin, "\n",
			  	stmt2->attr->code,
			  	stmts->attr->code,
			  	":=\t", elsepart->attr->after, "\n",
			  	": ", elsepart->attr->begin, "\n",
			  	elsepart->attr->code,
			  	": ", elsepart->attr->after, "\n");

			break;
		}


		//
		// end of production...
		//
		// Statement1 -> while BExp loop Statement2 ; Statements endloop
		//
		case M13:
		{
			SemStackNode* stmt1 = GetPtrTo(&semStack, eop->left);
			SemStackNode* bexp = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* stmt2 = GetPtrTo(&semStack, (eop->right + 3));
			SemStackNode* stmts = GetPtrTo(&semStack, (eop->right + 5));


			stmt1->attr->begin = NewLabel();
			stmt2->attr->begin = NewLabel();
			stmt1->attr->after = NewLabel();

			stmt1->attr->code = Gen(23,
				": ", stmt1->attr->begin, "\n",
				bexp->attr->code,
				"?:=\t", stmt2->attr->begin, ", ", bexp->attr->name, "\n",
				":=\t", stmt1->attr->after, "\n",
				": ", stmt2->attr->begin, "\n",
				stmt2->attr->code,
				stmts->attr->code,
				":=\t", stmt1->attr->begin, "\n",
				": ", stmt1->attr->after, "\n");

			break;
		}

		//
		// end of production...
		//
		// Statement -> read Vars
		// Statement -> write Vars
		//
		case M14:
		{
			SemStackNode* stmt = GetPtrTo(&semStack, eop->left);

			IdListNode* itr = varList->head;

			//
			// add vars into the code
			// and remove from list
			//
			while(itr != NULL)
			{
				if (itr->type == 'i')
				{
					stmt->attr->code = Gen(4, stmt->attr->code,
									      ".<\t", itr->name, "\n");
				}

				if (itr->type == 'a')
				{
					stmt->attr->code = Gen(7, stmt->attr->code, itr->code,
											  ".[]<\t", itr->name, ", ",
											  itr->index, "\n");
				}

				//IdListNode* freePtr = itr;
				//free((void*)freePtr);
				//freePtr = NULL;
				itr = itr->next;
			}

			//
			// re-initialize varList to a new empty list
			//
			varList = CreateList();

			break;
		}

		//
		// end of production...
		//
		// Statement -> write Vars
		//
		case M15:
		{
			SemStackNode* stmt = GetPtrTo(&semStack, eop->left);

			IdListNode* itr = varList->head;

			//
			// add vars into the code
			// and remove from list
			//
			while(itr != NULL)
			{
				if (itr->type == 'i')
				{
					stmt->attr->code = Gen(4, stmt->attr->code,
									      ".>\t", itr->name, "\n");
				}

				if (itr->type == 'a')
				{
					stmt->attr->code = Gen(7, stmt->attr->code, itr->code,
											  ".[]>\t", itr->name, ", ",
											  itr->index, "\n");
				}

				//IdListNode* freePtr = itr;
				//free((void*)freePtr);
				//freePtr = NULL;
				itr = itr->next;
			}

			//
			// re-initialize varList to a new empty list
			//
			varList = CreateList();

			break;
		}

		//
		// end of production...
		//
		// Else -> else Statement ; Statements
		//
		case M16:
		{
			SemStackNode* elsepart = GetPtrTo(&semStack, eop->left);
			SemStackNode* stmt = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* stmts = GetPtrTo(&semStack, (eop->right + 3));

			elsepart->attr->code = Gen(2, stmt->attr->code, stmts->attr->code);

			break;
		}

		//
		// middle of production...
		//
		// BExp -> RExp BExp_1
		//
		case M18_1:
		{
			SemStackNode* rexp = GetPtrTo(&semStack, eop->right);
			SemStackNode* bexp_1 = GetPtrTo(&semStack, (eop->right + 1));

			bexp_1->attr->name = rexp->attr->name;
			bexp_1->attr->place = rexp->attr->place;
			bexp_1->attr->code = rexp->attr->code;

			break;
		}

		//
		// end of production...
		//
		// BExp -> RExp BExp_1
		//
		case M18:
		{
			SemStackNode* bexp = GetPtrTo(&semStack, eop->left);
			SemStackNode* bexp_1 = GetPtrTo(&semStack, (eop->right + 1));

			bexp->attr->name = bexp_1->attr->name;
			bexp->attr->place = bexp_1->attr->place;
			bexp->attr->code = bexp_1->attr->code;

			break;
		}

		//
		// middle of production...
		//
		// BExp_1a -> and RExp BExp_1b
		//
		case M19_1:
		case M20_1:
		{
			SemStackNode* bexp_1a = GetPtrTo(&semStack, eop->left);
			SemStackNode* rexp = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* bexp_1b = GetPtrTo(&semStack, (eop->right + 2));

			char* op = (char*)malloc(sizeof(char) * 3);

			if (marker == M19_1)
				op = "&&";
			if (marker == M20_1)
				op = "||";

			bexp_1b->attr->place = NewTemp(&st, TEMP_PRED);
			bexp_1b->attr->name = GetName(st, bexp_1b->attr->place);

			bexp_1b->attr->code = Gen(9, rexp->attr->code,
				op, "\t", bexp_1b->attr->name, ", ", bexp_1a->attr->name, ", ",
				rexp->attr->name, "\n");

			break;
		}

		//
		// end of production...
		//
		// BExp_1a -> and RExp BExp_1b
		//
		case M19:
		case M20:
		{
			SemStackNode* exp_1a = GetPtrTo(&semStack, eop->left);
			SemStackNode* exp_1b = GetPtrTo(&semStack, (eop->right + 2));

			exp_1a->attr->name = exp_1b->attr->name;
			exp_1a->attr->place = exp_1b->attr->place;
			exp_1a->attr->code = SmartCat(exp_1a->attr->code, exp_1b->attr->code);

			break;
		}

		//
		// end of production...
		//
		// RExp-> not RExp_1
		//
		case M22:
		{
			SemStackNode* rexp = GetPtrTo(&semStack, eop->left);
			SemStackNode* rexp_1 = GetPtrTo(&semStack, (eop->right + 1));

			rexp->attr->place = NewTemp(&st, TEMP_PRED);
			rexp->attr->name = GetName(st, rexp->attr->place);

			rexp->attr->code = Gen(6, rexp_1->attr->code,
				"!\t", rexp->attr->name, ", ", rexp_1->attr->name, "\n");

			break;
		}

		//
		// end of production...
		//
		// RExp -> RExp_1
		//
		case M23:
		{
			SemStackNode* rexp = GetPtrTo(&semStack, eop->left);
			SemStackNode* rexp_1 = GetPtrTo(&semStack, eop->right);

			rexp->attr->name = rexp_1->attr->name;
			rexp->attr->place = rexp_1->attr->place;
			rexp->attr->code = rexp_1->attr->code;

			break;
		}


		//
		// end of production...
		//
		// RExp_1 -> Exp1 Comp Exp2
		//
		case M24:
		{
			SemStackNode* rexp_1 = GetPtrTo(&semStack, eop->left);
			SemStackNode* exp1 = GetPtrTo(&semStack, eop->right);
			SemStackNode* comp = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* exp2 = GetPtrTo(&semStack, (eop->right + 2));

			rexp_1->attr->place = NewTemp(&st, TEMP_PRED);
			rexp_1->attr->name = GetName(st, rexp_1->attr->place);

			if (exp1->attr->type == 'i' && exp2->attr->type == 'i')
			{
				rexp_1->attr->code = Gen(10, exp1->attr->code, exp2->attr->code,
					comp->attr->name, "\t", rexp_1->attr->name, ", ",
					exp1->attr->name, ", ", exp2->attr->name, "\n");
			}
			else
			if (exp1->attr->type == 'a' && exp2->attr->type == 'i')
			{
				//
				// find out the name of the temporary for the array
				//
				char* tempCode = (char*)malloc(sizeof(char) * (strlen(exp1->attr->code) + 1));
				tempCode = strcpy(tempCode, exp1->attr->code);
				tempCode = strchr(tempCode, '[');

				char* tempName = strtok(tempCode, "=[], ");
				tempName = strchr(tempName, TEMP_VAL);

				rexp_1->attr->code = Gen(10, exp1->attr->code, exp2->attr->code,
					comp->attr->name, "\t", rexp_1->attr->name, ", ",
					tempName, ", ", exp2->attr->name, "\n");

			}
			else
			if (exp1->attr->type == 'i' && exp2->attr->type == 'a')
			{
				//
				// find out the name of the temporary for the array
				//
				char* tempCode = (char*)malloc(sizeof(char) * (strlen(exp2->attr->code) + 1));
				tempCode = strcpy(tempCode, exp2->attr->code);
				tempCode = strchr(tempCode, '[');

				char* tempName = strtok(tempCode, "=[], ");
				tempName = strchr(tempName, TEMP_VAL);

				rexp_1->attr->code = Gen(10, exp1->attr->code, exp2->attr->code,
					comp->attr->name, "\t", rexp_1->attr->name, ", ",
					exp1->attr->name, ", ", tempName, "\n");
			}
			else
			if (exp1->attr->type == 'a' && exp2->attr->type == 'a')
			{
				//
				// find out the names of the tempoaries for the arrays
				//
				char* tempCode1 = (char*)malloc(sizeof(char) * (strlen(exp1->attr->code) + 1));
				tempCode1 = strcpy(tempCode1, exp1->attr->code);
				tempCode1 = strchr(tempCode1, '[');

				char* tempName1 = strtok(tempCode1, "=[], ");
				tempName1 = strchr(tempName1, TEMP_VAL);

				char* tempCode2 = (char*)malloc(sizeof(char) * (strlen(exp2->attr->code) + 1));
				tempCode2 = strcpy(tempCode2, exp2->attr->code);
				tempCode2 = strchr(tempCode2, '[');

				char* tempName2 = strtok(tempCode2, "=[], ");
				tempName2 = strchr(tempName2, TEMP_VAL);

				rexp_1->attr->code = Gen(10, exp1->attr->code, exp2->attr->code,
					comp->attr->name, "\t", rexp_1->attr->name, ", ",
					tempName1, ", ", tempName2, "\n");

			}


			break;
		}

		//
		// end of production...
		//
		// RExp_1 -> true;
		//
		case M25:
		{
			SemStackNode* rexp_1 = GetPtrTo(&semStack, eop->left);

			rexp_1->attr->name = "1";

			break;
		}

		//
		// end of production...
		//
		// RExp_1 -> false
		//
		case M26:
		{
			SemStackNode* rexp_1 = GetPtrTo(&semStack, eop->left);

			rexp_1->attr->name = "0";

			break;
		}

		//
		// end of production...
		//
		// Comp -> =
		// Comp -> <>
		// Comp -> <
		// Comp -> >
		// Comp -> <=
		// Comp -> >=
		//
		case M27:
		case M28:
		case M29:
		case M30:
		case M31:
		case M32:
		{
			SemStackNode* comp = GetPtrTo(&semStack, eop->left);

			//printf("eop.left = %s\n", comp->attr->name);

			//char* op = (char*)malloc(sizeof(char) * 3);

			if (marker == M27)
				comp->attr->name = "==";
			else
			if (marker == M28)
				comp->attr->name = "!=";
			else
			if (marker == M29)
				comp->attr->name = "<";
			else
			if (marker == M30)
				comp->attr->name = ">";
			else
			if (marker == M31)
				comp->attr->name = "<=";
			else
			if (marker == M32)
				comp->attr->name = ">=";

			//comp->attr->code = op;

			break;
		}

		//
		// middle of production...
		//
		// Exp -> Term Exp_1
		//
		case M33_1:
		{
			SemStackNode* term = GetPtrTo(&semStack, (eop->right));
			SemStackNode* exp_1 = GetPtrTo(&semStack, (eop->right + 1));

			exp_1->attr->name = term->attr->name;
			exp_1->attr->place = term->attr->place;
			exp_1->attr->type = term->attr->type;
			exp_1->attr->index = term->attr->index;
			exp_1->attr->code = term->attr->code;

			break;
		}

		//
		// end of production...
		//
		// Exp -> Term Exp_1
		//
		case M33:
		{
			SemStackNode* exp = GetPtrTo(&semStack, (eop->left));
			SemStackNode* exp_1 = GetPtrTo(&semStack, (eop->right + 1));

			exp->attr->name = exp_1->attr->name;
			exp->attr->place = exp_1->attr->place;
			exp->attr->type = exp_1->attr->type;
			exp->attr->index = exp_1->attr->index;
			exp->attr->code = exp_1->attr->code;

			if (exp->attr->type == 'a')
			{
				int tempPlace = NewTemp(&st, TEMP_VAL);
				exp->attr->place = tempPlace;
				char* tempName = GetName(st, exp->attr->place);

				exp->attr->code = Gen(8, exp->attr->code, "=[]\t",
					tempName, ", ",	exp->attr->name, ", ",
					exp->attr->index, "\n");
			}

			break;
		}


		//
		// middle of production...
		//
		// Exp -> - Term Exp_1
		//
		case M34_1:
		{
			SemStackNode* term = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* exp_1 = GetPtrTo(&semStack, (eop->right + 2));

			int tempPlace = NewTemp(&st, TEMP_VAL);
			term->attr->place = tempPlace;
			char* tempName = GetName(st, term->attr->place);

			term->attr->code = Gen(6, term->attr->code,
				"*\t", tempName, ", ", term->attr->name, ", -1\n");

			term->attr->name = tempName;

			exp_1->attr->name = term->attr->name;
			exp_1->attr->place = term->attr->place;
			exp_1->attr->type = term->attr->type;
			exp_1->attr->index = term->attr->index;
			exp_1->attr->code = term->attr->code;

			break;
		}

		//
		// end of production...
		//
		// Exp -> - Term Exp_1
		//
		case M34:
		{
			SemStackNode* exp = GetPtrTo(&semStack, (eop->left));
			SemStackNode* exp_1 = GetPtrTo(&semStack, (eop->right + 2));

			exp->attr->name = exp_1->attr->name;
			exp->attr->place = exp_1->attr->place;
			exp->attr->type = exp_1->attr->type;
			exp->attr->index = exp_1->attr->index;
			exp->attr->code = exp_1->attr->code;

			if (exp->attr->type == 'a')
			{
				int tempPlace = NewTemp(&st, TEMP_VAL);
				exp->attr->place = tempPlace;
				char* tempName = GetName(st, exp->attr->place);

				exp->attr->code = Gen(8, exp->attr->code,
					"=[]\t", tempName, ", ", exp->attr->name, ", ",
					exp->attr->index, "\n");
			}

			break;
		}

		//
		// middle of production...
		//
		// Exp_1a -> + Term Exp_1b
		// Exp_1a -> - Term Exp_1b
		//
		case M35_1:
		case M36_1:
		{
			SemStackNode* exp_1a = GetPtrTo(&semStack, (eop->left));
			SemStackNode* term = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* exp_1b = GetPtrTo(&semStack, (eop->right + 2));

			exp_1b->attr->place = NewTemp(&st, TEMP_VAL);
			exp_1b->attr->name = GetName(st, exp_1b->attr->place);
			exp_1b->attr->type = term->attr->type;
			exp_1b->attr->index = term->attr->index;

			char* op = (char*)malloc(sizeof(char) * 2);

			if (marker == M35_1)
				op = "+";
			if (marker == M36_1)
				op = "-";

			exp_1b->attr->code = Gen(9, term->attr->code,
				op, "\t", exp_1b->attr->name, ", ", exp_1a->attr->name,
				", ", term->attr->name, "\n");

			break;
		}

		//
		// end of production...
		//
		// Exp_1a -> + Term Exp_1b
		// Exp_1a -> - Term Exp_1b
		//
		case M35:
		case M36:
		{
			SemStackNode* exp_1a = GetPtrTo(&semStack, (eop->left));
			SemStackNode* exp_1b = GetPtrTo(&semStack, (eop->right + 2));

			exp_1a->attr->name = exp_1b->attr->name;
			exp_1a->attr->place = exp_1b->attr->place;
			exp_1a->attr->type = exp_1b->attr->type;
			exp_1a->attr->index = exp_1b->attr->index;
			exp_1a->attr->code = SmartCat(exp_1a->attr->code, exp_1b->attr->code);

			break;
		}

		//
		// middle of production...
		//
		// Term -> Factor Term_1
		//
		case M38_1:
		{
			SemStackNode* factor = GetPtrTo(&semStack, (eop->right));
			SemStackNode* term_1 = GetPtrTo(&semStack, (eop->right + 1));

			term_1->attr->name = factor->attr->name;
			term_1->attr->place = factor->attr->place;
			term_1->attr->type = factor->attr->type;
			term_1->attr->index = factor->attr->index;
			term_1->attr->code = factor->attr->code;

			break;
		}

		//
		// end of production...
		//
		// Term -> Factor Term_1
		//
		case M38:
		{
			SemStackNode* term = GetPtrTo(&semStack, (eop->left));
			SemStackNode* term_1 = GetPtrTo(&semStack, (eop->right + 1));

			term->attr->name = term_1->attr->name;
			term->attr->place = term_1->attr->place;
			term->attr->type = term_1->attr->type;
			term->attr->index = term_1->attr->index;
			term->attr->code = term_1->attr->code;

			break;
		}

		//
		// middle of production...
		//
		// Term1a -> * Factor Term_1b
		// Term1a -> / Factor Term_1b
		//
		case M39_1:
		case M40_1:
		{
			SemStackNode* term_1a = GetPtrTo(&semStack, eop->left);
			SemStackNode* factor = GetPtrTo(&semStack, (eop->right + 1));
			SemStackNode* term_1b = GetPtrTo(&semStack, (eop->right + 2));

			term_1b->attr->place = NewTemp(&st, TEMP_VAL);
			term_1b->attr->name = GetName(st, term_1b->attr->place);
			term_1b->attr->type = factor->attr->type;
			term_1b->attr->index = factor->attr->index;

			char* op = (char*)malloc(sizeof(char) + 1);

			if (marker == M39_1)
				op = "*";
			if (marker == M40_1)
				op = "/";

			term_1b->attr->code = Gen(9, factor->attr->code, op, "\t",
				term_1b->attr->name, ", ", term_1a->attr->name, ", ",
				factor->attr->name, "\n");

			break;
		}

		//
		// end of production...
		//
		// Term1a -> * Factor Term_1b
		// Term1a -> / Factor Term_1b
		//
		case M39:
		case M40:
		{
			SemStackNode* term_1a = GetPtrTo(&semStack, eop->left);
			SemStackNode* term_1b = GetPtrTo(&semStack, (eop->right + 2));

			term_1a->attr->name = term_1b->attr->name;
			term_1a->attr->place = term_1b->attr->place;
			term_1a->attr->type = term_1b->attr->type;
			term_1a->attr->index = term_1b->attr->index;
			term_1a->attr->code = SmartCat(term_1a->attr->code, term_1b->attr->code);

			break;
		}


		//
		// end of production...
		//
		// Factor -> Var
		//
		case M42:
		{
			SemStackNode* factor = GetPtrTo(&semStack, eop->left);
			SemStackNode* var = GetPtrTo(&semStack, eop->right);

			factor->attr->name = var->attr->name;
			factor->attr->place = var->attr->place;
			factor->attr->code = var->attr->code;
			factor->attr->type = var->attr->type;
			factor->attr->index = var->attr->index;

			break;
		}

		//
		// end of production...
		//
		// Factor -> num
		//
		case M43:
		{
			SemStackNode* factor = GetPtrTo(&semStack, eop->left);
			SemStackNode* num = GetPtrTo(&semStack, eop->right);

			factor->attr->name = num->attr->name;
			factor->attr->type = 'i';
			factor->attr->place = -1;

			break;
		}

		//
		// end of production...
		//
		// Factor -> ( Exp )
		//
		case M44:
		{
			SemStackNode* factor = GetPtrTo(&semStack, eop->left);
			SemStackNode* exp = GetPtrTo(&semStack, (eop->right + 1));

			factor->attr->name = exp->attr->name;
			factor->attr->place = exp->attr->place;
			factor->attr->type = exp->attr->type;
			factor->attr->code = exp->attr->code;
			factor->attr->index = exp->attr->index;

			break;
		}

		//
		// end of production...
		//
		// Vars -> Var, Vars_1
		//
		case M45_1:
		{
			SemStackNode* var = GetPtrTo(&semStack, eop->right);

			InsertToList(&varList, var->attr->name,
				var->attr->type, 0, var->attr->index, var->attr->code);

			break;
		}

		//
		// end of production...
		//
		// Vars_1a -> , Var Vars_1b
		//
		case M46_1:
		{
			SemStackNode* var = GetPtrTo(&semStack, (eop->right + 1));

			InsertToList(&varList, var->attr->name, var->attr->type, 0,
				var->attr->index, var->attr->code);

			break;
		}

		//
		// end of production...
		//
		// Var -> id Var_1
		//
		case M48:
		{
			SemStackNode* var = GetPtrTo(&semStack, eop->left);
			SemStackNode* id = GetPtrTo(&semStack, eop->right);
			SemStackNode* var_1 = GetPtrTo(&semStack, (eop->right + 1));

			var->attr->name = id->attr->name;
			var->attr->index = var_1->attr->name;
			var->attr->place = id->attr->place;
			var->attr->code = var_1->attr->code;
			var->attr->type = var_1->attr->type;

			break;
		}

		//
		// end of production...
		//
		// Var_1 -> ( Exp )
		//
		case M49:
		{
			SemStackNode* var_1 = GetPtrTo(&semStack, eop->left);
			SemStackNode* exp = GetPtrTo(&semStack, (eop->right + 1));

			var_1->attr->name = exp->attr->name;
			var_1->attr->code = exp->attr->code;
			var_1->attr->type = 'a';

			break;
		}

		//
		// end of production...
		//
		// Var_1 -> @
		//
		case M50:
		{
			SemStackNode* var_1 = GetPtrTo(&semStack, eop->left);

			var_1->attr->type = 'i';
		}
	}
}
//
// end function PerformSemanticRule(SemStack*, SymTab*, type_eop*,
//		int, SynStack*)
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// EngageParse(FILE* stream, Bool printTokens, Bool printProd,
//		Bool printSymbolTable)
//
// description: starts parse by getting a token from the input
// stream for the MINI_L language, this should be the keyword
// "program" from there, the parse will look at the item on the
// top of the stack, if it is a terminal, then it should match
// the input terminal, else if it is a non-terminal, then
// the parse table will tell us which production to replace
// the current nonterminal on the top of the stack with
// (in reverse order)
// this process of getting a token and comparing it to the top
// of the stack is continued until an error occurs or
// when the top of the stack is NULL and the current input
// token is NULL, at which point a successful parse has been
// performed.
//
// NOTE: the stack is initialized by pushing the non-terminal
// grammar element NGE_PROGRAM onto the top of the stack
//
void EngageParse(FILE* stream, Bool printTokens, Bool printProd,
	Bool printSymbolTable)
{
	InitializeParseTable();

	//
	// create the symbol table
	//
	SymTab* symbolTable = CreateSymTab();

	//
	// create lists
	//
	idList = CreateList();
	varList = CreateList();

	//
	// put the start symbol onto the start
	// start symbol = NGE_PROGRAM
	//
	SynStack* parseSynStack = NULL;
	SynPush(&parseSynStack, NGE_PROGRAM);

	//
	// put the start symbol onto the
	// semantic stack
	//
	SemStack* semStack = CreateSemStack();
	SemPush(&semStack, InitAttr(NGE_PROGRAM));

	//
	// initialize the semantic stack pointers
	//
	type_eop eop;
	eop.left = 0;
	eop.right = 0;
	eop.curr = 1;
	eop.top = 2;

	//
	// Get a token from input
	//
	Token* t = GetToken(stream);

	//
	// put token into a linked list for
	// printing of tokens later
	//
	if (t != NULL && printTokens == TRUE)
		Insert(t);

	//
	// parse until there is an error,
	// or the stack and input are $
	//
	while (parseSynStack != NULL && t != NULL)
	{
		SemStackNode* leftSide = GetPtrTo(&semStack, eop.left);
		SemStackNode* current = GetPtrTo(&semStack, eop.curr);

		//
		// make changes only once, we do this when the semantic
		// stack is growing, not shrinking
		//
		if (parseSynStack->gElement < MARKER_OFFSET)
		{
			if (leftSide != NULL && current != NULL && current->attr->gElement == TGE_ID)
			{
				current->attr->name = t->name;

				if (leftSide->attr->gElement == NGE_DECLARATION
					&& eop.curr == eop.right)
				{
					InsertToList(&idList, current->attr->name, current->attr->type,
						current->attr->length, "", "");
				}

				if (leftSide->attr->gElement == NGE_IDS
					&& eop.curr == eop.right + 1)
				{
					InsertToList(&idList, current->attr->name, current->attr->type,
						current->attr->length, "", "");
				}
			}

			else
			if (current != NULL && current->attr->gElement == TGE_NUM)
			{
				current->attr->name = t->name;
			}
		}

		//////////////////////////////////////
		// MARKER
		//
		// case: top of the stack is a marker
		//
		if (parseSynStack->gElement >= MARKER_OFFSET)
		{
			//
			// pop off marker and perform
			// corresponding semantic rule
			//
			int marker = parseSynStack->gElement;

			PerformSemanticRule(semStack, symbolTable, &eop, marker, parseSynStack);

			if (parseSynStack->gElement < MID_MARKER_OFFSET)
			{
				//
				// pop off marker
				//
				SynPop(&parseSynStack);

				//
				// restore eop
				//
				eop.left = Peek(parseSynStack);
				SynPop(&parseSynStack);
				eop.right = Peek(parseSynStack);
				SynPop(&parseSynStack);
				eop.curr = Peek(parseSynStack);
				SynPop(&parseSynStack);
				eop.top = Peek(parseSynStack);
				SynPop(&parseSynStack);

				//
				// increment current
				//
				if (eop.curr < eop.top - 1)
					eop.curr++;

				//
				// remove elements above and including top
				//
				SemPopTo(&semStack, eop.top);
			}
			else
			{
				//
				// pop off marker
				//
				SynPop(&parseSynStack);

				//
				// increment current
				//
				if (eop.curr < eop.top - 1)
					eop.curr++;
			}
		}

		//////////////////////////////////////
		// MATCH
		//
		// case: top of stack is a terminal
		//
		// pop the parsing stack
		// and advance input
		//
		else
		if (parseSynStack->gElement < NON_TERM_OFFSET)
		{
			//
			// increment current semantic stack pointer
			//
			if (eop.curr < eop.top - 1)
				eop.curr++;

			//
			// after the pointers are changed back
			// on the semantic stack, from the production
			// number marker and eop being popped off the
			// syntax stack, the syntax stack
			// is 1 element ahead of the current semantic stack
			// pointer, so increment that bad boy once again
			// then the top of the syntax stack == current eop
			//
			if (GetSymbolGE(Peek(parseSynStack)) != current->attr->gElement
			&&  eop.curr < eop.top - 1)
				eop.curr++;

			//
			// make sure the terminals match
			//
 			if (! Match(&parseSynStack, GetSymbolGE(t->symbol)))
 			{
				Error("Parse Error4.\n");
			}

 			//
 			// Get next token from input
 			//
 			t = GetToken(stream);

			//
			// put token into a linked list for
			// printing of tokens later
			//
 			if (t != NULL && printTokens == TRUE)
 				Insert(t);
		}

		//////////////////////////////////////
		// GENERATE
		//
		// case: top of stack is a non-terminal
		//
		// push production onto the
		// parsing stack
		//
		else
		{
			//
			// get production number from parse table
			//
			int productionNum =
				parseTable[parseSynStack->gElement - NON_TERM_OFFSET]
						  [GetSymbolGE(t->symbol)];

			//
			// print production
			//
			if (printProd == TRUE)
			{
				printf("%s -> ", GetGEString(parseSynStack->gElement));
			}

			//
			// put generated grammar elements onto the stack
			//
			ProduceToSynStack(&parseSynStack, &semStack, productionNum, &eop, printProd);

			//
			// setup new semantic stack pointers
			//
			eop.left = eop.curr;
			eop.right = eop.top;
			eop.curr = eop.top;
			eop.top = SemStackSize(semStack) + 1;
		}
	}

	if (parseSynStack != NULL)
	{
		//////////////////////////////////////
		// LAST MARKER AND NO MORE INPUT
		//
		if (parseSynStack->gElement >= MARKER_OFFSET)
		{
			//
			// pop off marker and perform
			// corresponding semantic rule
			//
			PerformSemanticRule(semStack, symbolTable, &eop, parseSynStack->gElement, parseSynStack);
			SynPop(&parseSynStack);

			//
			// restore eop
			//
			eop.left = Peek(parseSynStack);
			SynPop(&parseSynStack);
			eop.right = Peek(parseSynStack);
			SynPop(&parseSynStack);
			eop.curr = Peek(parseSynStack);
			SynPop(&parseSynStack);
			eop.top = Peek(parseSynStack);
			SynPop(&parseSynStack);
		}
	}
	else
	{	Error("Parse Error1.\n"); }

	//
	// make sure both the stack is empty and there
	// are no more tokens in the input
	//
	if (parseSynStack != NULL
	||  t != NULL)
	{ Error("Parse Error2.\n"); }

	if (printSymbolTable == TRUE)
		PrintSymTab(symbolTable);
}
//
// end EngageParse(FILE*, Bool, Bool, Bool) function
//////////////////////////////////////////////////////////////

