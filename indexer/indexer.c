/*
 * indexer.c - indexer module
 * TSE Lab 5
 *
 * Usage: ./indexer [pageDir] [indexFname]
 *
 * Jeff Cho CS50 Summer 2020
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "pagedir.h"
#include "webpage.h"
#include "counters.h"
#include "memory.h"
#include "index.h"
#include "word.h"
#include "hashtable.h"
#include "file.h"

bool check_arguments(int argc, char *argv[])
{
	// checking for right number of arguments
	if (argc != 3)
	{
		fprintf(stderr, "Insufficient number of arguments \n");
		fprintf(stderr, "Usage: ./indexer [pageDir] [indexFname] \n");
		return false;
	}

	// checking to see if page directory is crawler made or just does not exist
	if (!verify_crawler(argv[1]))
	{
		fprintf(stderr, "Page Directory is not a Crawler or DNE \n");
		fprintf(stderr, "Usage: ./indexer [pageDir] [indexFname] \n");
		return false;
	}

	FILE *fp;
	
	// checking to see if file can be opened for writing
	if ((fp = fopen(argv[2], "w")) == NULL)
	{
		fprintf(stderr, "%s cannot be opened for writing \n", argv[2]);
		fprintf(stderr, "Usage: ./indexer [pageDir] [indexFname] \n");
		return false;

	}

	else{
		fclose(fp);

	}

	return true;

}

void index_build(index_t *index, char *dir)
{
	int id = 1;
	char c[101];
	sprintf(c, "%d ", id);
	char* pageDir = malloc((strlen(dir) + 3)*sizeof(char* ));
       	strcpy(pageDir, dir);
	strcat(pageDir, "/");
	strcat(pageDir, c);
	FILE *fp;
	webpage_t *webpage;
	while ((fp = fopen(pageDir, "r")) != NULL)
	{
		int pos = 0;
		char *word;
		char *url;
		url = freadlinep(fp);
		char *n = freadlinep(fp);

		webpage = webpage_new(url, 0, freadfilep(fp));

		while ((word = webpage_getNextWord(webpage, &pos)) != NULL)
		{
			if (strlen(word) > 3)
			{
				word = NormalizeWord(word);
				counters_t *ctr;
				if (index_find(index, word) == NULL)
				{
					ctr = counters_new();
				}
				else{
					ctr = index_find(index, word);
				}
				counters_add(ctr, id);
				index_insert(index, word, ctr);
			}

			free(word);

		}

		// increment the id 
		id++;


		free(n);
		sprintf(c,"%d ", id);
		strcpy(pageDir, dir);
		strcat(pageDir, "/");
		strcat(pageDir, c);
		webpage_delete(webpage);
		fclose(fp);
	}

	free(pageDir);

}	

int main(int argc, char *argv[])
{

	// checking arguments
	if (check_arguments(argc, argv))
	{

		// creating new index 
		index_t *index = index_new(400);
		
		// building the index
		index_build(index, argv[1]);
		index_save(argv[2], index);
		
		// delete index and related data
		index_delete(index);
		return 0;
	}
	
	else{

		return 1;

	}

}






