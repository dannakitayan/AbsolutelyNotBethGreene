#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include <stdlib.h>
#include "Debug.h"

typedef struct
{
	GLuint ID;
}EBO;

EBO* EBOConstructor(GLuint*, GLsizeiptr, GLuint);
void EBODestructor(EBO*);

void EBOBind(EBO*);
void EBOUnbind();

#endif
