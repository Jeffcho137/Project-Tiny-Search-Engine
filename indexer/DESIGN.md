# Indexer Design

## Interface
Through command-line: requires 2 arguments

`indexer [pageDir] [indexFname]`

## Input/Output

* Input - command-line parameters described in Interface

* Output - words in the files are saved in `pageDir` to `indexFname` in specified format (`word id count [id count]`)

## Functions

1. `main`
2. `index data struture` 
3. `index_build`
4. `index_save`
5. `index_delete`
6. `index_find`
7. `index_insert`
8. `index_load`
9. `index_delete_help`
10. `index_save_help`
11. `index_save_counter_help`

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

* `counters`
* `hashtables`
* `index`



