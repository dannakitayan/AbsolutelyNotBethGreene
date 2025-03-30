#include "VBO.h"

VBO* VBOConstructor(GLfloat* array, GLsizeiptr size, GLuint id)
{
	VBO* this = (VBO*)malloc(sizeof(VBO)); 
	if (!this) return NULL; 

	this->ID = id;

	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, size, array, GL_STATIC_DRAW);

	return this;
}

void VBODestructor(VBO* this)
{
	glDeleteBuffers(1, &this->ID);
	free(this);
}

void VBOBind(VBO* this)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	DEBUG_LOG("VBOBind 1");
}

void VBOUnbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}