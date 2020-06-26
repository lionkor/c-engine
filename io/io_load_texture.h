#ifndef IO_LOAD_TEXTURE_H
#define IO_LOAD_TEXTURE_H

#include <SDL2/SDL.h>

extern SDL_Texture* load_texture(const char* filename, SDL_Renderer* renderer);

#endif // IO_LOAD_TEXTURE_H
