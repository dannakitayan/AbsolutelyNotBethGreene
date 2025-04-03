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

extern const GLuint Indices[];
extern const size_t IndicesSizeInBytes;

Mesh* MeshConstructor(int, int, int, int, int, int, int, EBO*, Shader*, Texture*);
void MeshDestructor(Mesh*);
void MeshDrawGeneral(int, int, Mesh*, Camera*);
void MeshDrawWater(int, int, Mesh*, Camera*, float);
void MeshDrawIntro(int, int, Mesh*, Camera*, float);
void MeshDrawLogo(int, int, Mesh*, Camera*, float);
void MeshDrawBackground(int, int, Mesh*, Camera*, float, vec3);

#endif 
