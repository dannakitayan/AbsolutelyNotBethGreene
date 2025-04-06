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
	const char* pathVertexShader = GetAssetPath(vertexShaderFilename);
	const char* pathFragmentShader = GetAssetPath(fragmentShaderFilename);

	Shader* this = (Shader*)malloc(sizeof(Shader));
	if (!this)
	{
		return NULL;
	}
	DEBUG_LOG("Shader instanced");

	const char* vertexShaderSource = ReadShader(pathVertexShader);
	const char* fragmentShaderSource = ReadShader(pathFragmentShader);

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

	//Set uniforms;
	//General uniforms;
	this->Uniforms.model = glGetUniformLocation(this->ID, "model");
	this->Uniforms.view = glGetUniformLocation(this->ID, "view");
	this->Uniforms.projection = glGetUniformLocation(this->ID, "projection");
	//Additional uniforms;
	this->Uniforms.time = glGetUniformLocation(this->ID, "Time");
	this->Uniforms.texture0 = glGetUniformLocation(this->ID, "tex0");
	this->Uniforms.AtlasSize = glGetUniformLocation(this->ID, "TextureSize");
	this->Uniforms.TextureHeight = glGetUniformLocation(this->ID, "WaveRepeatY");

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

void SetShaderUniform1f(Shader* this, const char* name, float value)
{
	GLint location = glGetUniformLocation(this->ID, name);
	if (location != -1)
		glUniform1f(location, value);
}