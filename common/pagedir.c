/*
 * pagedir.c - module based on the pagedir.h file in the common directory
 * TSE Lab
 *
 * Jeff Cho CS50 Summer 2020
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"
#include "memory.h"

/********** save_page() **********/
/* see pagedir.h for more information about save_page */

void save_page(webpage_t *page, char *fname){
	
	// file variable declaration
	FILE *fp;

	// opening file & writing
	fp = fopen(fname, "w");
	assertp(fp, "cannot open file for writing\n");

	// inserting content from page to file
	fprintf(fp, "%s\n%d\n%s",webpage_getURL(page),webpage_getDepth(page),webpage_getHTML(page));
	
	// freeing fname
	free(fname);
	
	// closing the file
	fclose(fp);

}


/********** verify_file() **********/
/* see pagedir.h for more information about verify_file */

bool verify_file(char *fname){

	FILE *fp;
	if ((fp = fopen(fname, "w")) == NULL){

		return false;
	}

	else{

		fclose(fp);
		return true;

	}

}










