#ifndef MAP_H
#define MAP_H

typedef struct
{
	char AtlasID;
	int FrameArea[4];
}Layer;

typedef struct
{
	Layer Layers[3];
	char* Collision;
}Map;

#endif
