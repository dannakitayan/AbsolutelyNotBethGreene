#include "Engine.h"

bool IsEngineDown = false;
SDL_Window* Window = NULL;
SDL_Event Event;
SDL_GLContext GLContext = { 0 };

bool InitWindow(const char* windowName, int windowWidth, int windowHeight, bool isFullscreen)
{
	bool Result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
	if (!Result)
	{
		SDL_Log("SDL error: %s", SDL_GetError());
		return false;
	}

	Window = SDL_CreateWindow(windowName, windowWidth, windowHeight, SDL_WINDOW_OPENGL | (isFullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
	if (Window == NULL)
	{
		SDL_Log("SDL create a window error: %s", SDL_GetError());
		return false;
	}

	//Set up OpenGL version and a context;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	GLContext = SDL_GL_CreateContext(Window);
	if (!GLContext) {
		SDL_Log("OpenGL Context Error: %s", SDL_GetError());
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log("Failed to initialize GLAD");
		return false;
	}

	if (isFullscreen)
	{
		int FinalWindowWidth, FinalWindowHeight;
		SDL_GetWindowSize(Window, &FinalWindowWidth, &FinalWindowHeight);

		//Adjusting the ratio;
		float TargetAspect = (float)windowWidth / (float)windowHeight;
		float WindowAspect = (float)FinalWindowWidth / (float)FinalWindowHeight;

		int ViewportWidth, ViewportHeight;
		int ViewportX, ViewportY;

		ViewportHeight = FinalWindowWidth;
		ViewportWidth = (int)(ViewportHeight * TargetAspect);

		//Centered horizontally;
		ViewportX = (FinalWindowWidth - ViewportWidth) / 2;
		ViewportY = 0;

		glViewport(ViewportX, ViewportY, ViewportWidth, ViewportHeight);
	}
	else
	{
		SDL_SetWindowBordered(Window, true);
		glViewport(0, 0, windowWidth, windowHeight);
	}

	return true;
}

bool InitEditorWindow(void)
{
	return InitWindow("ANBG.Editor", 1280, 860, false);
}

bool InitGameWindow(const char* gameName, bool isFullscreen)
{
	return InitWindow(gameName, 640, 480, isFullscreen);
}

void ShutdownEngine(void)
{
	if (Window)
	{
		SDL_DestroyWindow(Window);
	}

	if (GLContext)
	{
		SDL_GL_DestroyContext(GLContext);
	}
	
	SDL_Quit();
}

void SwapWindow(void)
{
	if (!Window)
	{
		return;
	}
	SDL_GL_SwapWindow(Window);
}