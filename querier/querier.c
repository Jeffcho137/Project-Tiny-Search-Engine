/*
 * querier.c - TSE Lab module
 *
 * Usage: ./querier [pageDir] [indexFileName]
 *
 * Jeff Cho CS50 Summer 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pagedir.h"
#include "word.h"
#include "index.h"
#include "file.h"
#include "webpage.h"
#include "counters.h"
#include "hashtable.h"
#include "memory.h"

// function prototypes

void inters_merge(void *arg, const int key, const int count);
void union_merge(void *arg, const int key, const int count);
void counting(void *arg, const int key, const int count);
void fill_array(void *arg, const int key, const int count);
void descend_sort(void *arg, int length);
void delete_words(void *arg);
void delete_docs(void *arg, int length);
counters_t* scan_and(counters_t *ctr1, counters_t *ctr2);
counters_t* scan_or(counters_t *ctr1, counters_t *ctr2);
counters_t* scan_query(index_t *index, char** words);
bool check_or(char *word);
bool check_and(char *word);
bool check_both(char *word);
bool check_args(int argc, char *argv[]);
char** read_file(FILE *fp);
void process_query(FILE *fp, index_t *index, char** words, char* url);
bool check_parse(char *word);

typedef struct two_ctrs { counters_t *ctr1, *ctr2; }  two_ctrs_t;

typedef struct id_count { int id, count; } id_count_t;

/********** inters_merge **********/
/*
 * merges the doc scores on the intersection
 */
void inters_merge(void *arg, const int key, const int count)
{
	// creating a two_ctrs struct variable 
	two_ctrs_t *temp = arg;
	counters_t *ctr2 = temp->ctr2;
	counters_t *output = temp->ctr1;

	// check the counter
	if (counters_get(ctr2, key) > 0)
	{
		if (counters_get(ctr2, key) > count)
		{
			// if found merge the intersection
			counters_set(output, key, count);
		}

		else
		{
			counters_set(output, key, counters_get(ctr2, key));

		}
	}
}

/********** union_merge **********/
/*
 * merges the doc scores on the union
 */
void union_merge(void *arg, const int key, const int count)
{
	counters_t *output = arg;
	
	// check to see if key exists in counter
	if (counters_get(output, key) > 0)
	{
		//if so, add to the current amount
		counters_set(output, key, counters_get(output, key) + count);
	}

	else
	{
		// if not, we add it to the list
		counters_set(output, key, count);
	}
}
/********** counting **********/ 
/*
 * counts the number of counters
 */
void counting(void *arg, const int key, const int count)
{
	int *total = arg;
	// checking to see if total exists
	if (total != NULL && key > 0)
	{
		(*total)++;
	}
}
/********** fill_array **********/ 
/*
 * creates and fills an array of docs
 */
void fill_array(void *arg, const int key, const int count)
{
	id_count_t **docs = arg;
	id_count_t *ids = malloc(sizeof(id_count_t*));
	ids->id = key;
	ids->count = count;
	int i = 0;
	// going through the array
	while (docs[i] != NULL)
	{
		// increment
		i++;
	}
	// reassignment
	docs[i] = ids;
}
/********** descend_sort **********/
/*
 * sorts the array in descending order
 */
void descend_sort(void *arg, int length)
{
	id_count_t **c = arg;
	
	// nested for loop to go through whole array and compare
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (c[j]->count < c[i]->count)
			{
				
				// switching places in array
				id_count_t * temp = c[i];
				c[i] = c[j];
				c[j] = temp;

			}
		}
	}

}
/********** delete_words **********/
/*
 * deletes an array of words
 */
void delete_words(void *arg)
{
	char **words = arg;
	for (int i = 0; words[i] != NULL; i++)
	{
		free(words[i]);
	}
	
}
/********** delete docs **********/
/*
 * deletes an array of docs
 */
void delete_docs(void *arg, int length)
{
	id_count_t **ids = arg;
	for (int i = 0; i < length; i++)
	{
		free(ids[i]);
	}

	free(ids);

}
/********** scan_and **********/
/* 
 * takes care of 'and' seqs in the query
 */
counters_t* scan_and(counters_t *ctr1, counters_t *ctr2)
{
	counters_t *output = counters_new();
	two_ctrs_t two = { output, ctr2 };
	counters_iterate(ctr1, &two, inters_merge);
	return output;
}
/********** scan_or **********/
/*
 * takes care of the 'or' seqs in the query
 */
counters_t* scan_or(counters_t *ctr1, counters_t *ctr2)
{
	counters_t *output = counters_new();
	counters_iterate(ctr1, output, union_merge);
	counters_iterate(ctr2, output, union_merge);
	return output;
}
/********** scan_query **********/
/*
 * takes care of each of the tokes within the query
 */
counters_t *scan_query(index_t *index, char** words)
{
	counters_t *prev_count;
	counters_t *ct;
	
	// loop through words
	for (int i = 0; words[i] != NULL; i++)
	{
		// checking for or
		if (!check_or(words[i]))
		{
			
			// checking for and
			if(check_and(words[i]))
			{
				// increment
				i++;
			}

			// check and scan and cases
			if (hashtable_find(index_get(index), words[i]) != NULL)
			{
				ct = hashtable_find(index_get(index), words[i]);
				if (i == 0)
				{
					prev_count = ct;
				}
				prev_count = scan_and(prev_count, ct);

			}

			else

			{
				ct = counters_new();
				if (i == 0)
				{
					prev_count = ct;
				}
				prev_count = scan_and(prev_count, ct);
			}
		}

		else
		{
			i++;

			// check and scan or cases
			if (hashtable_find(index_get(index), words[i]) != NULL)
			{
				ct = hashtable_find(index_get(index), words[i]);
				prev_count = scan_or(prev_count, ct);

			}

			else{

				ct = counters_new();
				prev_count = scan_or(prev_count, ct);
			}
		}
	}
	//counters_delete(ct);
	return prev_count; 
}
/********** check_or **********/
/*
 * checks if there is an 'or'
 */
