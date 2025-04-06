#include "VAO.h"

VAO* VAOConstructor()
{
	VAO* this = (VAO*)malloc(sizeof(VAO));
	if (!this) return NULL;

	glGenVertexArrays(1, &this->ID);

	return this;
}

void VAODestructor(VAO* this)
{
	glDeleteVertexArrays(1, &this->ID);
	free(this);
}

void LinkAttrib(VBO* vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBOBind(vbo);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	DEBUG_LOG("Linked attribute (%d)", layout);
	VBOUnbind();
}

void LinkMeshAttrib(VBO* vbo)
{
	LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void VAOBind(VAO* this)
{
	glBindVertexArray(this->ID);
	//DEBUG_LOG("VAOBind 1");
}

void VAOUnbind()
{
	glBindVertexArray(0);
}