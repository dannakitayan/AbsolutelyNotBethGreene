#ifndef VAO_H
#define VAO_H

#include"VBO.h"

typedef struct
{
	GLuint ID;
}VAO;

VAO* VAOConstructor();
void VAODestructor(VAO*);

void LinkAttrib(VBO*, GLuint, GLuint, GLenum, GLsizeiptr, void*);
void LinkMeshAttrib(VBO*);
void VAOBind(VAO*);
void VAOUnbind();

#endif
