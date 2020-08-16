#!bin/bash
#
# testing.sh - bash script that tests the indexer module 
#
# Input: 
# None
#
# Output:
# the testing results
# 
# Jeff Cho CS50 Summer 2020
#

# test for no arguments
./indexer

# invalid file directory
./indexer jeff testing

# valid test
./indexer ../crawler/testing test

# valid file directory (but no preproduced crawler)
mkdir crawlertesting
./indexer crawlertesting test
rmdir crawlertesting

# unable to write to file
echo file > file_test
chmod ugo=rx file_test
./indexer ../crawler/testing file_test
chmod ugo=rwx file_test
more file_test
rm file_test -f

# testing writable file
echo '' > file_test
chmod ugo=rx file_test
./indextest testoutput file_test
chmod ugo=rwx file_test
more file_test
rm file_test -f


