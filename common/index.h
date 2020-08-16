/*
 * index.h - header file for the index module in common directory
 *
 * Jeff Cho CS50 Summer 2020
 *
 */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "word.h"
#include "memory.h"
#include "pagedir.h"
#include "counters.h"
#include "webpage.h"
#include "hashtable.h"
/********** struct index_t **********/
/*
 * Struct that holds ht which will be initialized. It loads 
 * the index, saves the index, deletes the index, inserts the 
 * index, finds the index.
 *
 */
typedef struct index index_t;

/********** index_new() **********/
/* Input: 
 * number of slots in the hashtable
 *  
 * Returns: index_t* 
 */

index_t* index_new(const int numslots);

/********** index_find() **********/
/* Return the item associated with the given key.
 * 
 * Caller provides:
 * valid pointer to hashtable, valid string for key.
 * 
 * We return:
 * pointer to the item corresponding to the given key, if found;
 * NULL if index is NULL, key is NULL, or key is not found.
 * 
 * Notes:
 * the index is unchanged by this operation.
 */
void *index_find(index_t *index, const char *key);

/********** index_insert() **********/
/* Insert item, identified by key (string), into the given index.
 * 
 * Caller provides:
 * valid pointer to index, valid string for key, valid pointer for item.
 * 
 * We return:
 * false if key exists in index, any parameter is NULL, or error;
 * true iff new item was inserted.
 *
 * Notes:
 * The key string is copied for use by the hashtable; that is, the module
 * is responsible for allocating memory for a copy of the key string, and
 * later deallocating that memory; thus, the caller is free to re-use or
 * deallocate its key string after this call.
 */
bool index_insert(index_t *index, const char *key, void *item);

/********** index_save() **********/
/* 
 * Input: 
 * file name to save to index
 * index
 * 
 * Returns: nothing
 * 
 * Opens the file and iterates through the hashtable
 * passes index_save_help as itemfunc
 */
void index_save(char *fname, index_t *index);

/********** index_save_help() **********/
/* 
 * Input: 
 * arg - file
 * key - key in hashtable/index
 * item - counter
 * 
 * Returns: 
 *
 * Prints key/word to pointer file.
 * Iterates through the counters at the specified key
 */
void index_save_help(void *arg, const char *key, void *item);

/********** index_save_counter_help() **********/
/* 
 * Input: 
 * arg - file
 * key - the key in the counter
 * count - the count at the specified key
 * 
 * Returns: 
 * Prints key at parameter pointer file
 * For each key in the counter, it prints the key and the count
 * to the specific file
 */

void index_save_counter_help(void *arg, const int key, const int count);

/********** index_load() **********/
/* 
 * Input: 
 * file
 * index
 * 
 * Returns: nothing 
 * 
 * Scans the file for each word on a line. 
 * For each word, insert id and specified count into hashtable.
 */
void index_load(char *fname, index_t *index);

/********** index_delete() **********/
/* 
 * Input: 
 * index to be deleted
 * 
 * Returns: nothing
 * 
 * Calls hashtable_delete on the pointer index's hashtable
 */

void index_delete(index_t *index);

/********** index_delete_help() **********/
/* 
 * Input: void *item
 * 
 * Returns: nothing
 *
 * Helps call counters_delete on parameter item.
 */

void index_delete_help(void *item);

/********** index_get() **********/
/*
 * Input: index 
 *
 * Returns: hashtable assocaited with index
 *
 */

hashtable_t* index_get(index_t *index);
