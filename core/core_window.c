#define CORE_WINDOW_INTERNAL
#include "core_window.h"

#include <string.h>

Window* window_create(size_t width, size_t height, const char* title) {
    Window* window = (Window*)MALLOC(sizeof(Window));
    ASSERT_NOT_NULL(window);
    window->width  = width;
    window->height = height;
    strncpy(window->title, title, sizeof(window->title));
    return window;
}

void window_destroy(Window* window) {
    FREE(window);
}

size_t window_width(Window* window) {
    ASSERT_NOT_NULL(window);
    return window->width;
}

size_t window_height(Window* window) {
    ASSERT_NOT_NULL(window);
    return window->height;
}

const char* window_title(Window* window) {
    ASSERT_NOT_NULL(window);
    return window->title;
}
