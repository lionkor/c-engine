#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#define MALLOC malloc             /* void* MALLOC(size_t size) */
#define FREE free                 /* void FREE(void* pointer) */
#define CALLOC calloc             /* void* CALLOC(size_t nmemb, size_t size) */
#define REALLOC realloc           /* void* REALLOC(void* pointer, size_t size) */
#define REALLOCARRAY reallocarray /* void* REALLOCARRAY(void* pointer, size_t nmemb, size_t size) */
#define ASSERT assert             /* assert(cond) */

#define ASSERT_NOT_NULL(x) assert((x) != NULL)                                                      /* assert(cond) */
#define ASSERT_NOT_REACHABLE() printf("unreachable code reached in \"%s:%d\"", __FILE__, __LINE__); /* asserts if reached */

typedef unsigned int uint;

#define log_sdl_error(str) printf("%s:%d: SDL Error in %s (%s): %s\n", __FILE__, __LINE__, __FUNCTION__, str, SDL_GetError());

#endif // COMMON_H

