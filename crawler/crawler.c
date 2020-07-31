/*
 * crawler.c - implements header crawler.h from the crawler module
 * TSE Lab
 *
 * Usage: ./crawler [seedURL] [pageDir] [maxDepth]
 *
 * Jeff Cho CS50 Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "webpage.h"
#include "pagedir.h"
#include "hashtable.h"
#include "memory.h"
#include "bag.h"

inline static void logr(const char *action, char *url, int depth);
void crawler(char* seedURL, char* pageDir, int maxDepth);
void pagefetcher(webpage_t *page);
void pagescanner(webpage_t *webpage, bag_t *bag, hashtable_t *ht);


/*
 * logr() - prints the depth, action, and url at current
 *
 */

inline static void logr(const char *action, char *url, int depth){

	fprintf(stdout, "%2d %9s: %s \n", depth, action, url);

}

/*
 * main() - parses arguments and initializes other modules
 *
 */

int main(const int argc, char *argv[]){

	//check arguments
	if (argc != 4 || atoi(argv[3]) > 10 || atoi(argv[3]) < 0){
		
		//error statements
		fprintf(stderr, "arguments are not valid \n");
		fprintf(stderr, "Usage: ./crawler [seedURL] [pageDir] [0 < maxDepth < 10] \n");
		return 1;
	}
	
	// define/initialize usable variables
	int maxDepth = atoi(argv[3]);
	char *seedUrl = (char *)malloc((strlen(argv[1])) + 1);
	char *pageDir = (char *)malloc((strlen(argv[2]) + 10));
	strcpy(pageDir, argv[2]);
	strcat(pageDir, "/.crawler");
	strcpy(seedUrl, argv[1]);
	
	// check seedUrl
	if (!IsInternalURL(seedUrl)){
		
		//error statements
		fprintf(stderr, "seedURL not in server \n");
		fprintf(stderr, "Usage: ./crawler [seedURL] [pageDir] [0 < maxDepth < 10] \n");	
		
		// if error, free both
		free(pageDir);
		free(seedUrl);
		return 1;
	}

	// checking if file exists
	if (!verify_file(pageDir)){

		//error statements for failed checking
		fprintf(stderr, "Page Directory does not exist \n");
		fprintf(stderr, "Usage: ./crawler [seedURL] [pageDir] [0 < maxDepth < 10] \n");
		free(pageDir);
		free(seedUrl);
		return 1;
	}
	
	//run crawler
	crawler(seedUrl, argv[2], maxDepth);
	
	//free after crawler finished
	free(pageDir);
	return 0;

}


/*
 * hashtabledelete() - allows a pass to the hashtable
 *
 */
void hashtabledelete(void *item){
	;
}

/*
 * crawler() - uses a bag to track pages to explore, and hashtable to track pages seen; when it explores a page it gives the page URL to the pagefetcher, then the result to pagesaver, then to the pagescanner.
 *
 */

void crawler(char* seedURL, char* pageDir, int maxDepth){
	
	// initialize & define usable variables
	int id = 1;
	
	webpage_t *current;
	current = webpage_new(seedURL, 0, NULL);
	
	// new bag
	bag_t *pages;
	hashtable_t *seen;
	pages = bag_new();
	bag_insert(pages, current);
	
	// new hashtable
	seen = hashtable_new(100);
	hashtable_insert(seen, webpage_getURL(current), "");
	webpage_t *webpage;
	

	while ((webpage = bag_extract(pages)) != NULL){
		char *fp = (char *)malloc((strlen(pageDir) + 3)*sizeof(char*));	
		strcpy(fp, pageDir);
		strcat(fp, "/");
		char c[10];
		sprintf(c, "%d", id);
		strcat(fp, c);
		// adding the id to the end of the file name
		//sprintf(fp, "%s/%d", pageDir, id); 
		pagefetcher(webpage);

		if ((webpage_getHTML(webpage)) == NULL){
			
			// use logr to print message
			logr("File does not Exist", webpage_getURL(webpage), webpage_getDepth(webpage));

			// free the variables
			free(webpage);
			free(fp);
			free(seedURL);

			// deleting bag & hashtable
			bag_delete(pages, webpage_delete);
			hashtable_delete(seen, hashtabledelete);
			exit(1);
		}

		// save the page (from the pagedir.h)
		save_page(webpage, fp);
		
		//incrementation of id
		id++;

		// checking for max depth
		if (webpage_getDepth(webpage) < maxDepth){

			//message to realy the scan
			logr("Scanning Webpage", webpage_getURL(webpage), webpage_getDepth(webpage));
			pagescanner(webpage, pages, seen);
		}
		webpage_delete(webpage);
	}

	// at the end make sure to delete bag and hashtable
	bag_delete(pages, webpage_delete);
	hashtable_delete(seen, hashtabledelete);
}

/*
 * pagefetcher() - fetches the contents (HTML) for a page from a URL and returns
 */

void pagefetcher(webpage_t *page){

	// lets user know that page was fetched
	logr("Webpage Fetched", webpage_getURL(page), webpage_getDepth(page));
	webpage_fetch(page);
}

/*
 * pagescanner() - extracts URLS from a page and processes each one
 */

void pagescanner(webpage_t *webpage, bag_t *bag, hashtable_t *ht){
	
	int position = 0;
	char *next;

	while ((next = webpage_getNextURL(webpage, &position)) != NULL){
	
		// checking the url is internal
		if (IsInternalURL(next)){
			if (hashtable_insert(ht, next, "")){
				
				webpage_t *seen;
				seen  = webpage_new(next, webpage_getDepth(webpage)+1, NULL);
				logr("Webpage seen", webpage_getURL(seen), webpage_getDepth(webpage));
				
				bag_insert(bag, seen);
				logr("Page Inserted", webpage_getURL(seen), webpage_getDepth(webpage));

			}

			else{
				logr("Webpage Seen", next, webpage_getDepth(webpage));
				logr("Duplicate", next, webpage_getDepth(webpage));

				// free the url
				free(next);
			}
			
		}

		else{
			logr("Webpage Seen", next, webpage_getDepth(webpage));  
			logr("Unnecessary", next, webpage_getDepth(webpage)); 
			free(next);

		}
	}
}



