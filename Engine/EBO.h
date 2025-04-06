#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include <stdlib.h>
#include "Debug.h"

#include "ANBG_Engine.h"

typedef struct
{
	GLuint ID;
}EBO;

ANBG_API EBO* EBOConstructor(GLuint*, GLsizeiptr, GLuint);
ANBG_API void EBODestructor(EBO*);

ANBG_API void EBOBind(EBO*);
ANBG_API void EBOUnbind(void);

#endif
