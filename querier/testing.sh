#!/bin/bash
# Jeff Cho CS50 Summer 2020

cd ../common
make clean
make
cd -

# Variables
qq=./querier
fuzz=./fuzzquery
crawl=../crawler/data
index=~cs50/data/tse-output/letters-index-2/

# incorrect pageDirectory
$qq ../crawler $index

# incorrect IndexFilename
$qq $crawl ./crawler

# incorrect number of arguments
$qq $crawl $index ../crawler

# invalid queries
echo home_review | $qq $crawl $index

echo and review | $qq $crawl  $index

echo or home review | $qq $crawl $index

echo home and or review | $qq $crawl $index

echo hom search | $qq $crawl $index


# fuzzquery
#$fuzz $index 25 http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html | $qq $crawler $index
