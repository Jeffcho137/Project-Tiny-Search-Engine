# Makefile 'common' module 
#
# Jeff Cho CS50 Summer 2020

OBJS = pagedir.o index.o word.o list.o
LIB = common.a
L = ../libcs50

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L 
CC = gcc

# Building lib
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# object files depend on the header files
pagedir.o: $L/webpage.h pagedir.h 

index.o: $L/webpage.h $L/counters.h $L/hashtable.h $L/file.h index.h pagedir.h 

word.o: word.h

list.o: list.h

.PHONY: clean  

# clean up
clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f $(PROG)
