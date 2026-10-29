# Makefile for Assignment 2 (Inlupp 2)
# Authors: Victor Fredman & Olivia Emilsson
# Date: October 2026

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c17
CUNIT = -lcunit
VAL = valgrind --leak-check=full

.PHONY: all test coverage_warehouse memtest_warehouse clean ui

all: test_warehouse

ui: ui.c wh.c linked_list.c list_iterator.c hash_table.c hash_table_iterator.c hash_functions.c utils.c
	$(CC) $(CFLAGS) $^ -o ui

test_warehouse: warehouse_tests.o wh.o hash_table.o linked_list.o list_iterator.o hash_table_iterator.o hash_functions.o utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(CUNIT)

coverage_warehouse: clean
	gcc -Wall -Wextra -g -std=c17 --coverage -c wh.c -o wh.o
	gcc -Wall -Wextra -g -std=c17 --coverage -c warehouse_tests.c -o warehouse_tests.o
	gcc -Wall -Wextra -g -std=c17 -c hash_table.c -o hash_table.o
	gcc -Wall -Wextra -g -std=c17 -c linked_list.c -o linked_list.o
	gcc -Wall -Wextra -g -std=c17 -c list_iterator.c -o list_iterator.o
	gcc -Wall -Wextra -g -std=c17 -c hash_table_iterator.c -o hash_table_iterator.o
	gcc -Wall -Wextra -g -std=c17 -c hash_functions.c -o hash_functions.o
	gcc -Wall -Wextra -g -std=c17 -c utils.c -o utils.o
	gcc -Wall -Wextra -g -std=c17 --coverage -o test_warehouse warehouse_tests.o wh.o hash_table.o linked_list.o list_iterator.o hash_table_iterator.o hash_functions.o utils.o $(CUNIT)
	./test_warehouse
	gcov -b -c wh.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hash_table.o hash_table_tests.o: hash_table.h common.h
linked_list.o linked_list_tests.o: linked_list.h common.h
wh.o warehouse_tests.o: wh.h common.h

test: test_warehouse
	./test_warehouse

memtest_warehouse: test_warehouse
	$(VAL) ./test_warehouse

clean:
	rm -f *.o test_warehouse ui vgcore.* *.gcno *.gcda *.gcov