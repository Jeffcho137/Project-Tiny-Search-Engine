# Jeff Cho CS50 Summer 2020
# TSE Lab 6

L = ../libcs50
M = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=gnu11 -ggdb -I $M -I $L
LLIBS = $M/common.a $L/libcs50-given.a 

all: querier fuzzquery

querier: querier.o
		$(CC) $(CFLAGS) $^ $(LLIBS) -o $@

fuzzquery: fuzzquery.o
		$(CC) $(CFLAGS) $^ $(LLIBS) -o $@

#Phony Targets
.PHONY: clean test valgrind

clean:
	rm -f core *core.*
	rm -f querier fuzzquery *~ *.o

test: 
	bash -v testing2.sh
valgrind:
	echo review home | valgrind ./querier ../tse-output/toscrape-depth-1 ../indexer/toscrape-depth-1-index
 				
