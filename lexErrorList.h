#ifndef _LEXERRORLIST_H_
#define _LEXERRORLIST_H_

#include <stdio.h>

void lexErrorNodeInsert(int line, int position, char* message);
void lexErrorPrintList(FILE* stream);

#endif
