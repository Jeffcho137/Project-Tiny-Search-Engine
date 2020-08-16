#!bin/bash
#
# testing.sh - script that runs and tests 'crawler' module
#
# Outputs the result of each test
#
# Jeff Cho CS50 Summer 2020

# no arguments
'./crawler'

# external server
./crawler https://www.bing.com testing 1

# server invalid
./crawler http://jeffcho137.com/~jeffrocks/index.html testing 1

# invalid depths                                                                 
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html testing -1                                                                          
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html testing 11 

# non-existent directory
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html test 1

# excessive many arguments
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html testing 1 test

# valid server with nonexistent URL
#./crawler http://old-www.cs.dartmouth.edu/~jeff/index.html testing 2

# valid test
./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html testing 2

# valid test & different seed
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html testing 3
