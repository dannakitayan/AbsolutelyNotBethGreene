#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <cglm.h>

#include "Input.h"
#include "Mesh.h"
#include "Settings.h"
#include "GameState.h"

int main()
{
	Settings MainGame;
	MainGame.Name = "Repeated Call";
	MainGame.IsFullScreen = false;
	MainGame.Width = 640;
	MainGame.Height = 480;
	MainGame.TargetFPS = 30;

	//Initialize SDL3;
	SDL_Window* Window = NULL;
	SDL_Event Event;
	SDL_GLContext GLContext = {0};
	
	bool Result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
	if (!Result)
	{
		SDL_Log("SDL error: %s", SDL_GetError());
		return -1;
	}

	Window = SDL_CreateWindow(MainGame.Name, MainGame.Width, MainGame.Height, SDL_WINDOW_OPENGL | (MainGame.IsFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
	if (Window == NULL)
	{
		SDL_Log("SDL create a window error: %s", SDL_GetError());
		return -1;
	}

	GLContext = SDL_GL_CreateContext(Window);
	if (!GLContext) {
		SDL_Log("OpenGL Context Error: %s", SDL_GetError());
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, MainGame.Width, MainGame.Height);

	EBO* ebo = EBOConstructor(Indices, IndicesSizeInBytes, 1);

	//Shaders;
	Shader* water = ShaderConstructor("Shaders\\default.vert", "Shaders\\water.frag");
	Shader* general = ShaderConstructor("Shaders\\default.vert", "Shaders\\default.frag");

	//Atlases;
	Texture* e2m = TextureConstructor("Textures\\Maps\\Episode2\\e2m.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	//Meshes;
	Mesh* mesh = MeshConstructor(288, 432, 24, 984, 3120, 4440, 2, ebo, water, e2m);
	Mesh* ground = MeshConstructor(1056, 1008, 2064, 2160, 3120, 4440, 2, ebo, general, e2m);
	Mesh* up = MeshConstructor(1056, 1008, 2064, 3168, 3120, 4440, 2, ebo, general, e2m);

	//Unbing all;
	VAOUnbind();
	VBOUnbind();
	EBOUnbind();

	//Set up a camera;
	Camera* camera = CameraConstructor((float)MainGame.Width, (float)MainGame.Height, (vec2) { 0.0f, 0.0f });

	//Set up an input;
	InputActions cameraInput =
	{
		.Data = camera,
		.WKey = CameraUp,
		.SKey = CameraDown,
		.AKey = CameraLeft,
		.DKey = CameraRight
	};

	float timeInSeconds;

	//Set target frame rate;
	const int frameDelay = 1000 / MainGame.TargetFPS;
	Uint32 frameStart;
	int frameTime;

	//Vsync;
	SDL_GL_SetSwapInterval(0);

	//Alpha;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!IsGameEnd)
	{
		frameStart = SDL_GetTicks();
		timeInSeconds = SDL_GetTicks() / 1000.0f;
		//Input(&Event);
		Input(&Event, cameraInput);

		//Clear screen;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Render;
		MeshDraw(864, 768, mesh, camera, true, timeInSeconds);
		MeshDraw(0, 0, ground, camera, false, 0.0f);
		MeshDraw(0, 0, up, camera, false, 0.0f);
		

		//Swapchain;
		SDL_GL_SwapWindow(Window);

		//Set 30 fps;
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//Destructors;
	EBODestructor(ebo);
	//Shaders;
	ShaderDestructor(water);
	ShaderDestructor(general);
	//Atlases;
	TextureDestructor(e2m);
	//Meshes;
	MeshDestructor(mesh);
	MeshDestructor(ground);
	MeshDestructor(up);

	SDL_GL_DestroyContext(GLContext);
	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}