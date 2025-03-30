#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include "Debug.h"
#include "Settings.h"

typedef struct {
    GLint model;
    GLint view;
    GLint projection;
    GLint time;
    GLint texture0;
} ShaderUniforms;

typedef struct
{
	GLuint ID;
    ShaderUniforms Uniforms;
}Shader;

Shader* ShaderConstructor(const char*, const char*);
void ShaderDestructor(Shader*);

void ActivateShader(Shader*);
char* ReadShader(const char*);

void SetShaderUniform1f(Shader*, const char*, float);
#endif