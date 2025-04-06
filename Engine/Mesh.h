#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <cglm.h>
#include "Debug.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shaders.h"
#include "Textures.h"
#include "Camera.h"

#include "ANBG_Engine.h"

typedef struct
{
	GLfloat* Vertices;
	size_t SizeInBytes;
	Texture* MeshTexture;
	Shader* MeshShader;
	VBO* MeshVBO;
	VAO* MeshVAO;
	vec2 Position;
	mat4 Model;
	//For Water shader;
	vec2 AtlasSize;
	float TextureHeight;
}Mesh;

ANBG_API extern const GLuint Indices[];
ANBG_API extern const size_t IndicesSizeInBytes;

ANBG_API Mesh* MeshConstructor(int, int, int, int, int, int, int, EBO*, Shader*, Texture*);
ANBG_API void MeshDestructor(Mesh*);
ANBG_API void MeshDrawGeneral(int, int, Mesh*, Camera*);
ANBG_API void MeshDrawWater(int, int, Mesh*, Camera*, float);
ANBG_API void MeshDrawIntro(int, int, Mesh*, Camera*, float);
ANBG_API void MeshDrawLogo(int, int, Mesh*, Camera*, float);
ANBG_API void MeshDrawBackground(int, int, Mesh*, Camera*, float, vec3);

#endif 
