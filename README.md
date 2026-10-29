# IOOPM-inlupp2

**Authors:** Victor Fredman & Olivia Emilsson  
**Date:** October 2026  

## Design Decisions
* We decided to use Olivias hash, linked list and iterators. And we used Victors utils files.

**To compile and run all files:**

## We use a `Makefile` to build the programs. Open your terminal and run:

## To compile all tests
make all

## To run all tests
make test

## To run hash_table_tests.c and also see code coverage using gcov
make test_cov

## To run tests and check memory leaks (Using valgrind)
## Replace X with either (linked, freq, hash) depending on which file you want to test
make memtest_X 

## To clean out all new .o files before pushing to github for example
make clean

**Line and branch coverage from hash_table.c and linked_list.c**

File 'hash_table.c'
Lines executed:96.15% of 104
Branches executed:93.75% of 32
Taken at least once:87.50% of 32
Calls executed:80.95% of 21

File 'linked_list.c'
Lines executed:89.55% of 134
Branches executed:88.89% of 54
Taken at least once:62.96% of 54
Calls executed:37.50% of 8

# Initial Profiling Results
1. For each input, what are the top 3 functions?
Based on running the different text files (depends in sizes):
    1. `string_eq`
    2. `find_previous_entry`
    3. `string_hash_key` (and `cmp_freq_words` for the largest file).

2. For each input, are the top 3 functions in your code (that you have written), or is it in library functions?
All of the "biggest" functions above is writted and implemented by us in our own code!

3. Are the top 3 functions consistent across the inputs? Why? Why not?
Yes, mostly. The core functions related to the hash table are consistently over the different inputs. However, for the largest input, `cmp_freq_words` actually takes over the number 2 spot in terms of calls. This happens because larger text files contain a higher number of unique words. When the program finally sorts these words at the end, the sorting algorithm has a much larger array to process, resulting in  more calls to the function.

4. Is there some kind of trend? (Possibly several)
There is a big trend in terms of collision. Looking at the call logs for `string_eq` across the three different input sizes:
* Small input (1,000 words): 3,744 calls to `string_eq`
* Medium input (10,000 words): 115,860 calls to `string_eq`
* Large input (~17,000 words): 2,495,438 calls to `string_eq`
As the input grows, the number of string comparisons grows exponentially because the buckets get increasingly crowded.

5. Do the results correspond with your expectations?
Yes, pretty much. But I could not imagine the extreme results after executing the 16k-word text file. Calling a single function 2.5 million times is honestly crazy! I expected collisions because of the 17 buckets, but this large number i couldn´t see comming.

6. Based on these results, do you see a way to make your program go faster?
Yes, the main thing is to increase the number of buckets in the hash table. That would reduce the number of collisions and the amount of collision handling.