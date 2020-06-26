#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#define CORE_WINDOW_INTERNAL
#include "core_window.h"

#include <string.h>

Window* window_create(size_t width, size_t height, const char* title) {
    Window* window = (Window*)MALLOC(sizeof(Window));
    ASSERT_NOT_NULL(window);
    memset(window, 0, sizeof(Window));
    window->width  = width;
    window->height = height;
    strncpy(window->title, title, sizeof(window->title));

    // vector of SDL_Texture*
    window->sdl_textures = vector_create(sizeof(SDL_Texture*), 0);

    // initialize SDL

    uint res = SDL_Init(SDL_INIT_VIDEO);

    if (res != 0) {
        log_sdl_error("SDL_Init");
        return NULL;
    }

    window->sdl_window = SDL_CreateWindow(window->title, 20, 20, window->width, window->height, SDL_WINDOW_SHOWN);

    if (window->sdl_window == NULL) {
        log_sdl_error("SDL_CreateWindow");
        window_destroy(window);
        return NULL;
    }

    window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (window->sdl_renderer == NULL) {
        log_sdl_error("SDL_CreateRenderer");
        window_destroy(window);
        return NULL;
    }

    return window;
}

void window_destroy(Window* window) {
    if (window) {
        if (window->sdl_renderer) {
            SDL_DestroyRenderer(window->sdl_renderer);
        }
        if (window->sdl_window) {
            SDL_DestroyWindow(window->sdl_window);
        }
        if (window->sdl_textures) {
            for (size_t i = 0; i < window->sdl_textures->size; ++i) {
                SDL_Texture* texture = vector_at(window->sdl_textures, i);
                FREE(texture);
            }
            vector_destroy(window->sdl_textures);
        }
        SDL_Quit();
    }
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

void window_draw(Window* window) {
    ASSERT_NOT_NULL(window);
    SDL_RenderClear(window->sdl_renderer);
    SDL_RenderPresent(window->sdl_renderer);
}
