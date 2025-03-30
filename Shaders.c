#include "Shaders.h"

char* ReadShader(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (!file) return NULL;

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(length + 1);
	if (!buffer) {
		fclose(file);
		return NULL;
	}

	fread(buffer, 1, length, file);
	buffer[length] = '\0';

	fclose(file);
	return buffer;
}

Shader* ShaderConstructor(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	Shader* this = (Shader*)malloc(sizeof(Shader));
	if (!this)
	{
		free(this);
		return NULL;
	}
	DEBUG_LOG("Shader instanced");

	const char* vertexShaderSource = ReadShader(vertexShaderFilename);
	const char* fragmentShaderSource = ReadShader(fragmentShaderFilename);

	if (!vertexShaderSource || !fragmentShaderSource) {
		free((void*)vertexShaderSource);
		free((void*)fragmentShaderSource);
		free(this);
		return NULL;
	}
	DEBUG_LOG("Shader files loaded");

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	DEBUG_LOG("Vertex shader compiled");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	DEBUG_LOG("Fragment shader compiled");

	this->ID = glCreateProgram();
	DEBUG_LOG("Shader id got = glCreateProgram()");

	glAttachShader(this->ID, vertexShader);
	DEBUG_LOG("glAttachShader(this->ID, vertexShader)");

	glAttachShader(this->ID, fragmentShader);
	DEBUG_LOG("glAttachShader(this->ID, fragmentShader)");

	glLinkProgram(this->ID);
	DEBUG_LOG("glLinkProgram");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	free((void*)vertexShaderSource);
	free((void*)fragmentShaderSource);
	vertexShaderSource = NULL;
	fragmentShaderSource = NULL;

	return this;
}

void ShaderDestructor(Shader* this)
{
	glDeleteProgram(this->ID);
	free(this);
	this = NULL;
}

void ActivateShader(Shader* this)
{
	glUseProgram(this->ID);
	//DEBUG_LOG("Shader activated");
}