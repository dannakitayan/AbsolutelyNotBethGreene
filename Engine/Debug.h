#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#include <SDL3/SDL.h>
#define DEBUG_LOG(...) SDL_Log(__VA_ARGS__)
#else
#define DEBUG_LOG(...) ((void)0)
#endif

#endif
