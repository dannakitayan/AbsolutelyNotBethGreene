#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include "Debug.h"

typedef struct
{
	GLuint ID;
}Shader;

Shader* ShaderConstructor(const char*, const char*);
void ShaderDestructor(Shader*);

void ActivateShader(Shader*);
char* ReadShader(const char*);
#endif