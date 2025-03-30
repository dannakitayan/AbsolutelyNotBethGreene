#ifndef PROPS_H
#define PROPS_H

#include <stdbool.h>
#include <cglm.h>

typedef struct
{
	bool IsSolid;
	bool IsBreakable;
	bool IsDropItem;
	char Health;

	//Space;
	vec3 Position;
	short Angle;

	//Visual;
	char PropModelID;

	//Sounds;
	char DestroySoundID;

	//Collision;
	vec3 Poin1;
	vec3 Point2;
}Prop;

#endif