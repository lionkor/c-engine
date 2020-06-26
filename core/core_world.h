#ifndef CORE_WORLD_H
#define CORE_WORLD_H

#include "common.h"

#ifndef CORE_WORLD_INTERNAL
typedef void World;
#else  // CORE_WORLD_INTERNAL
typedef struct {
    size_t placeholder;
} World;
#endif // CORE_WORLD_INTERNAL

extern World* world_create();
extern void   world_destroy(World* world);

#endif // CORE_WORLD_H
