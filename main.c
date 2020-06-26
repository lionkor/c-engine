#include <stdio.h>
#include "core.h"

int main() {
    Window* window = window_create(1280, 720, "Hello, World!");
    World*  world  = world_create();

    printf("window title: %s\n", window_title(window));

    world_destroy(world);
    world = NULL;
    window_destroy(window);
    window = NULL;
    return 0;
}
