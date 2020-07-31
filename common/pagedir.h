/*
 * pagedir.h - header file for the pagedir module inside the common directory
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

/********** save_page **********/

/*
 * Input: 
 * fname - the name of the file being saved
 * page - the page being saved
 *
 * Output:
 * void - saves file
 */
void save_page(webpage_t *page, char *fname);

/*
 * FOR LAB 5
 */
/********** verify_crawler **********/
/*
 * Input:
 * dir - the directory being checked
 *
 * Output:
 * true - if directory exists
 * false - if directory does not exist
 */
bool verify_crawler(char *dir);

/********** verfiy_file **********/
/*
 * Input:
 * fname - the file being checked
 *
 * Output: 
 * true - if the file exists/can be opened
 * false - if file does not exist or cannot be opened
 */
bool verify_file(char *fname);

