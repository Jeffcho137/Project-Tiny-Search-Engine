# Makefile for 'crawler' module
# 
# Jeff Cho CS50 Summer 2020

L = ../libcs50
LC = ../common

CFLAGS= -Wall -pedantic -std=c11 -ggdb -I$L -I$(LC)
CC = gcc

PROG = crawler
OBJS = crawler.o 
LLIBS = $L/libcs50-given.a $(LC)/common.a

.PHONY: all test clean

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) -o $(PROG)

crawler.o: $L/webpage.h $L/bag.h $L/hashtable.h $(LC)/pagedir.h

# testing 
test: 
	bash -v testing.sh

# cleaning up
clean:
	rm -rf *.dYSM
	rm -rf *~ *.o
	rm -rf $(PROG)
