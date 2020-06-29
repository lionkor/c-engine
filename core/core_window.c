#include "core_window.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <string.h>

HIDState* hid_state_create() {
    HIDState* state = (HIDState*)MALLOC(sizeof(HIDState));
    memset(state->keys, false, sizeof(state->keys));
    memset(state->keys, false, sizeof(state->mouse_buttons));
    return state;
}

void hid_state_destroy(HIDState* state) {
    FREE(state);
}

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

    window->hid_state = hid_state_create();

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
                SDL_Texture* texture = *(SDL_Texture**)vector_at(window->sdl_textures, i);
                SDL_DestroyTexture(texture);
            }
            vector_destroy(window->sdl_textures);
        }
        SDL_Quit();
        if (window->hid_state) {
            hid_state_destroy(window->hid_state);
        }
    }
    FREE(window);
}

static size_t key_for_sdl_keycode(SDL_Keycode code) {
    switch (code) {
    case SDLK_0:
        return KEY_0;
    case SDLK_1:
        return KEY_1;
    case SDLK_2:
        return KEY_2;
    case SDLK_3:
        return KEY_3;
    case SDLK_4:
        return KEY_4;
    case SDLK_5:
        return KEY_5;
    case SDLK_6:
        return KEY_6;
    case SDLK_7:
        return KEY_7;
    case SDLK_8:
        return KEY_8;
    case SDLK_9:
        return KEY_9;
    case SDLK_a:
        return KEY_A;
    case SDLK_b:
        return KEY_B;
    case SDLK_c:
        return KEY_C;
    case SDLK_d:
        return KEY_D;
    case SDLK_e:
        return KEY_E;
    case SDLK_f:
        return KEY_F;
    case SDLK_g:
        return KEY_G;
    case SDLK_h:
        return KEY_H;
    case SDLK_i:
        return KEY_I;
    case SDLK_j:
        return KEY_J;
    case SDLK_k:
        return KEY_K;
    case SDLK_l:
        return KEY_L;
    case SDLK_m:
        return KEY_M;
    case SDLK_n:
        return KEY_N;
    case SDLK_o:
        return KEY_O;
    case SDLK_p:
        return KEY_P;
    case SDLK_q:
        return KEY_Q;
    case SDLK_r:
        return KEY_R;
    case SDLK_s:
        return KEY_S;
    case SDLK_t:
        return KEY_T;
    case SDLK_u:
        return KEY_U;
    case SDLK_v:
        return KEY_V;
    case SDLK_w:
        return KEY_W;
    case SDLK_x:
        return KEY_X;
    case SDLK_y:
        return KEY_Y;
    case SDLK_z:
        return KEY_Z;
    case SDLK_SPACE:
        return KEY_SPACE;
    case SDLK_ESCAPE:
        return KEY_ESCAPE;
    default:
        printf("unhandled keycode: %s\n", SDL_GetScancodeName(SDL_GetScancodeFromKey(code)));
        return 0;
    }
}

void window_poll_events(Window* window, bool* keep_running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            if (keep_running) {
                *keep_running = false;
            }
            break;
        case SDL_KEYDOWN: {
            size_t key                   = key_for_sdl_keycode(e.key.keysym.sym);
            window->hid_state->keys[key] = true;
            break;
        }
        case SDL_KEYUP: {
            size_t key                   = key_for_sdl_keycode(e.key.keysym.sym);
            window->hid_state->keys[key] = false;
            break;
        }
        default:
            printf("event not handled: %d\n", e.type);
            break;
        }
    }
}

const HIDState* window_hid_state(Window* window) {
    ASSERT_NOT_NULL(window);
    ASSERT_NOT_NULL(window->hid_state);
    return window->hid_state;
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
    for (size_t i = 0; i < window->sdl_textures->size; ++i) {
        SDL_RenderCopy(window->sdl_renderer, *(SDL_Texture**)vector_at(window->sdl_textures, i), NULL, NULL);
    }
    SDL_RenderPresent(window->sdl_renderer);
}

bool window_load_texture(Window* window, const char* filename) {
    ASSERT_NOT_NULL(window);
    ASSERT_NOT_NULL(filename);
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if (surface == NULL) {
        log_sdl_error("SDL_LoadBMP");
        return false;
    }

    texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);

    if (texture == NULL) {
        log_sdl_error("SDL_CreateTextureFromSurface");
        return false;
    }
    SDL_FreeSurface(surface);
    vector_append(window->sdl_textures, &texture);
    return true;
}

const Vector* window_stored_textures(Window* window) {
    return window->sdl_textures;
}
