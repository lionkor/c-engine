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

    // initialize SDL

    uint res = SDL_Init(SDL_INIT_VIDEO);

    if (res != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return NULL;
    }

    window->sdl_window = SDL_CreateWindow(window->title, 20, 20, window->width, window->height, SDL_WINDOW_SHOWN);

    if (window->sdl_window == NULL) {
        printf("error creating SDL window: %s\n", SDL_GetError());
        window_destroy(window);
        return NULL;
    }

    window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (window->sdl_renderer == NULL) {
        printf("error creating SDL renderer: %s\n", SDL_GetError());
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
