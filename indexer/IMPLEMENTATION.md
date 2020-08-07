# Implementation
## Indexer

Indexer creates an index for all of the words in each file based on a preproduced crawler directory.

## Usage
./indexer [pageDirectory] [indexFileName]

## Implementation
The indexer scans each file in the directory for words.

First the command-line arugments need to be checked. 

After ensuring the parameters are correct, we create an index.

We then building the index with the pageDir.

We search through each file in pageDirectory using `index_build`. It tracks the document, and for each file pageDirectory / id, we attempt to open the file. While there exists files to be read, we read the first line of the file using freadlinep. Also, we read in the depth at the second line; however, it is not used. A new initialized webpage is created. For each word that is found by `webpage_getNextWord`, we check to make sure the word is greater than 3 characters. If not, we do nothing with it. If the word is valid, we check if it is already in the index. If it is, we already have a counter in place for this word. If not, we can create one. After, we increment the counter at key, then insert it into the hashtable. We then free the word. We keep doing this until `webpage_getNextWord` returns null, meaning no more words were found.

We open FILE *fp, which is a file to write. We then calls hashtable_iterater. After the iterating is over, we close fp. `index_save_help` sets its own file to the fp passed to it, and it grabs the counter which hashtable_iterate provides. We then print out the word we are at in the hashtable. `index_save_counter_help` sets its own file to the fp passed to it, and then it prints out the key and the count of the word at the specified ID.

We then use `index_load` to insert a file into an index. It opens FILE *fp to write. Then, we initialize a character array c 101 locations to store in. This is where the document number OR the count will be sprintf'd to. We then keep track of which element of the line we're on. If `id_count` is false, we are at id. If it's true, the we are looking at the count at the previous id. The we also use an int i where 0 <= i <= 2. While there exists words to be fscanf'ed from fp, we check if the word is already in the index. If it is, we get the count. If not, we then make a new one. While there exists numbers to be read, we then check if `id_count` is true or false. Depending on that we set either id equal to the number read in, or count in that order. 

## Pseudocode
1. execute command line from  User Interface
2. check args, parameters, and initialize
3. while there exists a valid file to open
    1.  read the file for words
    2.  while there exists words to be found
        1. find word in that file
        2. if word is of greater length than 3,
        3. check if word is in the index
            1. if it is, store in its counter
            2. if not, create a new counter
        4. increment counter
        5. insert counter into table at that word
4. `index_save` to iterate through the index
5. `index_load` to read indexer produced file and load contents to an index
6. while there exists words to read
    1. scan word in file
    2. check if word is in the index
        1. if it is, store in its counter
        2. if not, create a new counter
    3. increment the counter at id
    4. insert the counter at that word

## Data Structures
* index
* counters
* hashtable
* set 

## Functions

* `int main(int argc, char *argv[])`
* `bool check_arguments(int argc, char *argv[])`
* `void index_build(index_t *index, char *dir)`
* `typedef struct index index_t`
* `index_t* index_new(const int numslots)`
* `void *index_find(index_t *index, const char *key)`
* `bool index_insert(index_t *index, const char *key, void *item)`
* `void index_save(char *fname, index_t *index)`
* `void index_save_help(void *arg, const char *key, void *item)`
* `void index_save_counter_help(void *arg, const int key, const int count)`
* `void index_load(char *fname, index_t *index)`
* `void index_delete(index_t *index)`
* `void index_delete_help(void *item)`

