wh: 
	gcc -I../inlupp1 -I../../labbar/lab2 -c wh.c
ui:
	gcc -g -Wall -I../inlupp1 -I../../labbar/lab2 \
	    ui.c wh.c \
	    linked_list.c \
	    list_iterator.c \
	   	hash_table.c \
	    hash_table_iterator.c \
	    hash_functions.c \
	    utils.c \
	    -o ui
	./ui

test:
	gcc -g -Wall \-I. \-I../inlupp1 \-I../../labbar/lab2 \-I/Users/oliviaemilsson/CUnitHome/include \tests.c wh.c \../inlupp1/linked_list.c \../inlupp1/list_iterator.c \../inlupp1/hash_table.c \../inlupp1/hash_table_iterator.c \../inlupp1/hash_functions.c \../../labbar/lab2/utils.c \-L/Users/oliviaemilsson/CUnitHome/lib \-lcunit \-o tests
	./tests