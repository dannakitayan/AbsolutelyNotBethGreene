#include "Settings.h"
#include "GameState.h"
#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h>

#include "Input.h"
#include "Camera.h"

#include <glad/glad.h>
#include "Shaders.h"
#include "Textures.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "Placeholders.h"
#include <cglm.h>

int main()
{
	Settings MainGame;
	MainGame.Name = "Repeated Call";
	MainGame.IsFullScreen = false;
	MainGame.Width = 640;
	MainGame.Height = 480;

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

	//Shader;
	Shader* shader = ShaderConstructor("default.vert", "default.frag");

	//Texture;
	Texture* texture = TextureConstructor("Textures\\Maps\\Episode2\\e2m.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	TextureUnit(shader, "tex0", 0);

	//VAO;
	VAO* vao = VAOConstructor(1);
	VAOBind(vao);

	//VBO & EBO;
	VBO* vbo = VBOConstructor(Vertices, sizeof(Vertices), 1);
	EBO* ebo = EBOConstructor(Indices, sizeof(Indices), 1);

	//Link;
	LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	EBOBind(ebo);

	//Unbing all;
	VAOUnbind();
	VBOUnbind();
	EBOUnbind();

	//SetTexture;
	GLuint tex0Uni = glGetUniformLocation(shader->ID, "tex0");
	ActivateShader(shader);

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

	while (!IsGameEnd)
	{
		//Input(&Event);
		Input(&Event, cameraInput);
		//Render loop;
		
		//Clear screen;
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ActivateShader(shader);
		CameraMatrix(camera, shader);
		mat4 model;

		glm_mat4_identity(model);
		
		vec3 modelPosition = { 0.0f, 0.0f, 0.0f };

		glm_translate(model, modelPosition);
		

		int modelLocation = glGetUniformLocation(shader->ID, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model[0]);

		

		TextureBind(texture);
		VAOBind(vao);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(Window);
	}

	VAODestructor(vao);
	VBODestructor(vbo);
	EBODestructor(ebo);
	ShaderDestructor(shader);
	TextureDestructor(texture);

	SDL_GL_DestroyContext(GLContext);
	SDL_DestroyWindow(Window);
	SDL_Quit();

	return 0;
}