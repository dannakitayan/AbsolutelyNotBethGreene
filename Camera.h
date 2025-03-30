#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include "Shaders.h"
#include <cglm.h>
#include <stdbool.h>
#include "GeneralTypes.h"

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

Camera* CameraConstructor(float, float, vec2);
void CameraMatrix(Camera*, Shader*);
void SetLock(bool, bool);

CallbackParameter CameraUp(Camera*);
CallbackParameter CameraDown(Camera*);
CallbackParameter CameraLeft(Camera*);
CallbackParameter CameraRight(Camera*);

#endif