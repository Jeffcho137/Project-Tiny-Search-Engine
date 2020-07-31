# TSE Lab Crawler Module
## Jeff Cho CS50 Summer 2020
## Purpose

The crawler module crawls the web while also fetching webpages and scanning them for the Urls. It then scans those Urls for even more Urls (getting deeper). After, the crawler module saves the webpages to a file with each of their own id.

## Usage

Building crawler module - `make`
Testing crawler module - `make test`
Saving log of test - `make test &> testing.out
Cleaning up - `make clean`

## Notes
`crawler` - crawls web, fetches webpages, and scans for urls
