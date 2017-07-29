CC = gcc
CFLAGS = -g -Wall -I. 
OBJS = interpreter.o symtab.o
TARGET = ml

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

interpreter.o: interpreter.c
	$(CC) $(CFLAGS) -c interpreter.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c
