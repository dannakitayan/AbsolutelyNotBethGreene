#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <stdlib.h>
#include <stdio.h>
#include "ANBG_Engine.h"

/**
// @brief Sprite is a single frame with float UV[4] coordinates of a sprite;
*/
typedef struct
{
	float UV[4];
} Sprite;

/**
// @brief Animation is a struct with int AtlasID as an id of an atlas, AnimationFrame* Frames array and int FramesCount as a count of frames;
*/
typedef struct
{
	int AtlasID;
	Sprite* Frames;
	int FramesCount;
} Animation;

/**
// @brief Animation* AnimationConstructor(int atlasID, Sprite* frames, int framesCount, float frameDuration);
*/
ANBG_API Animation* AnimationConstructor(int, Sprite*, int, float);
ANBG_API Sprite** GetFramesFromFile(const char*);

#endif