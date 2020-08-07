/*
 * word.c - based on the header file word.h. Located in common directory
 *
 * Jeff Cho CS50 Summer 2020
 *
 */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "memory.h"

/********** NormalizeWord() **********/
// look at word.h for more information on function

char* NormalizeWord(char *word){

	char *theWord = calloc((strlen(word) + 1), sizeof(char *));
	for (int i = 0; i < strlen(word); i++){

		theWord[i] = tolower(word[i]);

	}

	free(word);
	return theWord;

}
