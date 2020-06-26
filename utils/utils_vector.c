#include "utils_vector.h"
#include <string.h>

Vector* vector_create(size_t elem_size, size_t capacity) {
    Vector* vector = (Vector*)MALLOC(sizeof(Vector));
    ASSERT_NOT_NULL(vector);
    ASSERT(elem_size != 0);
    memset(vector, 0, sizeof(Vector));
    vector->elem_size = elem_size;
    vector->size      = 0;
    if (capacity == 0) {
        capacity = 1;
    }
    vector->capacity = capacity;
    vector->data     = CALLOC(elem_size, capacity);
    ASSERT_NOT_NULL(vector->data);
    return vector;
}

void vector_reserve(Vector* vector, size_t new_size) {
    ASSERT_NOT_NULL(vector);
    if (vector->capacity >= new_size) {
        printf("vector capacity >= new_size\n");
        return;
    }
    void* new_data = REALLOCARRAY(vector->data, new_size, vector->elem_size);
    ASSERT_NOT_NULL(new_data);
    vector->data     = new_data;
    vector->capacity = new_size;
}

void* vector_append(Vector* vector, void* element) {
    ASSERT_NOT_NULL(vector);
    ASSERT_NOT_NULL(element);
    ASSERT(vector->size <= vector->capacity); // !(size > capacity)
    if (vector->size == vector->capacity) {
        printf("growing %p from %lu to ", vector, vector->capacity);
        vector_reserve(vector, vector->capacity + vector->capacity / 1.5 + 1);
        printf("%lu\n", vector->capacity);
    } else {
        printf("not growing\n");
    }
    size_t index = vector->size;
    void*  iter  = memcpy(vector->data + index * vector->elem_size, element, vector->elem_size);
    vector->size += 1;
    return iter;
}

extern void* vector_at(Vector* vector, size_t index) {
    ASSERT_NOT_NULL(vector);
    if (index >= vector->size) {
        printf("tried to access element %lu in vector %p, out of range (size = %lu)\n", index, vector, vector->size);
        return NULL;
    }
    printf("accessing %lu in %p\n", index, vector);
    return vector->data + index * vector->elem_size;
}

void vector_destroy(Vector* vector) {
    if (vector) {
        FREE(vector->data);
    }
    FREE(vector);
}
