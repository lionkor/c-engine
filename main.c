#include <stdio.h>
#include "common.h"
#include "core.h"
#include "utils/utils_vector.h"
#include "io/io_load_texture.h"

int main() {
    Window* window = window_create(1280, 720, "Hello, World!");
    World*  world  = world_create();

    printf("window title: %s\n", window_title(window));

    bool success = window_load_texture(window, "test.bmp");
    if (!success)
        return 1;

    bool is_running = true;
    while (is_running) {
        window_draw(window);
        window_poll_events(window, &is_running);
    }

    world_destroy(world);
    world = NULL;
    window_destroy(window);
    window = NULL;
    return 0;
}
