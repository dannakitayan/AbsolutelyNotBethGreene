#ifndef GENERALTYPES_H
#define GENERALTYPES_H

#include "ANBG_Engine.h"

typedef enum
{
	Forward,
	Backward,
	Left,
	Right
}Direction;

typedef enum
{
	Intro0,
	Intro1,
	Intro2,
	Intro3,
	Title,
	MainMenu,
	SettingsMenu,
	Game,
	Pause
}SceneState;

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
