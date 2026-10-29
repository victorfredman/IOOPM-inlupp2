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

## To see code coverage using gcov
make coverage_warehouse

## To run tests and check memory leaks (Using valgrind)
## Replace X with either (linked, freq, hash) depending on which file you want to test
make memtest_X 

## To clean out all new .o files before pushing to github for example
make clean

**Line and branch coverage**

File: wh.c
Lines executed: 87.04 of 270
Branches executed: 100.00% of 78
Taken at least once: 73.08 of 78
Calls executed 95.93 of 123