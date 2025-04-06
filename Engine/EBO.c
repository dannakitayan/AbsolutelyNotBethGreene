#include "EBO.h"

EBO* EBOConstructor(GLuint* array, GLsizeiptr size, GLuint id)
{
	EBO* this = (EBO*)malloc(sizeof(EBO));
	if (!this) return NULL;

	this->ID = id;

	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, array, GL_STATIC_DRAW);

	return this;
}

void EBODestructor(EBO* this)
{
	glDeleteBuffers(1, &this->ID);
	free(this);
}

void EBOBind(EBO* this)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
	DEBUG_LOG("EBOBind 1");
}

void EBOUnbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}