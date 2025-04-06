#ifndef BUFFERS_H
#define BUFFERS_H

#include "uthash.h"
#include "Map.h"
#include "EngineTypes.h"

#include "ANBG_Engine.h"

//Assets storage;
typedef struct
{
	char ID;
	void* Data;
	AssetType Type;
	UT_hash_handle HashHandle;
}Container;

ANBG_API extern Container* TexturesStorage = NULL;
ANBG_API extern Container* ShadersStorage = NULL;
ANBG_API extern Container* MeshesStorage = NULL;


#endif
