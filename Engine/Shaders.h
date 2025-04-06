#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include "Debug.h"
#include "Settings.h"

#include "ANBG_Engine.h"

typedef struct {
    GLint model;
    GLint view;
    GLint projection;
    GLint time;
    GLint texture0;
    //Water shader;
    GLint AtlasSize;
    GLint TextureHeight;
} ShaderUniforms;

typedef struct
{
	GLuint ID;
    ShaderUniforms Uniforms;
}Shader;

ANBG_API Shader* ShaderConstructor(const char*, const char*);
ANBG_API void ShaderDestructor(Shader*);

ANBG_API void ActivateShader(Shader*);
ANBG_API char* ReadShader(const char*);

ANBG_API void SetShaderUniform1f(Shader*, const char*, float);
#endif