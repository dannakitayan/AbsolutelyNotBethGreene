#ifndef PLACEHOLDERS_H
#define PLACEHOLDERS_H

#include <glad/glad.h>

#define SizeX 408.0f
#define SizeY 480.0f

#define TileX 0.0f
#define TileY 0.0f
#define AtlasWidth 3120.0f
#define AtlasHeight 4440.0f

#define U0 TileX/AtlasWidth
#define V0 TileY/AtlasHeight
#define U1 (TileX+SizeX)/AtlasWidth
#define V1 (TileY+SizeY)/AtlasHeight

// Vertices coordinates
GLfloat Vertices[] =
{
	//X		Y	  Z		  R		G	  B			U	   V
	0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,		U0, V0,	// A - 0
	SizeX * 2, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,		U1, V0,	// B - 1
	0.0f, SizeY * 2, 0.0f,    1.0f, 1.0f, 1.0f,		U0, V1,	// C - 2
	SizeX * 2, SizeY * 2, 0.0f,   1.0f, 1.0f, 1.0f,		U1, V1	// D - 3
};

GLuint Indices[] =
{
	2, 0, 1, // CAB
	2, 1, 3, // CBD
};

#endif
