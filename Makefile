
CC = gcc
CFLAGS = -g -Wall -I. 
OBJS = main.o lex.o lex_utils.o lexErrorList.o linkedlist.o parse.o synstack.o list.o idlist.o semstack.o symtab.o parse_utils.o gen.o
TARGET = jcc

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c 
	$(CC) -c $(CFLAGS) main.c

lex.o: lex.c lex.h 
	$(CC) -c $(CFLAGS) lex.c

parse.o: parse.c parse.h idlist.c idlist.h parse_utils.c
	$(CC) -c $(CFLAGS) parse.c

parse_utils.o: parse.c parse.h parse_utils.c
	$(CC) -c $(CFLAGS) parse_utils.c

lex_utils.o: lex_utils.c lex_utils.h
	$(CC) -c $(CFLAGS) lex_utils.c
	
lexErrorList.o : lexErrorList.c
	$(CC) -c $(CFLAGS) lexErrorList.c
	
linkedlist.o: linkedlist.c
	$(CC) -c $(CFLAGS) linkedlist.c

idlist.o: idlist.c idlist.h
	$(CC) -c $(CFLAGS) idlist.c

list.o: list.c list.h
	$(CC) -c $(CFLAGS) list.c
	
synstack.o: synstack.c synstack.h list.c list.h
	$(CC) -c $(CFLAGS) synstack.c	
	
semstack.o: semstack.c semstack.h
	$(CC) -c $(CFLAGS) semstack.c

symtab.o: symtab.c symtab.h
	$(CC) -c $(CFLAGS) symtab.c

gen.o: gen.c gen.h
	$(CC) -c $(CFLAGS) gen.c

clean:
	rm -f *.o core

depend:
	makedepend -I. *.c

# DO NOT DELETE

idlist.o: idlist.h /usr/include/malloc.h /usr/include/sys/types.h
idlist.o: /usr/include/sys/isa_defs.h /usr/include/sys/feature_tests.h
idlist.o: /usr/include/sys/machtypes.h /usr/include/sys/int_types.h
idlist.o: /usr/include/sys/select.h /usr/include/sys/time.h
idlist.o: /usr/include/sys/time.h /usr/include/strings.h
idlist.o: /usr/include/string.h /usr/include/iso/string_iso.h
lex.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
lex.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
lex.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
lex.o: /usr/include/stdio_impl.h /usr/include/stdlib.h
lex.o: /usr/include/iso/stdlib_iso.h /usr/include/strings.h
lex.o: /usr/include/sys/types.h /usr/include/sys/machtypes.h
lex.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
lex.o: /usr/include/sys/time.h /usr/include/sys/time.h /usr/include/string.h
lex.o: /usr/include/iso/string_iso.h /usr/include/ctype.h
lex.o: /usr/include/iso/ctype_iso.h lex.h lexErrorList.h linkedlist.h
lex.o: lex_utils.h
lexErrorList.o: lex.h /usr/include/stdio.h /usr/include/iso/stdio_iso.h
lexErrorList.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
lexErrorList.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
lexErrorList.o: /usr/include/stdio_impl.h lex_utils.h lexErrorList.h
lexErrorList.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
lexErrorList.o: /usr/include/string.h /usr/include/iso/string_iso.h
lex_utils.o: lex_utils.h lex.h /usr/include/stdio.h
lex_utils.o: /usr/include/iso/stdio_iso.h /usr/include/sys/feature_tests.h
lex_utils.o: /usr/include/sys/isa_defs.h /usr/include/sys/va_list.h
lex_utils.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
lex_utils.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
lex_utils.o: /usr/include/strings.h /usr/include/sys/types.h
lex_utils.o: /usr/include/sys/machtypes.h /usr/include/sys/int_types.h
lex_utils.o: /usr/include/sys/select.h /usr/include/sys/time.h
lex_utils.o: /usr/include/sys/time.h /usr/include/string.h
lex_utils.o: /usr/include/iso/string_iso.h
linkedlist.o: lex.h /usr/include/stdio.h /usr/include/iso/stdio_iso.h
linkedlist.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
linkedlist.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
linkedlist.o: /usr/include/stdio_impl.h lex_utils.h linkedlist.h
linkedlist.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h
linkedlist.o: /usr/include/string.h /usr/include/iso/string_iso.h
list.o: list.h /usr/include/stdio.h /usr/include/iso/stdio_iso.h
list.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
list.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
list.o: /usr/include/stdio_impl.h /usr/include/stdlib.h
list.o: /usr/include/iso/stdlib_iso.h
listtest.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
listtest.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
listtest.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
listtest.o: /usr/include/stdio_impl.h
main.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
main.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
main.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
main.o: /usr/include/stdio_impl.h /usr/include/stdlib.h
main.o: /usr/include/iso/stdlib_iso.h /usr/include/strings.h
main.o: /usr/include/sys/types.h /usr/include/sys/machtypes.h
main.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
main.o: /usr/include/sys/time.h /usr/include/sys/time.h /usr/include/string.h
main.o: /usr/include/iso/string_iso.h lexErrorList.h linkedlist.h lex.h
main.o: parse.h synstack.h
parse.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
parse.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
parse.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
parse.o: /usr/include/stdio_impl.h parse.h synstack.h lex.h
parse.o: /usr/include/strings.h /usr/include/sys/types.h
parse.o: /usr/include/sys/machtypes.h /usr/include/sys/int_types.h
parse.o: /usr/include/sys/select.h /usr/include/sys/time.h
parse.o: /usr/include/sys/time.h /usr/include/string.h
parse.o: /usr/include/iso/string_iso.h linkedlist.h
semstack.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
semstack.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
semstack.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
semstack.o: /usr/include/stdio_impl.h /usr/include/strings.h
semstack.o: /usr/include/sys/types.h /usr/include/sys/machtypes.h
semstack.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
semstack.o: /usr/include/sys/time.h /usr/include/sys/time.h
semstack.o: /usr/include/string.h /usr/include/iso/string_iso.h
semstack.o: /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h semstack.h
synstack.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
synstack.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
synstack.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
synstack.o: /usr/include/stdio_impl.h /usr/include/stdlib.h
synstack.o: /usr/include/iso/stdlib_iso.h /usr/include/stdarg.h
synstack.o: /usr/include/iso/stdarg_iso.h synstack.h lex.h list.h
testidlist.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
testidlist.o: /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h
testidlist.o: /usr/include/sys/va_list.h /usr/include/stdio_tag.h
testidlist.o: /usr/include/stdio_impl.h /usr/include/malloc.h
testidlist.o: /usr/include/sys/types.h /usr/include/sys/machtypes.h
testidlist.o: /usr/include/sys/int_types.h /usr/include/sys/select.h
testidlist.o: /usr/include/sys/time.h /usr/include/sys/time.h
testidlist.o: /usr/include/strings.h /usr/include/string.h
testidlist.o: /usr/include/iso/string_iso.h
