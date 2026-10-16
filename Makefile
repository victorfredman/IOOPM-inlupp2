# Makefile for Assignment 2 (Inlupp 2)
# Authors: Victor Fredman & Simon Eriksson
# Date: 3 Oct 2026

# Compiler and standard flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17
CUNIT = -lcunit
VAL = valgrind --leak-check=full

# Phony targets
.PHONY: all test test_cov memtest_hash memtest_freq memtest_linked memtest_warehouse clean ui wh

# Default target
all: freq_count test_hash test_linked_list test_warehouse

# ==========================================
# UI OCH WAREHOUSE TARGETS
# ==========================================

wh:
	$(CC) $(CFLAGS) -c wh.c

ui:
	$(CC) $(CFLAGS) \
		ui.c wh.c \
		linked_list.c \
		list_iterator.c \
		hash_table.c \
		hash_table_iterator.c \
		hash_functions.c \
		utils.c \
		-o ui
	./ui

# ==========================================
# EXECUTABLE OCH TEST TARGETS
# ==========================================

freq_count: freq_count.o hash_table.o
	$(CC) $(CFLAGS) -o $@ $^

test_hash: hash_table_tests.o hash_table.o
	$(CC) $(CFLAGS) -o $@ $^ $(CUNIT)

test_linked_list: linked_list_tests.o linked_list.o
	$(CC) $(CFLAGS) -o $@ $^ $(CUNIT)

test_warehouse: warehouse_tests.o wh.o hash_table.o linked_list.o list_iterator.o hash_table_iterator.o hash_functions.o utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(CUNIT)

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Header dependencies
hash_table.o hash_table_tests.o freq_count.o: hash_table.h common.h
linked_list.o linked_list_tests.o: linked_list.h common.h
linked_list_tests.o: list_iterator.h
wh.o warehouse_tests.o: wh.h common.h

# ==========================================
# KÖRA ALLA TESTER
# ==========================================

test: test_hash test_linked_list test_warehouse
	./test_hash
	./test_linked_list
	./test_warehouse

# ==========================================
# MEMORY CHECKING TARGETS (VALGRIND)
# ==========================================

memtest_hash: test_hash
	$(VAL) ./test_hash

memtest_freq: freq_count
	$(VAL) ./freq_count test.txt

memtest_linked: test_linked_list
	$(VAL) ./test_linked_list

memtest_warehouse: test_warehouse
	$(VAL) ./test_warehouse

# ==========================================
# CLEANUP
# ==========================================

clean:
	rm -f *.o freq_count test_hash test_linked_list test_warehouse vgcore.* *.gcno *.gcda *.gcov freq_count_prof gmon.out profilering.txt ui