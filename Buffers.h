#ifndef BUFFERS_H
#define BUFFERS_H

#include "uthash.h"
#include "Map.h"
#include "GeneralTypes.h"

//Assets storage;
typedef struct
{
	char ID;
	void* Data;
	AssetType Type;
	UT_hash_handle HashHandle;
}Container;

extern Container* TexturesStorage = NULL;
extern Container* ShadersStorage = NULL;
extern Container* MeshesStorage = NULL;


#endif
