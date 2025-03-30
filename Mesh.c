#include "Mesh.h"

const GLuint Indices[] =
{
	2, 0, 1, // CAB
	2, 1, 3, // CBD
};

const size_t IndicesSizeInBytes = sizeof(Indices);

Mesh* MeshConstructor(int sizeX, int sizeY, int tileStartX, int tileStartY, int atlasWidth, int atlasHeight, int multiplySize, EBO* ebo, Shader* shader, Texture* texture)
{
	Mesh* this = (Mesh*)malloc(sizeof(Mesh));
	if (!this)
	{
		return NULL;
	}
	DEBUG_LOG("Mesh instanced");

	float U0 = (float)tileStartX / (float)atlasWidth;
	float V0 = (float)tileStartY / (float)atlasHeight;
	float U1 = (float)(tileStartX + sizeX) / (float)atlasWidth;
	float V1 = (float)(tileStartY + sizeY) / (float)atlasHeight;

	float newSizeX = (float)(sizeX * multiplySize);
	float newSizeY = (float)(sizeY * multiplySize);

	GLfloat temporary[] =
	{
		0.0f, 0.0f, 0.0f,			1.0f, 1.0f, 1.0f,		U0, V0,	// A - 0
		newSizeX, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,		U1, V0,	// B - 1
		0.0f, newSizeY, 0.0f,		1.0f, 1.0f, 1.0f,		U0, V1,	// C - 2
		newSizeX, newSizeY, 0.0f,	1.0f, 1.0f, 1.0f,		U1, V1	// D - 3
	};

	this->Vertices = (GLfloat*)malloc(sizeof(temporary));
	if (!this->Vertices)
	{
		return NULL;
	}

	this->MeshShader = shader;
	this->MeshTexture = texture;

	this->SizeInBytes = sizeof(temporary);

	memcpy(this->Vertices, temporary, this->SizeInBytes);
	DEBUG_LOG("Size of vertices array, %d", this->SizeInBytes);

	this->MeshVAO = VAOConstructor();
	VAOBind(this->MeshVAO);

	this->MeshVBO = VBOConstructor(this->Vertices, this->SizeInBytes);
	LinkMeshAttrib(this->MeshVBO);

	if (!ebo)
	{
		return NULL;
	}

	EBOBind(ebo);

	return this;
}

void MeshDestructor(Mesh* this)
{
	free(this->Vertices);
	VAODestructor(this->MeshVAO);
	VBODestructor(this->MeshVBO);
	free(this);
}

void MeshDraw(int x, int y, Mesh* mesh, Camera* camera, bool isWater, float time)
{
	vec2 position = {(float)x, (float)y};
	glm_vec2_copy(position, mesh->Position);

	ActivateShader(mesh->MeshShader);

	if(isWater) SetShaderUniform1f(mesh->MeshShader, "Time", time);

	CameraMatrix(camera, mesh->MeshShader);

	glm_mat4_identity(mesh->Model);
	glm_translate(mesh->Model, (vec3) { mesh->Position[0], mesh->Position[1], 0.0f});

	int modelLocation = glGetUniformLocation(mesh->MeshShader->ID, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, mesh->Model[0]);

	TextureBind(mesh->MeshTexture);
	VAOBind(mesh->MeshVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		DEBUG_LOG("GL ERROR: %d", err);
	}
}