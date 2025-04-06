#ifndef TEXTURES_H
#define TEXTURES_H

#include<glad/glad.h>
#include <SDL_image.h>
#include "Shaders.h"
#include "Settings.h"
#include "Debug.h"

#include "ANBG_Engine.h"

typedef struct
{
	GLuint ID;
	GLenum Type;
}Texture;

ANBG_API Texture* TextureConstructor(const char*, GLenum, GLenum, GLenum, GLenum);
ANBG_API void TextureDestructor(Texture*);

ANBG_API void TextureUnit(Shader*, const char*, GLuint);
ANBG_API void TextureBind(Texture*);
ANBG_API void TextureUnbind(Texture*);

#endif
