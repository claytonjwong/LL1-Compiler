//////////////////////////////////////////////////////////////
//
// programmer: Clayton Wong
// parse_utils.c
// description: contains utility functions for parsing
// and generating code in the 1 pass compiler
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// header files
//
#include <parse.h>
#include <semstack.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// GetSymbolGE(Symbol sym)
//
// returns: an integer representation of the symbol
// as a grammar element definition
//
int GetSymbolGE(Symbol sym)
{
	switch(sym)
	{
		case IDENTIFIER:
			return TGE_ID;
		case NUMBER:
			return TGE_NUM;
		case PROGSYM:
			return TGE_PROGRAM;
		case BEGPROGSYM:
			return TGE_BEGINPROGRAM;
		case ENDPROGSYM:
			return TGE_ENDPROGRAM;
		case ARRAYSYM:
			return TGE_ARRAY;
		case OFSYM:
			return TGE_OF;
		case INTSYM:
			return TGE_INTEGER;
		case IFSYM:
			return TGE_IF;
		case THENSYM:
			return TGE_THEN;
		case ELSESYM:
			return TGE_ELSE;
		case ENDIFSYM:
			return TGE_ENDIF;
		case WHILESYM:
			return TGE_WHILE;
		case LOOPSYM:
			return TGE_LOOP;
		case ENDLOOPSYM:
			return TGE_ENDLOOP;
		case READSYM:
			return TGE_READ;
		case WRITESYM:
			return TGE_WRITE;
		case NOTSYM:
			return TGE_NOT;
		case ANDSYM:
			return TGE_AND;
		case ORSYM:
			return TGE_OR;
		case TRUESYM:
			return TGE_TRUE;
		case FALSESYM:
			return TGE_FALSE;
		case SEMISYM:
			return TGE_SEMI;
		case COMMASYM:
			return TGE_COMMA;
		case COLONSYM:
			return TGE_COLON;
		case ASSIGNSYM:
			return TGE_ASSIGN;
		case EQUALSYM:
			return TGE_EQUAL;
		case LPARSYM:
			return TGE_LPAR;
		case RPARSYM:
			return TGE_RPAR;
		case NOTEQSYM:
			return TGE_NOTEQUAL;
		case LTSYM:
			return TGE_LT;
		case GTSYM:
			return TGE_GT;
		case LESYM:
			return TGE_LE;
		case GESYM:
			return TGE_GE;
		case PLUSSYM:
			return TGE_PLUS;
		case MINUSSYM:
			return TGE_MINUS;
		case TIMESSYM:
			return TGE_TIMES;
		case DIVSYM:
			return TGE_DIV;
		case 17:
			return TGE_READ;
		default:
			printf("symbol: %d =? %d\n", sym, READSYM);
			printf("string: %s\n", GetGEString(sym));
			Error("Parse Error6.\n");
	}

	return -1;
}
//
// end GetSymbolGE(Symbol) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// GetGEString(int ge)
//
// returns: a string representation of the grammar element
//
char* GetGEString(int ge)
{
	switch(ge)
	{
		case TGE_ID:
			return "id";
		case TGE_NUM:
			return "num";
		case TGE_PROGRAM:
			return "program";
		case TGE_BEGINPROGRAM:
			return "beginprogram";
		case TGE_ENDPROGRAM:
			return "endprogram";
		case TGE_INTEGER:
			return "integer";
		case TGE_ARRAY:
			return "array";
		case TGE_IF:
			return "if";
		case TGE_THEN:
			return "then";
		case TGE_ELSE:
			return "else";
		case TGE_ENDIF:
			return "elseif";
		case TGE_LOOP:
			return "loop";
		case TGE_ENDLOOP:
			return "endloop";
		case TGE_WHILE:
			return "while";
		case TGE_NOT:
			return "not";
		case TGE_AND:
			return "and";
		case TGE_OR:
			return "or";
		case TGE_READ:
			return "read";
		case TGE_WRITE:
			return "write";
		case TGE_TRUE:
			return "true";
		case TGE_FALSE:
			return "false";
		case TGE_SEMI:
			return ";";
		case TGE_COLON:
			return ":";
		case TGE_ASSIGN:
			return ":=";
		case TGE_EQUAL:
			return "=";
		case TGE_NOTEQUAL:
			return "<>";
		case TGE_LT:
			return "<";
		case TGE_GT:
			return ">";
		case TGE_LE:
			return "<=";
		case TGE_GE:
			return ">=";
		case TGE_LPAR:
			return "(";
		case TGE_RPAR:
			return ")";
		case TGE_PLUS:
			return "+";
		case TGE_MINUS:
			return "-";
		case TGE_TIMES:
			return "*";
		case TGE_DIV:
			return "/";
		case TGE_COMMA:
			return ",";
		case TGE_OF:
			return "of";
		case NGE_PROGRAM:
			return "Program";
		case NGE_BLOCK:
			return "Block";
		case NGE_DECLARATIONS:
			return "Declarations";
		case NGE_DECLARATION:
			return "Declaration";
		case NGE_IDS:
			return "Ids";
		case NGE_TYPE:
			return "Type";
		case NGE_STATEMENTS:
			return "Statements";
		case NGE_STATEMENT:
			return "Statement";
		case NGE_ELSE:
			return "Else";
		case NGE_BEXP:
			return "BExp";
		case NGE_BEXP_1:
			return "BExp_1";
		case NGE_REXP:
			return "RExp";
		case NGE_REXP_1:
			return "RExp_1";
		case NGE_COMP:
			return "Comp";
		case NGE_EXP:
			return "Exp";
		case NGE_EXP_1:
			return "Exp_1";
		case NGE_TERM:
			return "Term";
		case NGE_TERM_1:
			return "Term_1";
		case NGE_FACTOR:
			return "Factor";
		case NGE_VARS:
			return "Vars";
		case NGE_VARS_1:
			return "Vars_1";
		case NGE_VAR:
			return "Var";
		case NGE_VAR_1:
			return "Var_1";
		case M0:
			return "M#0";
		case M1:
			return "M#1";
		case M2:
			return "M#2";
		case M3:
			return "M#3";
		case M4:
			return "M#4";
		case M5:
			return "M#5";
		case M6:
			return "M#6";
		case M7:
			return "M#7";
		case M8:
			return "M#8";
		case M9:
			return "M#9";
		case M10:
			return "M#10";
		case M11:
			return "M#11";
		case M12:
			return "M#12";
		case M13:
			return "M#13";
		case M14:
			return "M#15";
		case M16:
			return "M#16";
		case M17:
			return "M#17";
		case M18:
			return "M#18";
		case M19:
			return "M#19";
		case M20:
			return "M#20";
		case M21:
			return "M#21";
		case M22:
			return "M#22";
		case M23:
			return "M#23";
		case M24:
			return "M#24";
		case M25:
			return "M#25";
		case M26:
			return "M#26";
		case M27:
			return "M#27";
		case M28:
			return "M#28";
		case M29:
			return "M#29";
		case M30:
			return "M#30";
		case M31:
			return "M#31";
		case M32:
			return "M#32";
		case M33:
			return "M#33";
		case M34:
			return "M#34";
		case M35:
			return "M#35";
		case M36:
			return "M#36";
		case M37:
			return "M#37";
		case M38:
			return "M#38";
		case M39:
			return "M#39";
		case M40:
			return "M#40";
		case M41:
			return "M#41";
		case M42:
			return "M#42";
		case M43:
			return "M#43";
		case M44:
			return "M#44";
		case M45:
			return "M#45";
		case M46:
			return "M#46";
		case M47:
			return "M#47";
		case M48:
			return "M#48";
		case M49:
			return "M#49";
		case M50:
			return "M#50";

		case M9_1:
			return "M9_1";
		case M18_1:
			return "M18_1";
		case M19_1:
			return "M19_1";
		case M20_1:
			return "M20_1";
		case M33_1:
			return "M33_1";
		case M34_1:
			return "M34_1";
		case M35_1:
			return "M35_1";
		case M36_1:
			return "M36_1";
		case M38_1:
			return "M38_1";
		default:
		{
			printf("unknown: %d\n", ge);
			Error("Parse Error69.\n");
		}
	}

	return "NOT FOUND!";
}
//
// end GetGEString(int ge) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// InitAttr(int symbol)
//
// description: initializes attributes of an element
// on the semantic stack
//
Attribute InitAttr(int symbol)
{
        Attribute a;
        if (symbol >= NON_TERM_OFFSET)
                a.gElement = symbol;
        else
                a.gElement = GetSymbolGE(symbol);

        a.length = 0;
        a.code = "";
        a.name = GetGEString(symbol);
        a.type = 'u';
        a.value = 0;

        return a;
}
//
// end InitAttr(int) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// PushEOP(SynStack** s, type_eop* eop)
//
// description: pushes the eop values onto the syntax stack
//
void PushEOP(SynStack** s, type_eop* eop)
{
                SynPush(s, eop->top);
                SynPush(s, eop->curr);
                SynPush(s, eop->right);
                SynPush(s, eop->left);
}
//
// end PushEOP(SynStack**, type_eop*) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// NewTemp(SymTab**s, char tempType)
//
// description: creates a new temporary, stores it on the
// symbol table, and returns the index of the new
// temporary's position on the symbol table
//
int NewTemp(SymTab** s, char tempType)
{
        static int currTempVal = 0;
        static int currTempPred = 0;

        char buffer[ID_MAX_LENGTH];

        if (tempType == TEMP_VAL)
        {
                sprintf(buffer, "%c%d", tempType, currTempVal);
                currTempVal++;
        }
        if (tempType == TEMP_PRED)
        {
                sprintf(buffer, "%c%d", tempType, currTempPred);
                currTempPred++;
        }

        InsertSymTab(s, buffer, 'i', 0);

        return GetPlace(*s, buffer);
}
//
// end NewTemp(SymTab**, char) function
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// NewLabel()
//
// description: creates a new label and returns its name,
// keeps track of the current label number, and increments
// after each new label is created
//
char* NewLabel()
{
        static int currLabel = 0;

        char* buffer = (char*)malloc(sizeof(char) * ID_MAX_LENGTH + 1);

        sprintf(buffer, "%c%d", LABEL, currLabel);

        currLabel++;

        return buffer;
}
//
// end NewLabel() function
//////////////////////////////////////////////////////////////
