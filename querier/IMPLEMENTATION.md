# Querier Implementation

Querier searches an index for all of the words in each file of a crawler made directory, while ranking them.

## Usage
./querier [pageDir] [indexFileName]

## Implementation
The querier take a look at each file in the directory, scanning it for words queried by the user. Then based on the command line arugments we make sure that all the arguments by the user are valid before we proceed. One important process is to determine whether we are using a directory preproduced by the crawler. 

After we make sure all the parameters are valid, we create an index and go through all the lines in the file. Then we pass the index and load it from the indexFileName. Then the file is read from the input (stdin). Next we need to normalize the word and make sure the query search doesn't have any troublesome characters or symbols. We take the words and eventually place them into arrays. 

We then process the query and determine the count of the word based on the index. We then tally up all the queried words and begin to rank them. We do this by keeping the minimum score found. After the query is processed, we serach for the documents that satisfy the search, which means we allocated memory for the arrays of documents we will have. Then we print out all the relevant documents in descending order with the highest counts at the top.

## Pseudocode
1. execute command line as shown in the User Interface
2. check args, validate parameters, and initialize other usable modules
3. while the user inputs a query
4. we tokenize the query
5. then merge document scores based on the query
6. The arrays are filled
7. The arrays are sorted
8. print it out to user
9. prompt them again for another query

## Data Structures
* `index`
* `counters`
* `hashtable`
* `set`
* `id_count`
* `two_ctrs` 

## Functions in querier module

* `void inters_merge(void *arg, const int key, const int count);`
* `void union_merge(void *arg, const int key, const int count);`
* `void counting(void *arg, const int key, const int count);`
* `void fill_array(void *arg, const int key, const int count);`
* `void descend_sort(void *arg, int length);`
* `void delete_words(void *arg);`
* `void delete_docs(void *arg, int length);`
* `counters_t* scan_and(counters_t *ctr1, counters_t *ctr2);`
* `counters_t* scan_or(counters_t *ctr1, counters_t *ctr2);`
* `counters_t* scan_query(index_t *index, char** words);`
* `bool check_or(char *word);`
* `bool check_and(char *word);`
* `bool check_both(char *word);`
* `bool check_args(int argc, char *argv[]);`
* `char** read_file(FILE *fp);`
* `void process_query(FILE *fp, index_t *index, char** words, char* url);`
* `bool check_parse(char *word);`

