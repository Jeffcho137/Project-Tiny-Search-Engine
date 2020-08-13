# Lab 5: 91/100

## Makefiles: 11/13
  * -1: compilation error because you didn't include set, hashtable, and counter `.c` files. If you're not planning on using your own `.c` files to construct the `.a` file, you should use the command provided in the `libcs50` Makefile header comment
  * -1: compilation warning in `index.c`

## Git repo requirements: 4/5
  * -1: no git tag `lab5submit`; need to use `git tag lab5submit` and `git push --tags` commands

## Documentation & Testing: 17/17
  * Try to include more comments throughout your code

## Coding Style: 18/20
  * -2: should include `NULL` check or call `assertp` whenever you attempt to allocate memory

## Functionality: 33/35
  * -1: incorrect spacing in index file: need space between each word and the first document number, or else it messes up the spacing for every other docID/count pair in that line. Fixing this would also make your `index_load` a little simpler
  * -1: in `main` functions, you should `return 0` if everything worked, but you should call `exit` with an error code if any errors were encountered

## Memory leaks: 8/10
  * -2: memory leak from never freeing counter in `index_load`

# Nice job Jeff! Slack/email me if you have any questions.

