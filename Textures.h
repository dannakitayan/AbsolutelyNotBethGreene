#ifndef TEXTURES_H
#define TEXTURES_H

#include<glad/glad.h>
#include <SDL_image.h>
#include "Shaders.h"
#include "Settings.h"
#include "Debug.h"

typedef struct
{
	GLuint ID;
	GLenum Type;
}Texture;

Texture* TextureConstructor(const char*, GLenum, GLenum, GLenum, GLenum);
void TextureDestructor(Texture*);

void TextureUnit(Shader*, const char*, GLuint);
void TextureBind(Texture*);
void TextureUnbind(Texture*);

#endif
