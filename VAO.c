#include "VAO.h"

VAO* VAOConstructor(GLuint id)
{
	VAO* this = (VAO*)malloc(sizeof(VAO));
	if (!this) return NULL;

	this->ID = id;

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

void VAOBind(VAO* this)
{
	glBindVertexArray(this->ID);
	//DEBUG_LOG("VAOBind 1");
}

void VAOUnbind()
{
	glBindVertexArray(0);
}