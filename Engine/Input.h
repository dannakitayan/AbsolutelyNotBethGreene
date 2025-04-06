#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h> 
#include "Engine.h"
#include "Debug.h"
#include "EngineTypes.h"

#include "ANBG_Engine.h"

ANBG_API void Input(SDL_Event*, InputActions);

#endif