/*
 * index.c - based on the header file index.h 
 * in index module in common directory
 *
 * Jeff Cho CS50 Summer 2020
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "pagedir.h"
#include "webpage.h"
#include "memory.h"
#include "index.h"
#include "word.h"
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include "jhash.h"
#include "set.h"

typedef struct index 
{
	hashtable_t *ht;
}index_t;

/********** index_new() **********/
/* see index.h for more information */

index_t* index_new(const int numslots)
{
	
	//allocating memory
	index_t *index = malloc(sizeof(index_t));
	
	//creating index hashtable
	index->ht = hashtable_new(numslots);
	return index;
}

/********** index_find() **********/
/* see index.h for more information */

void *index_find(index_t *index, const char *key)
{
	//finding the key for hashtable pointer in index
        return hashtable_find(index->ht, key);
	
}

	



/********** index_insert() **********/
/* see index.h for more information */

bool index_insert(index_t *index, const char *key, void *item)
{
	// checking if the hashtable insert worked
	if (hashtable_insert(index->ht, key, item)){
		return true;
	}
	else{
		return false;
	}
}

/********** index_save_counter_help **********/
/* see index.h for more information */
void index_save_counter_help(void *arg, const int key, const int count)
{
	FILE *fp = arg;
	fprintf(fp, "%d %d ", key, count);

}

/********** index_save_help() **********/
/* see index.h for more information */
void index_save_help(void *arg, const char *key, void *item)
{
	FILE *fp = arg;
	counters_t *counter = item;
	fprintf(fp, "%s ", key);

	counters_iterate(counter, fp, index_save_counter_help);
	fprintf(fp, "\n");
}

/********** index_save() **********/
/* see index.h for more information */

void index_save(char *fname, index_t *index)
{
	FILE *fp;
	fp = fopen(fname, "w");
	hashtable_iterate(index->ht, fp, index_save_help);
	fclose(fp);
			}
/********** index_load() **********/
/* see index.h for more information */

void index_load(char *fname, index_t *index)
{

	FILE *fp;
	fp = fopen(fname, "r");
	
	// declarations and assignments
	char c[101];
	int n;
	int id;
	int count;

	counters_t *counter;

	// some integer that is between 0 and 2 inclusive
	int increment = 0;

	bool id_count = true;

	// checking each word in the file
	while(fscanf(fp, "%s", &c[0]) == 1)
	{
		if (hashtable_find(index->ht, c) == NULL)
		{
			
			// if doesn't exist, create a new counter
			counter = counters_new();
		}
		else{
			// if it does exist we take it
			counter = hashtable_find(index->ht, c);
		}

		// checking in the file for numbers in ID count format
		while (fscanf(fp, "%d", &n) == 1)
		{
			if (id_count)
			{
				//if there is a id number we update
				id = n;
				id_count = false;
				increment++;
			}
			else{

				//if not, we still update
				count = n;
				id_count = true;
				increment++;

			}

			if (increment == 2)
			{

				//checking to make sure increment stays from 0 to 2 inclusive
				increment = 0;

				//updating the count 
				counters_set(counter, id, count);
				
				//inserting the new counter into the index hashtable
				hashtable_insert(index->ht, c, counter);
				//free(counter);
			}
		//free(counter);
		}

	//	counters_delete(counter);
	}
	//free(counter);
	fclose(fp);
}

/********** index_delete_help() **********/
/* see index.h for more information */
void index_delete_help(void *item)
{
	counters_t* delete = item;
	counters_delete(delete);

}

/********** index_delete() **********/
/* see index.h for more information */

void index_delete(index_t *index)
{
	hashtable_delete(index->ht, index_delete_help);
	free(index);
}

/********** index_get() ***********/
/* see index.h for more information */

hashtable_t* index_get(index_t *index)
{
	return index->ht;
}
