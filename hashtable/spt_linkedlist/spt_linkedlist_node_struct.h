#ifndef SPT_LINKEDLIST_NODE_H
#define SPT_LINKEDLIST_NODE_H

#include "str_ptr_tuple/str_ptr_tuple.h"

typedef struct spt_linkedlist_node spt_linkedlist_node;

typedef struct spt_linkedlist_node {
    spt_linkedlist_node *next;
    str_ptr_tuple *tuple;
} spt_linkedlist_node;

#endif 
