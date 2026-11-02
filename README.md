# IOOPM-inlupp2: Webstore

**Authors:** Victor Fredman & Olivia Emilsson  
**Date:** October 2026  

## Design Decisions
- We decided to use Olivia's hash table, linked list, and iterators as the foundational data structures.
- We used Victor's `utils.c` for robust input handling and format checking in the UI.
- The backend utilizes two hash tables (`name_to_merch` and `shelf_to_name`) to ensure fast lookups for both items and storage locations.
- **Memory Management:** We established a strict separation of concerns where the UI handles input, but the backend (`wh.c`) takes full ownership of its memory by copying strings using `strdup`.

## Instructions

We use a `Makefile` to build the programs. Open your terminal and run the following commands.

**To compile the program and all tests:**
`make all`

**To Compile the program**
`make ui`

**To run the main Webstore program:**
`make run`

**To run all unit tests:**
`make test`

**To run tests and check for memory leaks (Valgrind):**
`make memtest_warehouse`

**To see code coverage using gcov:**
`make coverage_warehouse`

**To clean out all compiled `.o` files (e.g., before pushing to GitHub):**
`make clean`

## Line and Branch Coverage

Measured with **gcov** (`gcov -b -c`).

### wh.c (CUnit unit tests, `make coverage_warehouse`)
- **Lines executed:** 87.91% of 273
- **Branches executed:** 100.00% of 82
- **Taken at least once:** 75.61% of 82
- **Calls executed:** 96.15% of 130

### ui.c (course script `webstoretest.txt`, `make coverage_ui`)
- **Lines executed:** 86.13% of 238
- **Branches executed:** 84.00% of 100
- **Taken at least once:** 59.00% of 100
- **Calls executed:** 85.14% of 148