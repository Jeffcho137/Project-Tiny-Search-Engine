/*
 * word.h - header file for 'word' module in common
 *
 * Jeff Cho CS50 Summer 2020
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "memory.h"

/********** NormalizeWord() **********/
/*
 * Input - 
 * word that is going to be normalized
 *
 * Ouput - 
 * the word in all lowercase
 *
 */

char* NormalizeWord(char *word);
