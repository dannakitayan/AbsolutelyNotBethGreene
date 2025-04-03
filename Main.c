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
	MainGame.IsFullScreen = true;
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

	//Set up OpenGL version and a context;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	GLContext = SDL_GL_CreateContext(Window);
	if (!GLContext) {
		SDL_Log("OpenGL Context Error: %s", SDL_GetError());
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log("Failed to initialize GLAD");
		return -1;
	}

	int windowWidth, windowHeight;
	SDL_GetWindowSize(Window, &windowWidth, &windowHeight);

	//Adjusting the ratio;
	float targetAspect = (float)MainGame.Width / (float)MainGame.Height;
	float windowAspect = (float)windowWidth / (float)windowHeight;

	int viewportWidth, viewportHeight;
	int viewportX, viewportY;

	viewportHeight = windowHeight;
	viewportWidth = (int)(viewportHeight * targetAspect);

	//Centered horizontally;
	viewportX = (windowWidth - viewportWidth) / 2;
	viewportY = 0;

	//Set up viewport;
	//glViewport(0, 0, MainGame.Width, MainGame.Height);
	glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

	//Scene set up;
	CurrentSceneType = Intro0;
	InputActions currentInput;
	
	//EBO;
	EBO* ebo = EBOConstructor(Indices, IndicesSizeInBytes, 1);

	//Shaders;
	Shader* water = ShaderConstructor("Shaders\\default.vert", "Shaders\\water.frag");
	Shader* general = ShaderConstructor("Shaders\\default.vert", "Shaders\\default.frag");
	Shader* intro = ShaderConstructor("Shaders\\default.vert", "Shaders\\intro.frag");

	//Atlases;
	Texture* e2m = TextureConstructor("Textures\\Maps\\Episode2\\e2m.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture* ui = TextureConstructor("Textures\\UI\\base.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	//Meshes;
	Mesh* mesh = MeshConstructor(288, 432, 24, 984, 3120, 4440, 2, ebo, water, e2m);
	Mesh* ground = MeshConstructor(1056, 1008, 2064, 2160, 3120, 4440, 2, ebo, general, e2m);
	Mesh* up = MeshConstructor(1056, 1008, 2064, 3168, 3120, 4440, 2, ebo, general, e2m);

	//Intro;
	Mesh* introEngine = MeshConstructor(640, 480, 0, 0, 4096, 4096, 1, ebo, intro, ui);
	Mesh* introTeamGrisGris = MeshConstructor(640, 480, 0, 960, 4096, 4096, 1, ebo, intro, ui);

	//Unbing all;
	VAOUnbind();
	VBOUnbind();
	EBOUnbind();

	//Set up a camera;
	Camera* camera = CameraConstructor((float)MainGame.Width, (float)MainGame.Height, (vec2) { 0.0f, 0.0f });

	//Set up an inputs;
	InputActions cameraInput =
	{
		.Data = camera,
		.WKey = CameraUp,
		.SKey = CameraDown,
		.AKey = CameraLeft,
		.DKey = CameraRight
	};

	Uint32 PreviousTicks = SDL_GetTicks();
	Uint32 CurrentTicks;

	const float ShowIntroTime = 4.0f;
	float IntroFrameTime = ShowIntroTime;
	float TimeInSeconds = 0.0f;
	const float TimeScale = 100.0f;
	float DeltaTime = 0.0f;

	//Set target frame rate;

	//Vsync;
	SDL_GL_SetSwapInterval(1);

	//Alpha;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!IsGameEnd)
	{
		CurrentTicks = SDL_GetTicks();
		DeltaTime = (CurrentTicks - PreviousTicks) / 1000.0f;

		TimeInSeconds = SDL_GetTicks() / 1000.0f;
		//Input(&Event);
		switch (CurrentSceneType)
		{
		case Intro0:
			break;
		case Game:
			Input(&Event, cameraInput);
			break;
		}

		//Clear screen;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render;
		switch (CurrentSceneType)
		{
		case Intro0:
			IntroFrameTime -= DeltaTime;
			MeshDrawIntro(0, 0, introEngine, camera, IntroFrameTime);
			if (IntroFrameTime < 0.0f)
			{
				IntroFrameTime = ShowIntroTime;
				CurrentSceneType = Intro1;
			}
			break;
		case Intro1:
			IntroFrameTime -= DeltaTime;
			MeshDrawIntro(0, 0, introTeamGrisGris, camera, IntroFrameTime);
			if (IntroFrameTime < 0.0f)
			{
				IntroFrameTime = ShowIntroTime;
				CurrentSceneType = Game;
			}
			break;
		case Game:
			MeshDrawWater(864, 768, mesh, camera, TimeInSeconds);
			MeshDrawGeneral(0, 0, ground, camera);
			MeshDrawGeneral(0, 0, up, camera);
			//Render bottom map layer;

			//Render middle map layer;

			//Render game assets (Player and etc);

			//Render ghosts;

			//Render top map layer;

			//Render screen effects. Sequence: Rain, Fog, Darkness;

			//Render UI;
			break;
		}

		//Swapchain;
		SDL_GL_SwapWindow(Window);
		PreviousTicks = CurrentTicks;

		//Set 30 fps;
	}

	//Destructors;
	EBODestructor(ebo);
	//Shaders;
	ShaderDestructor(water);
	ShaderDestructor(general);
	ShaderDestructor(intro);
	//Atlases;
	TextureDestructor(e2m);
	TextureDestructor(ui);
	//Meshes;
	MeshDestructor(mesh);
	MeshDestructor(ground);
	MeshDestructor(up);
	MeshDestructor(introEngine);
	MeshDestructor(introTeamGrisGris);

	SDL_GL_DestroyContext(GLContext);
	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}