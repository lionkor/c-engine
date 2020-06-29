#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "common.h"
#include "utils/utils_vector.h"

enum
{
    MB_LEFT,
    MB_RIGHT,
    MB_MIDDLE,
    MB_EXTRA1,
    MB_EXTRA2,
    // END
    MB_COUNT,
};

enum
{
    KEY_UNKNOWN = 0,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_SPACE,
    KEY_ESCAPE,
    // END
    KEY_COUNT
};

typedef struct
{
    bool mouse_buttons[MB_COUNT];
    bool keys[KEY_COUNT];
} HIDState;

#include <SDL2/SDL.h>
typedef struct {
    size_t        width;
    size_t        height;
    char          title[256];
    SDL_Window*   sdl_window;
    SDL_Renderer* sdl_renderer;
    Vector*       sdl_textures;
    HIDState*     hid_state;
} Window;


extern HIDState* hid_state_create();
extern void      hid_state_destroy(HIDState*);

extern Window*         window_create(size_t width, size_t height, const char* title);
extern void            window_destroy(Window*);
extern void            window_draw(Window*);
extern bool            window_load_texture(Window*, const char* filename);
extern void            window_poll_events(Window*, bool* keep_running);
extern const HIDState* window_hid_state(Window*);

extern const Vector* window_stored_textures(Window*);
extern size_t        window_width(Window*);
extern size_t        window_height(Window*);
extern const char*   window_title(Window*);

#endif // CORE_WINDOW_H
