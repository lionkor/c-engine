#include "utils_array.h"
#include <string.h>

Array* array_create(size_t elem_size, size_t count) {
    ASSERT(elem_size != 0);
    ASSERT(count != 0);
    Array* array = (Array*)MALLOC(sizeof(Array));
    ASSERT_NOT_NULL(array);
    array->size      = count;
    array->elem_size = elem_size;
    array->data      = CALLOC(count, elem_size);
    memset(array->data, 0, count * elem_size);
    return array;
}

void array_destroy(Array* array) {
    if (array) {
        FREE(array->data);
    }
    FREE(array);
}
