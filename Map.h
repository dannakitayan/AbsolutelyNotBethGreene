#ifndef MAP_H
#define MAP_H

#include "Mesh.h"

typedef struct
{
	int TileSize[2];
	int TileStartPoint[2];
	int AtlasSize[2];
	char ShaderID; 
	char TextureID;
}Layer;

typedef struct
{
	int GlobalPosition[2];
	char* Collision;
	Layer Layers[3];
}Room;

typedef struct
{
	Room CurrentRoom;
	Mesh** MeshLayer;
}Map;

#endif
