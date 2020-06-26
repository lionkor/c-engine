#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "common.h"

#ifndef CORE_WINDOW_INTERNAL
typedef void Window;
#else  // CORE_WINDOW_INTERNAL
typedef struct {
    size_t width;
    size_t height;
    char   title[256];
} Window;
#endif // CORE_WINDOW_INTERNAL

extern Window*     window_create(size_t width, size_t height, const char* title); /* creates a Window with specified size */
extern void        window_destroy(Window* window);                                /* closes and destroys the window */
extern size_t      window_width(Window* window);                                  /* width of the window */
extern size_t      window_height(Window* window);                                 /* height of the window */
extern const char* window_title(Window* window);                                  /* title of the window */

#endif // CORE_WINDOW_H
