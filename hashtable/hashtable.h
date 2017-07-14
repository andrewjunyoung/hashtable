#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "spt_linkedlist/spt_linkedlist.c"

#define MAX_STRING_LEN 8

typedef struct hashtable {
    uint16_t capacity;
    uint16_t size;
    spt_linkedlist* buckets;
    bool is_dynamic;
} hashtable;

// Names for these methods are largely based off the Java 7 implementation of 
// HashMap and its associated methods. hashtable_destroy is custom-named for
// clarity about its function

/* Returns the hash of the input string
 *
 * @param str The string to get the hash of
 * @return    The numerical value of the input str's hash value.
 */
unsigned long _hashtable_get_hash(char *str);

/* Creates an initialized hashtable in memory
 * Iff is_dynamic set, the capacity will increase automatically when items are
 * added to the hashtable. 
 * Else the capacity will double automatically when its size becomes greater 
 * than 3/4 * capacity
 *
 * @param capacity   The initial capacity of the hashtable. 
 * @param is_dynamic True iff the hashtable 
 * @return           A pointer to initialized hashtable's location in memory
 */
hashtable *hashtable_init(uint16_t capacity, bool is_dynamic);

/* Returns the hashtable's number of elements
 *
 * @param hashtable The hashtable for which to find the size
 * @return          The size of the hashtable parameter
 */
uint16_t hashtable_get_size(hashtable *table);

/* Returns the hashtable's max possible number of elements
 *
 * @param hashtable The hashtable for which to find the capacity
 * @return          The capacity of the hashtable parameter
 */
uint16_t hashtable_get_capacity(hashtable *table);

/* Returns true iff the input hashtable is dynamic
 *
 * @param hashtable The hashtable for which to perform the check
 * @return          True iff the hashtable is dynamic, else false
 */
bool hashtable_is_dynamic(hashtable *table);

/* Returns true iff there are no items in the hashtable
 *
 * @param hashtable The hashtable to perform the chec on
 * @return          True iff the hashtable is empty. Otherwise returns false.
 */
bool hashtable_is_empty(hashtable *table);

/* Returns true iff the hashtable contains an item with the associated key
 *
 * @param hashtable The hashtable to perform the check on
 * @param key       The key that is being checked for within the hashtable
 * @return          True iff hashtable contains the key, else returns false
 */
bool hashtable_contains_key(hashtable *table, char *key);

/* Returns true iff the hashtable contains a key for which value is the
 * associated value
 *
 * @param hashtabel The hashtable to perform the check on
 * @param value     The value that is being checked for within the hashtable
 * @return          True iff the hashtable contains a key for which value is the
 *                  associated value
 */
bool hashtable_contains_value(hashtable *table, void *value);

/* Returns an array containing all of the keys contained in the hashtable
 *
 * @param hashtable The hashtable to get keys from
 * @return          An array containing all the keys within the hashtable
 */
void **hashtable_get_key_set(hashtable *table);

/* Returns an array containing all of the values contained in the hashtable
 *
 * @param hashtable The hashtable to get values from
 * @return          An array containing all the values within the hashtable
 */
void **hashtable_get_value_set(hashtable *table);

/* Adds a key-value pair to a hashtable
 *
 * @param hashtable A pointer in memory to the hashtable to add the values to
 * @param key       The key to add to the hashtable
 * @param value     The value to associate with the key added
 * @return          True iff the key and value were successfully added to the 
 *                  hashtable. Else false.
 */
bool hashtable_add(hashtable *table, char *key, void *value);

/* Removes a key and its associated value from a hashtable
 *
 * @param hashtable A pointer in memory to the hashtable to remove the key and
 *                  assocaited value from
 * @param key       The key to remove from the hashtable
 * @return          True iff the key (and associated value) was successfully 
 *                  removed from the hashtable
 */
bool hashtable_remove(hashtable *table, char *key);

/* Returns the value associated with a key in a given hashtable
 *
 * @param hashtable The hashtable in which to look up the key and return a value
 *                  from
 * @param key       The key to look up in the hashtable
 * @return          The value associated with a key in a given hashtable
 */ 
void *hashtable_get(hashtable *table, char *key);

/* Makes a soft-copy of the currenct hashtable. The new hashtable will have the 
 * same capacity and properties as the input hashtable, but none of the elements
 * within it.
 *
 * @param hashtable The hashtable to make a copy of
 * @return          A pointer to the new hashtable copy
 */
void *hashtable_clone(hashtable *table);

/* Removes all elements from a hashtable, and frees all memory that the 
 * hashtable was using in memory.
 *
 * @param hashtable The hashtable to destroy
 */
void hashtable_destroy(hashtable *table);

/* Clears all elements from a hashtable, but does not free the memory of the 
 * hashtable, nor change its capacity.
 *
 * @param hashtable A pointer in memory to the hashtable to clear.
 */
void *hashtable_clear(hashtable *table);

bool hashtable_expand_and_rehash(hashtable *table);

uint16_t hashtable_get_bucket_id(hashtable *table, char *str);

spt_linkedlist *hashtable_get_bucket(hashtable *table, char *str);

void hashtable_get_keys(hashtable *table, char **keys);

void hashtable_get_values(hashtable *hashtable, char **values);

#endif 
