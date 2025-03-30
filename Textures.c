#include "Textures.h"

Texture* TextureConstructor(const char* imageFilename, GLenum texureType, GLenum textureShaderLayer, GLenum format, GLenum pixelType)
{
	const char* path = GetAssetPath(imageFilename);
	//Load Image;
	SDL_Surface* surface = IMG_Load(path);
	if (!surface) {
		DEBUG_LOG("IMG_Load failed: %s", SDL_GetError());
		SDL_DestroySurface(surface);
		return NULL;
	}

	free(path);

	Texture* this = (Texture*)malloc(sizeof(Texture));
	this->Type = texureType;

	glGenTextures(1, &this->ID);
	glActiveTexture(textureShaderLayer);
	glBindTexture(texureType, this->ID);

	// Filters set up;
	glTexParameteri(texureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Load pixels
	glTexImage2D(texureType, 0, format, surface->w, surface->h, 0, format, pixelType, surface->pixels);

	glBindTexture(texureType, 0);
	SDL_DestroySurface(surface);

	return this;
}

void TextureDestructor(Texture* this)
{
	glDeleteTextures(1, &this->ID);
	free(this);
}

void TextureUnit(Shader* this, const char* parameter, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(this->ID, parameter);
	ActivateShader(this);
	glUniform1i(texUni, unit);
}

void TextureBind(Texture* this)
{
	glBindTexture(this->Type, this->ID);
}

void TextureUnbind(Texture* this)
{
	glBindTexture(this->Type, 0);
}