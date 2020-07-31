# Crawler Implementation

## Crawler
The crawler module crawls the web while also fetching webpages and scanning them for the Urls. It then scans those Urls for even more Urls (getting deeper). After, the crawler module saves the webpages to a file with each of their own id.

## Usage
./crawler [seedURL] [pageDir] [0 < maxDepth < 10]

Where seedURL is an internal, valid URL, pageDir is an existing subdirectory, and maxDepth is an int between 0 and 10 (inclusive).

## Implementation
The TSE Crawler is implemented as a dfs.

We check that first that the arguments on the command-line are valid.

After verifying the parameters are valid, we create a webpage variable for the given seedURL while also initializing other variables such as the id to keep track of files. We then create a bag that holds the unscanned pages, while also creating a hastable to hold the already seen webpages.

Next, we create another webpage, which will represent the next page. Then we store the location of where we're going to save by allocating memory. We then call fetch the page to update the HTML of page. The HTML is checked for nullity. If so, we know the page does not exist. However, if the HTML is not null, we continue by saving the page and then incrementing id. 

Next, the depth of the current page is checked to make sure it is less than the maxDepth provided. If it is, logr is used to show that we are scanning the page. We find the next embedded URL in page, and For each URL it finds, we check if the URL is internal, and if it is not, we ignore it, while also logging that we saw it. After this, we delete the page we found to free the memory and then extract the bag again until the page we extract is null, meaning we have exhauseted all of the embedded urls. 

Lastly, delete the bag while freeing all the remaining memory. We also delete the hashtable and free all the webpages again. 

## Pseudocode
The crawler runs:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules
3. make a webpage for the seedURL, marked with depth=0
4. add that page to the bag of webpages to crawl
5. add that URL to the hashtable of URLs seen
6. while there are more webpages to crawl, 
	5. extract a webpage (URL,depth) item from the bag of webpages to be crawled, 
	4. pause for at least one second, 
	6. use pagefetcher to retrieve the HTML for the page at that URL, 
	5. use pagesaver to write the webpage to the pageDirectory with a unique document ID, as described in the Requirements. 
	6. if the webpage depth is < maxDepth, explore the webpage to find links: 
		7. use pagescanner to parse the webpage to extract all its embedded URLs; 
		7. for each extracted URL, 
			8. 'normalize' the URL (see below) 
			9. if that URL is not 'internal' (see below), ignore it; 
			9. try to insert that URL into the hashtable of URLs seen 
				10. if it was already in the table, do nothing; 
				11. if it was added to the table, 
					12. make a new webpage for that URL, at depth+1 
					13. add the new webpage to the bag of webpages to be crawled

## Data Structures Modules

`webpage` 
`bag` 
`hashtable`
`set`

## Functions defined in crawler

`int main(const int argc, char *argv[])`
`void hashtabledelete(void *item)`
`inline static void logr(const char *action, char *url,  int depth)`
`void crawler(char* seedURL, char* pageDir, int maxDepth)`
`void pagefetcher(webpage_t *page)`
`void pagescanner(webpage_t *webpage, bag_t *bag, hashtable_t *ht)`

## Other functions in crawler
`void save_page(webpage_t *page, char *fname)`
`bool verify_file(char *fname)`
`bool IsInternalURL(char *url)`
`char *webpage_getNextURL(webpage_t *page, int *pos)`
`int webpage_getDepth(const webpage_t *page)`
`char *webpage_getURL(const webpage_t *page)`
`bool webpage_fetch(webpage_t * page)`
`char *webpage_getHTML(const webpage_t *page)`
`webpage_t *webpage_new(char *url, const int depth, char *html)`
`void webpage_delete(void *data)`


