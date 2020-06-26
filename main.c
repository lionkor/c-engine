#include <stdio.h>
#include "common.h"
#include "core.h"
#include "utils/utils_vector.h"

int main() {
    Window* window = window_create(1280, 720, "Hello, World!");
    World*  world  = world_create();

    printf("window title: %s\n", window_title(window));

    Vector* vec = vector_create(sizeof(int), 0);

    for (int i = 0; i < 10; ++i) {
        vector_append(vec, &i);
    }

    for (int i = 0; i < 10; ++i) {
        printf("at %d: %d\n", i, *(int*)vector_at(vec, i));
    }

    vector_destroy(vec);
    vec = NULL;

    /*
    while (true) {
        window_draw(window);
    }
    */

    world_destroy(world);
    world = NULL;
    window_destroy(window);
    window = NULL;
    return 0;
}
