#ifndef VAO_H
#define VAO_H

#include"VBO.h"

#include "ANBG_Engine.h"

typedef struct
{
	GLuint ID;
}VAO;

ANBG_API VAO* VAOConstructor(void);
ANBG_API void VAODestructor(VAO*);

ANBG_API void LinkAttrib(VBO*, GLuint, GLuint, GLenum, GLsizeiptr, void*);
ANBG_API void LinkMeshAttrib(VBO*);
ANBG_API void VAOBind(VAO*);
ANBG_API void VAOUnbind(void);

#endif
