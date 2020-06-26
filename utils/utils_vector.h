#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H

#include "common.h"

typedef struct {
    void* data;
    // private, dont change
    size_t elem_size;
    size_t size;
    size_t capacity;
} Vector;

extern Vector* vector_create(size_t elem_size, size_t capacity);
extern void    vector_reserve(Vector*, size_t new_size);
extern void*   vector_append(Vector*, void* element);
extern void*   vector_at(Vector*, size_t index);
extern void    vector_destroy(Vector*);

#endif // UTILS_VECTOR_H
