#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include "Shaders.h"
#include <cglm.h>
#include <stdbool.h>
#include "GeneralTypes.h"

#include "ANBG_Engine.h"

typedef struct
{
	vec2 Position;
	bool IsLockedHorizontal;
	bool IsLockedVertical;
	float ViewportWidth;
	float ViewportHeight;
	mat4 View;
	mat4 Projection;
	mat4 Multiply;
}Camera;

ANBG_API Camera* CameraConstructor(float, float, vec2);
ANBG_API void CameraMatrix(Camera*, Shader*);
ANBG_API void SetLock(bool, bool);

ANBG_API CallbackParameter CameraUp(Camera*);
ANBG_API CallbackParameter CameraDown(Camera*);
ANBG_API CallbackParameter CameraLeft(Camera*);
ANBG_API CallbackParameter CameraRight(Camera*);

#endif