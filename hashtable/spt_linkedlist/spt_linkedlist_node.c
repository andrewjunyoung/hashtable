#include <stdlib.h>
#include "spt_linkedlist_node.h"

spt_linkedlist_node *spt_linkedlist_node_init(str_ptr_tuple *tuple) {
    spt_linkedlist_node *node = malloc(sizeof(spt_linkedlist_node));

    node->tuple = tuple;
    node->next = NULL;

    return node;
}

void spt_linkedlist_node_destroy(spt_linkedlist_node *node) {
    // Using spt_linkedlist_node_get_tuple as a NULL check
    str_ptr_tuple_destroy(spt_linkedlist_node_get_tuple(node));
    free(node);
}

void spt_linkedlist_node_destroy_all(spt_linkedlist_node *node) {
    spt_linkedlist_node *curr = node;

    // We use spt_linkedlist_node_has_next rather than (curr->next != NULL)
    // because it includes a check for the case that node == NULL
    while (spt_linkedlist_node_has_next(curr)) {
        spt_linkedlist_node *next = curr->next;

        spt_linkedlist_node_destroy(curr);

        curr = next;
    }

    spt_linkedlist_node_destroy(curr);
}

spt_linkedlist_node *spt_linkedlist_node_get_next(spt_linkedlist_node *node) { 
    if (!node) return NULL;
    return node->next;
}

void *spt_linkedlist_node_get_tuple(spt_linkedlist_node *node) {
    if (!node) return NULL;
    return node->tuple;
}

bool spt_linkedlist_node_has_next(spt_linkedlist_node *node) {
    // This includes a null check on node
    return !(spt_linkedlist_node_get_next(node));
}

bool spt_linkedlist_node_set_next(spt_linkedlist_node *curr, spt_linkedlist_node *next) {
    if (!curr) return false;
    curr->next = next;
    return true;
}

bool spt_linkedlist_node_set_tuple(spt_linkedlist_node *node, str_ptr_tuple *tuple) {
    if (!node) return false;
    node->tuple = tuple;
    return true;
}
