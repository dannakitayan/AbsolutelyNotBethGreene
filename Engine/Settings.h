#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL3/SDL.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "Debug.h"
#include <string.h>

typedef struct
{
	char* Name;
	bool IsFullScreen;
	int Width;
	int Height;
	int TargetFPS;
}Settings;

static const char* baseCPFullPath = NULL;
static const char* baseCPFolderPath = "BaseCP\\";
static size_t baseCPFullPathSize = 0;

//Get the path to the BaseCP folder;
const char* GetBaseCPFolderPath(void);
const char* GetAssetPath(const char*);

#endif