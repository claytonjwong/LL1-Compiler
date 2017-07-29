#include <symtab.h>
#include <stdio.h>

int main()
{
	SymTab* st = CreateSymTab();

	int i = 0;

	for (i=0; i < 5; i++)
		InsertSymTab(&st, "a", 'i', 0);

	PrintSymTab(st);

	return 0;
}
