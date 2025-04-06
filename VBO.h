#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include <stdlib.h>
#include "Debug.h"

#include "ANBG_Engine.h"

typedef struct
{
	GLuint ID;
}VBO;

ANBG_API VBO* VBOConstructor(GLfloat*, GLsizeiptr);
ANBG_API void VBODestructor(VBO*);

ANBG_API void VBOBind(VBO*);
ANBG_API void VBOUnbind(void);

#endif
