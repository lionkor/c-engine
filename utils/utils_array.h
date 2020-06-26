#ifndef UTILS_ARRAY_H
#define UTILS_ARRAY_H

#include "common.h"

typedef struct {
    void* data;
    // private, dont change
    size_t elem_size;
    size_t size;
} Array;

extern Array* array_create(size_t elem_size, size_t count);
extern void   array_destroy(Array*);

#endif // UTILS_ARRAY_H

