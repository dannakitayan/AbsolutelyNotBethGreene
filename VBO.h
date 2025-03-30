#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include <stdlib.h>
#include "Debug.h"

typedef struct
{
	GLuint ID;
}VBO;

VBO* VBOConstructor(GLfloat*, GLsizeiptr, GLuint);
void VBODestructor(VBO*);

void VBOBind(VBO*);
void VBOUnbind();

#endif
