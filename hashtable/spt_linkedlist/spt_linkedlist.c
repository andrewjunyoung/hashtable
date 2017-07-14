#include <stdlib.h>
#include <string.h>

#include "spt_linkedlist.h"

// Note that checks on the nullity of the head are irrelevant in this code, but 
// act as a safety mechanism for later alterations

spt_linkedlist *spt_linkedlist_init(spt_linkedlist_node *node) {
    spt_linkedlist *list = malloc(sizeof(spt_linkedlist));

    list->head = node;
    list->size = 0;

    return list;
}

void spt_linkedlist_destroy(spt_linkedlist *list) {
    // spt_linkedlist_get_head(list) acts as a NULL check as well
    spt_linkedlist_node *head = spt_linkedlist_get_head(list);
    spt_linkedlist_node_destroy_all(head);

    free(list);
}

spt_linkedlist_node *spt_linkedlist_get_head(spt_linkedlist *list) {
    if (!list) return NULL;
    return list->head;
}

uint16_t spt_linkedlist_get_size(spt_linkedlist *list) {
    if (!list) return 0;
    return list->size;
}

bool spt_linkedlist_set_head(spt_linkedlist *list, spt_linkedlist_node *node) {
    // We allow the head -- and only the head -- to be set to null.
    // Be very careful about this case because it may cause memory leaks.
    if (!list) return false;

    list->head = node;
    return true;
}

spt_linkedlist_node *spt_linkedlist_get_last(spt_linkedlist *list) {
    spt_linkedlist_node *curr = spt_linkedlist_get_head(list);

    // Null-checks the list and the head
    if (!curr) return NULL;
   
    // If there is a next node, go to it.
    while (spt_linkedlist_node_has_next(curr)) {
        curr = spt_linkedlist_node_get_next(curr);
    }

    // MID: current_node != NULL
    return curr;
}

bool spt_linkedlist_add(spt_linkedlist *list, spt_linkedlist_node *node) {
    // We allow the string within he node to be null, but not the node itself
    if (!list || !node) return false;

    // Checks that list != NULL and HEAD == NULL
    if (!spt_linkedlist_get_head(list)) {
        spt_linkedlist_set_head(list, node);
        list->size++;

        return true;
    }

    // MID: list->head != NULL
    // Replace the head and add the new node
    spt_linkedlist_node *fmr_head = list->head;
    spt_linkedlist_node_set_next(node, fmr_head);

    list->head = node;
    list->size++;

    return true;
}

bool _spt_linkedlist_is_out_of_bounds(spt_linkedlist *list, uint16_t index) {
    return (index < 0 || index >= list->size);
}

spt_linkedlist_node *spt_linkedlist_get_node_by_index(spt_linkedlist *list, uint16_t index) {
    if (_spt_linkedlist_is_out_of_bounds(list, index)) return NULL;

    spt_linkedlist_node *curr = spt_linkedlist_get_head(list);

    // We have to include this check because of the spt_linkedlist_pop function
    // Other checks aren't needed because we don't allow nodes other than the 
    // head to be NULL
    if (!curr) return NULL;

    // MID: All nodes in this range are non-NULL
    // This relies on nodes not being able to be set to null, and size always 
    // being equal to the number of non-null nodes in the array
    for (int i = 0; i < index; i++) {
        curr = spt_linkedlist_node_get_next(curr);
    }

    return curr;
}

spt_linkedlist_node *spt_linkedlist_pop(spt_linkedlist *list) {
    spt_linkedlist_node *fmr_head = spt_linkedlist_get_head(list);
    if (!fmr_head) return NULL;

    spt_linkedlist_set_head(list, spt_linkedlist_node_get_next(fmr_head));
    list->size--;

    // The freeing of this node must be handled (properly -- not to delete the
    // rest of the list) later. 
    // Note that list->head may be NULL at this point.
    return fmr_head;
}

bool spt_linkedlist_set_tuple_at_index(spt_linkedlist *list, uint16_t index, str_ptr_tuple *tuple) {
    if (_spt_linkedlist_is_out_of_bounds(list, index)) return false;

    spt_linkedlist_node *node = spt_linkedlist_get_node_by_index(list, index);
    spt_linkedlist_node_set_tuple(node, tuple);
    return true;
}

bool spt_linkedlist_remove_node_by_str(spt_linkedlist *list, char *str) {
    spt_linkedlist_node *head = spt_linkedlist_get_head(list);
    if (!head) return false;

    spt_linkedlist_node *curr = spt_linkedlist_node_get_next(curr);

    // Singleton list case
    if (!curr) {
        str_ptr_tuple *head_tuple = spt_linkedlist_node_get_tuple(head);

        // Destroy iff the two strings match
        if (str_ptr_tuple_strcmp(head_tuple, str)) {
            spt_linkedlist_set_head(list, NULL);

            spt_linkedlist_node_destroy(head);

            return true;
        }

        return false;
    }

    // We use this alias for readability in our code
    spt_linkedlist_node *prev = head;

    while (curr) {
        str_ptr_tuple *tuple = spt_linkedlist_node_get_tuple(curr);

        spt_linkedlist_node *next = spt_linkedlist_node_get_next(curr);

        if (str_ptr_tuple_strcmp(tuple, str)) {
            spt_linkedlist_node_set_next(prev, next);
            spt_linkedlist_node_destroy(curr);
            return true;
        }

        prev = curr;
        curr = next;
    }

    return false;
}

str_ptr_tuple *spt_linkedlist_find_str(spt_linkedlist *list, char *str) {
    spt_linkedlist_node *curr = spt_linkedlist_get_head(list);

    while (curr) {
        str_ptr_tuple *tuple = spt_linkedlist_node_get_tuple(curr);
        if (str_ptr_tuple_strcmp(tuple, str)) {
            return tuple;
        }

        curr = spt_linkedlist_node_get_next(curr);
    }

    return NULL;
}
