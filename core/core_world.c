#define CORE_WORLD_INTERNAL
#include "core_world.h"

World* world_create() {
    World* world       = (World*)MALLOC(sizeof(World));
    world->placeholder = 100;
    return world;
}

void world_destroy(World* world) {
    FREE(world);
}
