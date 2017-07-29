//////////////////////////////////////////////////////////////
//
// Programmer: Clayton Wong
//
// parse.h
//
// description: this file contains definitions used for the
// MINI_L LL(1) parser
//
//////////////////////////////////////////////////////////////

#include <synstack.h>
#include <symtab.h>

//////////////////////////////////////////////////////////////
// LL(1) parse table definitions
//
#define		EMPTY				-1
#define 	TGE_ID				0
#define		TGE_NUM				1
#define		TGE_PROGRAM			2
#define		TGE_BEGINPROGRAM	3
#define		TGE_ENDPROGRAM		4
#define		TGE_INTEGER			5
#define		TGE_ARRAY			6
#define		TGE_IF				7
#define		TGE_THEN			8
#define		TGE_ELSE			9
#define		TGE_ENDIF			10
#define		TGE_LOOP			11
#define		TGE_ENDLOOP			12
#define		TGE_WHILE			13
#define		TGE_NOT				14
#define		TGE_AND				15
#define		TGE_OR				16
#define		TGE_READ			17
#define		TGE_WRITE			18
#define		TGE_TRUE			19
#define		TGE_FALSE			20
#define		TGE_SEMI			21
#define		TGE_COLON			22
#define		TGE_ASSIGN			23
#define		TGE_EQUAL			24
#define		TGE_NOTEQUAL		25
#define		TGE_LT				26
#define		TGE_GT				27
#define		TGE_LE				28
#define		TGE_GE				29
#define		TGE_LPAR			30
#define		TGE_RPAR			31
#define		TGE_PLUS			32
#define		TGE_MINUS			33
#define		TGE_TIMES			34
#define		TGE_DIV				35
#define		TGE_COMMA			36
#define		TGE_OF				37
#define		NGE_PROGRAM			38
#define		NGE_BLOCK			39
#define		NGE_DECLARATIONS	40
#define		NGE_DECLARATION		41
#define		NGE_IDS				42
#define		NGE_TYPE			43
#define		NGE_STATEMENTS		44
#define		NGE_STATEMENT		45
#define		NGE_ELSE			46
#define		NGE_BEXP			47
#define		NGE_BEXP_1			48
#define		NGE_REXP			49
#define		NGE_REXP_1			50
#define		NGE_COMP			51
#define		NGE_EXP				52
#define		NGE_EXP_1			53
#define		NGE_TERM			54
#define		NGE_TERM_1			55
#define		NGE_FACTOR			56
#define		NGE_VARS			57
#define		NGE_VARS_1			58
#define		NGE_VAR				59
#define		NGE_VAR_1			60

#define 	NON_TERM_OFFSET		38
#define 	N_TERMINAL			38
#define		N_NONTERMINAL		23
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// semantic definitions
//
//
// end of production markers
//
#define		M0					61
#define		M1					62
#define		M2					63
#define		M3					64
#define		M4					65
#define		M5					66
#define		M6					67
#define		M7					68
#define		M8					69
#define		M9					70
#define		M10					71
#define		M11					72
#define		M12					73
#define		M13					74
#define		M14					75
#define		M15					76
#define		M16					77
#define		M17					78
#define		M18					79
#define		M19					80
#define		M20					81
#define		M21					82
#define		M22					83
#define		M23					84
#define		M24					85
#define		M25					86
#define		M26					87
#define		M27					88
#define		M28					89
#define		M29					90
#define		M30					91
#define		M31					92
#define		M32					93
#define		M33					94
#define		M34					95
#define		M35					96
#define		M36					97
#define		M37					98
#define		M38					99
#define		M39					100
#define		M40					101
#define		M41					102
#define		M42					103
#define		M43					104
#define		M44					105
#define		M45					106
#define		M46					107
#define		M47					108
#define		M48					109
#define		M49					110
#define		M50					111
//
// middle of production markers
//
#define		M9_1				112
#define		M18_1				113
#define		M19_1				114
#define		M20_1				115
#define		M33_1				116
#define		M34_1				117
#define		M35_1				118
#define		M36_1				119
#define		M38_1				120
#define		M39_1				121
#define		M40_1				122
#define 	M45_1				123
#define		M46_1				124
//
// offsets
//
#define		MARKER_OFFSET		61
#define		MID_MARKER_OFFSET	112
//
//
//
#define 	OUTPUT_EXTENSION	".code"
#define		MAX_NUM_LENGTH		13
//
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//
// intermediate code characters
//
#define 	TEMP_VAL	't'
#define		TEMP_PRED	'p'
#define		LABEL		'L'
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// eop structure
//
typedef struct
{
	int left, right, curr, top;
} type_eop;
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// LL(1) parse table
int parseTable[N_NONTERMINAL][N_TERMINAL];
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// function declarations
//
void ProduceToStack(SynStack** s, int prodNum, Bool printProd);
char* GetGEString(int ge);
int GetSymbolGE(Symbol sym);
void InitializeParseTable();
void EngageParse(FILE* stream, Bool printTokens, Bool printProd, Bool printSymbolTable);
void PrintParseTable();
void PushEOP(SynStack** s, type_eop* eop);
int NewTemp(SymTab** s, char tempType);
char* NewLabel();
//////////////////////////////////////////////////////////////
