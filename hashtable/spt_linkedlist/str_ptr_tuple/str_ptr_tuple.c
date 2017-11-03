#include <stdlib.h>
#include <string.h>

#include "../../../crash_test/err/err.h"
#include "str_ptr_tuple_struct.h"

str_ptr_tuple *str_ptr_tuple_init(char *str, void *ptr) {
    str_ptr_tuple *tuple = malloc(sizeof(str_ptr_tuple));

    tuple->str = str;
    tuple->ptr = ptr;

    return tuple;
}

void str_ptr_tuple_destroy(str_ptr_tuple *tuple) {
    free(tuple);
}

char *str_ptr_tuple_get_str(str_ptr_tuple *tuple) {
    if (!tuple) return NULL;

    return tuple->str;
}

void *str_ptr_tuple_get_ptr(str_ptr_tuple *tuple) {
    if (!tuple) return NULL;

    return tuple->ptr;
}

bool str_ptr_tuple_set_str(str_ptr_tuple *tuple, char *str) {
    if (!tuple) {
        err_init_and_handle(AERR_NULL_PTR, WARNING, __func__, "Attempted to set str in a null str_ptr_tuple", "Returning false");
        return false;
    }

    tuple->str = str;
    return true;
}

bool str_ptr_tuple_set_ptr(str_ptr_tuple *tuple, void *ptr) {
    if (!tuple) {
        err_init_and_handle(AERR_NULL_PTR, WARNING, __func__, "Attempted to set ptr in a null str_ptr_tuple", "Returning false");
        return false;
    }

    tuple->ptr = ptr;
    return true;
} 

bool str_ptr_tuple_strcmp(str_ptr_tuple *tuple, char *str) {
    return (strcmp(str_ptr_tuple_get_str(tuple), str) == 0);
}
