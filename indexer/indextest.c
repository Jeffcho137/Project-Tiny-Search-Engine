/*
 * indextest.c - tests indexer module
 * TSE Lab 5 Indexer
 *
 * Usage: ./indextest [oldIndexFilename] [newIndexFilename]
 *
 * Jeff Cho CS50 Summer 2020
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "memory.h"
#include "index.h"
#include "file.h"

bool check_args(int argc, char *argv[])
{

	// checking number of arguments
	if (argc != 3)
	{
		fprintf(stderr, "Insufficient number of arguments \n ");
		fprintf(stderr, "Usage: ./indextest [oldIndexFilename] [newIndexFilename] \n");
		return false;
	}

	FILE *fp;
	
	// checking whether file can be read
	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "%s cannot be opened for reading \n", argv[1]);
		fprintf(stderr, "Usage: ./indextest [oldIndexFilename] [newIndexFilename] \n");
		return false;
	}

	else{
		fclose(fp);
	}

	if ((fp = fopen(argv[2], "w")) == NULL)
	{
		fprintf(stderr, "%s cannot be opened for writing \n", argv[2]);
		fprintf(stderr, "Usage: ./indextest [oldIndexFilename] [newIndexFilename] \n");
		return false;
	}

	else{
		fclose(fp);
	}
	return true;

}

int main(int argc, char *argv[])
{

	// checking arguments
	if (check_args(argc, argv))
	{
		// opening the file for reading
		FILE *fp = fopen(argv[1], "r");

		// create index based on number of words in file
		int lines = lines_in_file(fp);
		index_t *index = index_new(lines);
		index_load(argv[1], index);
		index_save(argv[2], index);

		// delete index and other related index data
		index_delete(index);

		//close the file
		fclose(fp);
		return 0;

	}

	else{
		return 1;

	
	}
}
