#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h> 

#include <glad/glad.h>

#include "ANBG_Engine.h"

ANBG_API extern bool IsEngineDown;
ANBG_API extern SDL_Window* Window;
ANBG_API extern SDL_Event Event;
ANBG_API extern SDL_GLContext GLContext;

ANBG_API bool InitEditorWindow(void);
ANBG_API bool InitGameWindow(const char*, bool);
ANBG_API void ShutdownEngine(void);
ANBG_API void SwapWindow(void);

#endif