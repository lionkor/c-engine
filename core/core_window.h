#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "common.h"
#include "utils/utils_vector.h"

#ifndef CORE_WINDOW_INTERNAL

typedef void Window;

#else // CORE_WINDOW_INTERNAL

#include <SDL2/SDL.h>
typedef struct {
    size_t        width;
    size_t        height;
    char          title[256];
    SDL_Window*   sdl_window;
    SDL_Renderer* sdl_renderer;
    Vector*       sdl_textures;
} Window;

#endif // CORE_WINDOW_INTERNAL

extern Window* window_create(size_t width, size_t height, const char* title);
extern void    window_destroy(Window*);
extern void    window_draw(Window*);
extern bool    window_load_texture(Window*, const char* filename);
extern void    window_poll_events(Window*, bool* keep_running);

extern const Vector* window_stored_textures(Window*);
extern size_t        window_width(Window*);
extern size_t        window_height(Window*);
extern const char*   window_title(Window*);

#endif // CORE_WINDOW_H
