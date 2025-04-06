#include "Input.h"

void Input(SDL_Event* event, InputActions actions)
{
	while (SDL_PollEvent(event))
	{
		switch (event->type)
		{
		case SDL_EVENT_QUIT:
			IsEngineDown = true;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
			{
				DEBUG_LOG("EXIT GAME");
				IsEngineDown = true;
				break;
			}

			if (event->key.scancode == SDL_SCANCODE_W)
			{
				//DEBUG_LOG("W");
				actions.WKey(actions.Data);
				break;
			}
			else if (event->key.scancode == SDL_SCANCODE_S)
			{
				//DEBUG_LOG("S");
				actions.SKey(actions.Data);
				break;
			}
			else if (event->key.scancode == SDL_SCANCODE_D)
			{
				//DEBUG_LOG("D");
				actions.DKey(actions.Data);
				break;
			}
			else if (event->key.scancode == SDL_SCANCODE_A)
			{
				//DEBUG_LOG("A");
				actions.AKey(actions.Data);
				break;
			}
		}
	}
}