bool check_or(char *word)
{
	int i = strcmp(word, "or");
	if (i == 0)
	{
		return true;
	}

	return false;
}
/********** check_and **********/
/*
 * checks if there is an 'and'
 */
bool check_and(char *word)
{
	int i = strcmp(word, "and");
	if (i == 0)
	{
		return true;
	}
	return false;
}
/********** check_both **********/
/*
 * checks if there is an 'and' or 'or'
 */
bool check_both(char *word)
{
	return check_or(word) || check_and(word);
}
/********** check_args **********/
/*
 * checks the arguments and makes sure it's valid
 */
bool check_args(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Insufficient amount of args \n");
		fprintf(stderr, "Usage: ./querier [pageDir] [indexFileName] \n");
		return false;
	}

	if (!verify_crawler(argv[1]))
	{
		fprintf(stderr, "Directory is not produced by crawler or DNE \n");
		fprintf(stderr, "Usage: ./querier [pageDir] [indexFileName] \n");
		return false;
	}

	FILE *fp;
	if ((fp = fopen(argv[2], "r")) == NULL)
	{
		fprintf(stderr, "%s unable to be opened for reading \n", argv[2]);
		fprintf(stderr, "Usage: ./querier [pageDir] [indexFileName] \n");
		return false;
	}

	else
	{
		fclose(fp);
	}

	return true;
}
/********** read_file **********/
/*
 * tokenizes and reads the query input
 */
char** read_file(FILE *fp)
{
	int i  = 0;
	char **words = calloc(1,sizeof(char*));
	fprintf(stdout, "Query? \n");
	char *line = freadlinep(fp);

	if (line == NULL || strcmp(line,"") == 0)
	{
		free(line);
		delete_words(words);
		return words;

	}

	line = NormalizeWord(line);

	if (!(check_parse(line)))
	{
		char *new_line = malloc((strlen(line) + 1)*sizeof(char*));
		strcpy(new_line, line);

		char *new_word = strtok(new_line, " ");
		int c = 1;
		do{
			c++;
		} while ((new_word = strtok(NULL," ")));

		free(new_line);

		delete_words(words);
		free(words);
		words = calloc(c,sizeof(char*));

		char *word = strtok(line," ");
		do{
			words[i] = word;
			i++;
		} while ((word = strtok(NULL," ")));

		return words;

	}
	else
	{
		free(line);
		delete_words(words);
		return words;
	}
}
/********** process_query **********/
/*
 * formats and processed query, while also outputting the query results
 */
void process_query(FILE *fp, index_t *index, char** words, char* url)
{
	while (words != NULL && words[0] != NULL)
	{
		int i = 0;
		if (check_both(words[i]))
		{
			fprintf(stderr, "and/or cannot be first in the query \n");
			exit(1);
		}

		for (i = 1; words[i] != NULL; i++)
		{
			if (check_both(words[i]) && check_both(words[i-1]))
			{
				fprintf(stderr, "and/or cannot be consecutive in the query \n");
				exit(1);
			}
		}

		if (check_both(words[i-1]))
		{
			fprintf(stderr, "and/or cannot be last in query \n");
			exit(1);

		}

		fprintf(stdout, "Query: ");
		for (i = 0; words[i] != NULL; i++)
		{
			fprintf(stdout, "%s ", words[i]);
		}

		fprintf(stdout, "\n");
		counters_t *query = scan_query(index, words);

		int length = 0;
		counters_iterate(query,&length,counting);
		fprintf(stdout, "Matches %d ranked \n", length);
		//fprintf(stdout, "Score Doc Url \n");

		id_count_t **ids = calloc(length,sizeof(id_count_t*));
		counters_iterate(query,ids,fill_array);
		descend_sort(ids,length);
	//	printf(ids);
		for (int i = 0; i < length; i++)
		{
			char c[101];
			sprintf(c, "%d", ids[i]->id);
			char *dir = malloc((strlen(url) + 3)*sizeof(char*));
			strcpy(dir, url);
			strcat(dir, "/");
			strcat(dir, c);
			FILE *doc = fopen(dir, "r");
			char* new_url = freadlinep(doc);
			fclose(doc);

			fprintf(stdout, "Score %3d Doc %3d, %s \n", ids[i]->count, ids[i]->id, new_url);
			free(dir);
			free(new_url);
		}

		printf("-----------------------------------------------------\n");
		delete_docs(ids, length);
		counters_delete(query);
		words = read_file(fp);
	}

	delete_words(words);
}
/********** check_parse **********/ 
/*
 * checks to see if the tokens are proper
 */
bool check_parse(char *word)
{
	for (char *c = word; *c != '\0'; c++)
	{
		if (!isalpha(*c) && !isspace(*c))
		{
			fprintf(stderr, "non alphanumeric character %c in query \n", *c);
			return true;

		}
	}
	return false;
}


int main(int argc, char *argv[])
{
	if (check_args(argc, argv))
	{
		FILE *fp = fopen(argv[2], "r");
		int lines = lines_in_file(fp);
		fclose(fp);

		index_t *index = index_new(lines);
		char **words;
		index_load(argv[2], index);

		fp = stdin;
		words = read_file(fp);
		process_query(fp, index, words, argv[1]);

		free(words);
		index_delete(index);
		fclose(fp);
		return 0;

	}

	else
	{
		return 1;
	}
}
