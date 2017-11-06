#ifndef STR_PTR_TUPLE_H
#define STR_PTR_TUPLE_H

#include "str_ptr_tuple_struct.h"

/* Creates a new str_ptr_tuple with str and ptr as specified as params
 *
 * @param str   The str to be held in the str_ptr_tuple
 * @param ptr   The ptr to be held in the str_ptr_tuple
 * @return      A pointer in memory to the initialized str_ptr_tuple
 */
str_ptr_tuple *str_ptr_tuple_init(char *str, void *ptr);

/* Destroys the contents of a str_ptr_tuple by freeing all the space in memory
 * that it occupied.
 *
 * @param str_ptr_tuple The str_ptr_tuple to be destroyed
 */ 
void str_ptr_tuple_destroy(str_ptr_tuple *tuple);

/* Returns the str of the requested str_ptr_tuple
 *
 * @param str_ptr_tuple The str_ptr_tuple to return the str of
 * @return              The str of the tuple param
 */ 
char *str_ptr_tuple_get_str(str_ptr_tuple *tuple);

/* Returns the ptr of the specified str_ptr_tuple
 *
 * @param str_ptr_tuple The str_ptr_tuple to return the ptr of
 * @return              The ptr of the tuple param
 */ 
void *str_ptr_tuple_get_ptr(str_ptr_tuple *tuple);

/* Sets the ptr of a passed-in str_ptr_tuple to the value specified.
 *
 * @param str_ptr_tuple The str_ptr_tuple to change the str of
 * @param ptr           The new value for the str in the str_ptr_tuple
 * @return              True iff the tuple str was set to str
 */
bool str_ptr_tuple_set_str(str_ptr_tuple *tuple, char *str);

/* Sets the ptr of a passed-in str_ptr_tuple to the value specified.
 *
 * @param str_ptr_tuple The str_ptr_tuple to change the ptr of
 * @param ptr           The new value for the ptr of the str_ptr_tuple
 * @return              True iff the tuple ptr was set to str
 */
bool str_ptr_tuple_set_ptr(str_ptr_tuple *tuple, void *ptr);

/* Returns true iff the str ptr of the str_ptr_tuple equals the ptr passed in as 
 * a parameter.
 *
 * @param str_ptr_tuple The str_ptr_tuple to perform the check on
 * @param str           The string compared to the str_ptr_tuple's str.
 * @return              True iff the str_ptr_tuple's str is equal to str. Else 
 *                      false.
 */
bool str_ptr_tuple_strcmp(str_ptr_tuple *tuple, char *str);

#endif
