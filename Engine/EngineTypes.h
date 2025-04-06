#ifndef ENGINETYPES_H
#define ENGINETYPES_H

#include "ANBG_Engine.h"

typedef enum
{
	Up,
	Down,
	Left,
	Right
}Direction;

typedef enum
{
	AssetTexture,
	AssetMesh,
	AssetShader
}AssetType;

typedef void(*Callback)();
typedef void(*CallbackParameter)(void* data);

typedef struct {
	CallbackParameter WKey;
	CallbackParameter SKey;
	CallbackParameter AKey;
	CallbackParameter DKey;
	CallbackParameter EscKey;
	CallbackParameter EnterKey;
	CallbackParameter SpaceKey;
	void* Data;
}InputActions;

#endif
