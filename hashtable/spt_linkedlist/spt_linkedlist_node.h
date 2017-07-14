#ifndef SPT_LINKEDLIST_NODE_H
#define SPT_LINKEDLIST_NODE_H

#include <stdbool.h>
#include "str_ptr_tuple/str_ptr_tuple.c"

typedef struct spt_linkedlist_node spt_linkedlist_node;

struct spt_linkedlist_node {
    spt_linkedlist_node *next;
    str_ptr_tuple *tuple;
};

/* Creates a new spt_linkedlist_node and returns a pointer to it in memory. Does 
 * not set next
 *
 * @param value The value to set within the linkedlist_node
 * @return      A pointer to the locaction of the created spt_linkedlist_node
 */
spt_linkedlist_node *spt_linkedlist_node_init(str_ptr_tuple *tuple);

/* Clears the memory space occupied by the input linkedlist_node and its tuple
 * 
 * @param node A pointer to the location of the node to be destroyed
 */
void spt_linkedlist_node_destroy(spt_linkedlist_node *node);

/* The preferred method for destroying a linkedlist_node. Destroys the current
 * linkedlist_node and all its successors as well as all of their stored tuples.
 *
 * @param node The first spt_linkedlist_node to destroy
 */
void spt_linkedlist_node_destroy_all(spt_linkedlist_node *node);

/* Returns the next node in the linkedlist following the linkedlist_node input
 *
 * @param node The node whose successor we want to get
 * @return     The next node of the node param
 */
spt_linkedlist_node *spt_linkedlist_node_get_next(spt_linkedlist_node *node);

/* Returns the tuple stored in the current node in a linkedlist_node
 *
 * @param node The linkedlist_node whose tuple we want to find
 * @return     The tuple stored within the node passed in as a parameter
 */
void *spt_linkedlist_node_get_tuple(spt_linkedlist_node *node);

/* Returns true iff the node's next is not NULL
 *
 * @param node The node to perform the check on
 * @return     True iff the node's next is not NULL
 */
bool spt_linkedlist_node_has_next(spt_linkedlist_node *node);

/* Sets the value of next for the specified linkedlist_node
 *
 * @param node A pointer to the node whose successor we want to set
 * @param next A pointer to the node to become the next node after the node 
 *             param.
 * @return     True iff the next is successfully set
 */
bool spt_linkedlist_node_set_next(spt_linkedlist_node *curr, spt_linkedlist_node *next);

/* Sets the value of a specified linkedlist_node to the value specified as a 
 * parameter
 *
 * @param node  A pointer to the node to set the tuple of
 * @param value A pointer to the tuple to set the node's tuple to
 * @return      True iff the tuple is successfully set
 */
bool spt_linkedlist_node_set_tuple(spt_linkedlist_node *node, str_ptr_tuple *tuple);

#endif 
