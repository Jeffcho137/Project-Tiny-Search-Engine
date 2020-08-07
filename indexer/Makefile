# Makefile for CS50 indexer
#
# Jeff Cho CS50 Summer 2020

L = ../libcs50
LC = ../common

CFLAGS= -Wall -pedantic -std=c11 -ggdb -I$L -I$(LC)
CC=gcc

PROG_IND = indexer
PROG_IND_TEST = indextest
OBJS_IND = indexer.o  $(LC)/pagedir.o $(LC)/word.o $(LC)/index.o 
OBJS_IND_TEST = indextest.o $(LC)/index.o
LLIBS = $L/libcs50-given.a $(LC)/common.a

.PHONY: all clean test

all: indexer indextest

indexer: $(OBJS_IND) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS_IND) $(LLIBS) -o indexer

indextest: $(OBJS_IND_TEST) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS_IND_TEST) $(LLIBS) -o indextest

indexer.o: $L/hashtable.h $L/counters.h $L/file.h $L/webpage.h $(LC)/index.h $(LC)/pagedir.h $(LC)/word.h 

indextest.o: $(LC)/index.h $L/file.h

test:
	bash -v testing.sh


clean:
	rm -rf *.dSYM
	rm -rf *~ *.o
	rm -rf $(PROG_IND_TEST) $(PROG_IND)
