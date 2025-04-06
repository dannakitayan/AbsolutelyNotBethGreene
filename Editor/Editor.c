#include "Engine.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
	//Init Editor window;
	if (!InitEditorWindow()) return -1;

	while (!IsEngineDown)
	{

		SwapWindow();
	}

	ShutdownEngine();
	return 0;
}