#ifndef SPT_LINKEDLIST_STRUCT_H
#define SPT_LINKEDLIST_STRUCT_H

#include <stdint.h>

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

#endif
