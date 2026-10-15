#pragma once

#include "linked_list.h"
#include <stddef.h>
#include "common.h"

 /**
* @file linked_list_struct.c
* @author Olivia Emilsson
* @date 29/9-26
* @brief The struct of a simple linked list

*/

typedef struct link link_t;

struct link
{ 
    elem_t element;
    link_t *next;
};

struct list
{
    link_t *first_link;
    link_t *last_link;
    size_t size;
};
