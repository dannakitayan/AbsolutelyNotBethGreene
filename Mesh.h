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
}Mesh;

extern const GLuint Indices[];
extern const size_t IndicesSizeInBytes;

Mesh* MeshConstructor(int, int, int, int, int, int, int, EBO*, Shader*, Texture*);
void MeshDestructor(Mesh*);
void MeshDraw(int, int, Mesh*, Camera*, bool, float);

#endif 
