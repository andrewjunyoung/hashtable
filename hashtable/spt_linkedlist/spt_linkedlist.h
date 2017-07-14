#include "spt_linkedlist_node.c"

/* A struct storing an spt_linkedlist made up of one spt_linkedlist_node that is
 * linked to other spt_linkedlist_nodes
 *
 * @elem head The first node in the spt_linkedlist
 */
typedef struct spt_linkedlist {
    spt_linkedlist_node *head;
    uint16_t size;
} spt_linkedlist;

/* Creates an spt_linkedlist in memory and returns a pointer to it
 *
 * @param node The first node in the new spt_linkedlist
 * @return     A pointer to a newly created spt_linkedlist with node as its 
 *             first node
 */ 
spt_linkedlist *spt_linkedlist_init(spt_linkedlist_node *node);

/* Destroys all nodes in the spt_linkedlist and frees up the space in memory
 * that they occupied
 *
 * @param list The spt_linkedlist to be destroyed.
 */
void spt_linkedlist_destroy(spt_linkedlist *list);

/* Returns the number of nodes in the specified spt_linkedlist
 *
 * @pre        The linkedlist terminates
 * @param list The spt_linkedlist to get the size of
 * @return     The number of nodes in the spt_linkedlist
 */
uint16_t spt_linkedlist_get_size(spt_linkedlist *list);

/* Returns the first node in the specified spt_linkedlist
 *
 * @param list The spt_linkedlist to get the first node from
 * @return     A pointer to the head node in the spt_linkedlist
 */
spt_linkedlist_node *spt_linkedlist_get_head(spt_linkedlist *list);

/* Returns the last node in the specified spt_linkedlist
 *
 * @pre        The linkedlist terminates
 * @param list The spt_linkedlist to get the last node from
 * @return     A pointer to the last node in the spt_linkedlist
 */
spt_linkedlist_node *spt_linkedlist_get_last(spt_linkedlist *list);

/* Removes the node with the specified str from the spt_linkedlist
 *
 * @param list The spt_linkedlist to remove the node from
 * @param str  The value of str within the str_ptr_tuple we want to remove from
 *             the specified list
 * @return     True iff the node is successfully removed
 */
bool spt_linkedlist_remove_node_by_str(spt_linkedlist *list, char *str);

/* Sets the head of the linkedlist to the linkedlist's head's next, and returns
 * the former head node.
 *
 * @param list The list to pop the head from
 * @return     A pointer to the former head item of the list
 */
spt_linkedlist_node *spt_linkedlist_pop(spt_linkedlist *list);

/* Returns the node within the linkedlist that holds the specified str
 *
 * @param list The linkedlist to obtain the node from
 * @param str  The str of the node we are trying to find
 * @return     The str_ptr_tuple with string equal to str. If there is no match
 *             then returns NULL
 */
spt_linkedlist_node *spt_linkedlist_get_node_by_str(spt_linkedlist *list, char *str);

/* Returns the node at the index within the specified spt_linkedlist
 *
 * @param list  The spt_linkedlist which provides ordering to its nodes
 * @param index The numerical index of the tuple to get
 * @return      The tuple at the specified index within list. If there is no 
 *              match then returns NULL.
 */
spt_linkedlist_node *spt_linkedlist_get_node_by_index(spt_linkedlist *list, uint16_t index);

/* Sets the tuple at the specified index within the linkedlist
 *
 * @param list  The spt_linkedlist which provides ordering to its nodes
 * @param index The numerical index of the tuple to change
 * @param tuple The new value for the tuple at the specified index
 * @return      True iff the tuple was successfully set to the new value
 */
bool spt_linkedlist_set_tuple_at_index(spt_linkedlist *list, uint16_t index, str_ptr_tuple *tuple);

/* Adds an spt_linkedlist_node to the specified linkedlist
 *
 * @param list The list to add the new node to
 * @param node The node to add to the specified linkedlist
 * @return     True iff the node was successfully added to list
 */
bool spt_linkedlist_add(spt_linkedlist *list, spt_linkedlist_node *node);

/* Returns the tuple within the node where the str is equal to the specified str
 *
 * @param list The list to search within
 * @param str  The str to search for within the specified list
 * @return     The tuple within the list which has a str value equal to the str
 *             param. If no match found, then return NULL
 */
str_ptr_tuple *spt_linkedlist_find_str(spt_linkedlist *list, char *str);
