# Querier Design 

## User interface/interaction
The only queriers interface with the user is while on the command-line, which needs 2 arguments

## Usgae
./querier [pageDir] [indexFileName]

## Input
command-line parameters

## Output
results of the query

## Utilized Functions

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

## Data structures

1. `counters`
2. `sets`
3. `hashtable`
4. `index`
5. `id_counts`
6. `two_ctrs`
