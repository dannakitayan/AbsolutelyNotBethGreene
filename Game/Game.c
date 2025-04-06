#include "Engine.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
	//Init Game window;
	if (!InitGameWindow("Corpse Party Repeated Call", true)) return -1;

	while (!IsEngineDown)
	{

		SwapWindow();
	}

	ShutdownEngine();
	return 0;
}