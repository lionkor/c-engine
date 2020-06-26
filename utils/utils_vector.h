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


extern Vector* vector_create(size_t elem_size, size_t capacity); // elem_size may not be 0, capacity may be 0.
extern void    vector_reserve(Vector*, size_t new_size);         // ensures that the vector has the specified size allocated.
extern void*   vector_append(Vector*, void* element);            // resizes the array and mem-copies the value of *element with assumed size vector->elem_size.
extern void*   vector_at(Vector*, size_t index);                 // returns a pointer to that index in the array, or NULL on OOB.
extern void    vector_destroy(Vector*);

#endif // UTILS_VECTOR_H
