#ifndef HASHTABLE_STRUCT_H
#define HASHTABLE_STRUCT_H

#include "spt_linkedlist/spt_linkedlist.h"

#define MAX_STRING_LEN 256

typedef struct hashtable {
    uint16_t capacity;
    uint16_t size;
    spt_linkedlist* buckets;
    bool is_dynamic;
} hashtable;

#endif 
