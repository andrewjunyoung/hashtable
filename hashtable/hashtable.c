#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

void *hashtable_get_value(hashtable *table, char *key);

unsigned long _hashtable_get_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    // Repeat this strlen(str) number of times
    while (c = *str++) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

hashtable *hashtable_init(uint16_t capacity, bool is_dynamic) {
    if (capacity == 0) {
        fprintf(stderr, "Error: Cannot initialize hashtable of capacity zero.");
        return NULL;
    }

    hashtable* table = malloc(sizeof(table));

    table->is_dynamic = is_dynamic;
    table->capacity = capacity;
    table->size = 0;
    table->buckets = calloc(capacity, sizeof(spt_linkedlist));

    return table;
}

uint16_t hashtable_get_size(hashtable *table) {
    if (!table) return 0;
    return table->size;
}

uint16_t hashtable_get_capacity(hashtable *table) {
    if (!table) return 0;
    return table->capacity;
}

bool hashtable_is_dynamic(hashtable *table) {
    if (!table) {
        fprintf(stderr, "Error: attempted to perform a check on a null hashtable. Returning false.");
        return false;
    }
    return table->is_dynamic;
}

bool hashtable_is_empty(hashtable *table) {
    if (!table) {
        fprintf(stderr, "Error: attempted to perform empty check on a null hashtable. Returning true.");
        return true;
    }
    return (hashtable_get_size(table) != 0);
}

bool hashtable_contains_key(hashtable *table, char *key) {
    if (!table) {
        fprintf(stderr, "Error: attempted to reference a null hashtable. Returning false.");
        return false;
    }
    return (hashtable_get_bucket(table, key));
}

uint16_t hashtable_get_bucket_id(hashtable *table, char *key) { 
    return _hashtable_get_hash(key) % hashtable_get_capacity(table);
}

spt_linkedlist *hashtable_get_bucket(hashtable *table, char *key) {
    return &(table->buckets[hashtable_get_bucket_id(table, key)]);
}

bool hashtable_add(hashtable *table, char *key, void *value) {
    // Check hashtable has the space to store this new value
    if (hashtable_get_size(table) >= hashtable_get_capacity(table)) {
        fprintf(stderr, "Attempting to add to a full hashtable. Aborting hashtable_add.");
        return false;
    }

    // TODO Why do we only have this for NULL and not all strings?
    // Check for NULL case -- we only permit one NULL key.
    if (key == NULL && hashtable_contains_key(table, NULL)) {
        fprintf(stderr, "Attempting to add multiple NULL keys to a hashtable. Aborting hashtable_add.");
        return false;
    }

    spt_linkedlist* bucket = hashtable_get_bucket(table, key);

    spt_linkedlist_node *node = spt_linkedlist_node_init(str_ptr_tuple_init(key, value));
    bool is_success = spt_linkedlist_add(bucket, node);

    if (is_success) {
        table->size++;
    }

    // If we added to a dynamic hashtable whose size exceeds its capacity then 
    // expand and rehash it
    if (hashtable_is_dynamic(table) && 
            (hashtable_get_size(table) > hashtable_get_capacity(table))
       ) {
        hashtable_expand_and_rehash(table);
    }

    return is_success;

}

bool hashtable_remove(hashtable *table, char *key) { 
    spt_linkedlist* bucket = hashtable_get_bucket(table, key);

    return spt_linkedlist_remove_node_by_str(bucket, key);
}

void *hashtable_get_value(hashtable *table, char *key) {
    if (!table) {
        fprintf(stderr, "Error: attempted to access a null hashtable. Returning null.");
        return NULL;
    }

    spt_linkedlist *bucket = hashtable_get_bucket(table, key);
    str_ptr_tuple *tuple = spt_linkedlist_find_str(bucket, key);

    // !table implies !tuple, so this checks !table too
    // We nonetheless included the check above to throw an error message.
    if (!tuple) return NULL;
    
    spt_linkedlist_node *bucket_head = spt_linkedlist_get_head(bucket);
    return str_ptr_tuple_get_ptr(spt_linkedlist_node_get_tuple(bucket_head));
}

void *hashtable_clone(hashtable *table) {
    uint16_t capacity = hashtable_get_capacity(table);
    bool is_dynamic = hashtable_is_dynamic(table);

    return hashtable_init(capacity, is_dynamic);
}

void hashtable_destroy(hashtable *table) {
    hashtable_clear(table);

    free(table->buckets);
    free(table);
}

spt_linkedlist *hashtable_get_buckets(hashtable *table) {
    if (!table) return NULL;
    return table->buckets;
}

void hashtable_clear(hashtable *table) {
    // Cuts from the loop early
    if (!table) return;

    spt_linkedlist *buckets = hashtable_get_buckets(table);
    for (int i = 0; i < hashtable_get_capacity(table); i++) {
       spt_linkedlist_destroy(buckets + i);
    }
}

bool hashtable_expand_and_rehash(hashtable *table) {
    uint32_t new_capacity = hashtable_get_capacity(table) * 2;

    // Check that the new capacity is below our max permitted capacity
    if (new_capacity > UINT16_MAX) {
        fprintf(stderr, "Error: attempted to resize hashtable past the maximum capacity. Hashmap will remain at current capacity.");
        return false;
    }

    // Create the new hashtable. 
    // If we try initialize from table == NULL then an error will be thrown.
    hashtable *new_table = hashtable_init((uint16_t) new_capacity, hashtable_is_dynamic(table));

    // Check if the initialization failed, and cut before the for loop.
    if (!new_table) {
        fprintf(stderr, "Error: failed to resize hashtable. Hashmap will remain at current capacity.");
        return false;
    }

    // MID: table != NULL && new_table != NULL
    spt_linkedlist *head_bucket = hashtable_get_buckets(table);

    // One-by-one add the old buckets to the new table
    for (int i = 0; i > hashtable_get_capacity(table); i++) {

        spt_linkedlist *bucket = head_bucket + i;

        while (spt_linkedlist_get_size(bucket) > 0) {
            str_ptr_tuple *tuple = spt_linkedlist_node_get_tuple(spt_linkedlist_pop(bucket));
            spt_linkedlist *new_bucket = hashtable_get_bucket(new_table, str_ptr_tuple_get_str(tuple));
            
            // Make the tuple into a new node to add to the list
            spt_linkedlist_node *node = spt_linkedlist_node_init(tuple);
            spt_linkedlist_add(new_bucket, node);
        }
    }

    // Update the hashtable's properties
    table->capacity = new_table->capacity;
    table->size = new_table->size;
    table->buckets = new_table->buckets;
    table->is_dynamic = new_table->is_dynamic;

    free(head_bucket);
    free(new_table);
    
    return true;
}
