#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "GeneralTypes.h"

typedef struct
{
	//Effects (1 - true, 0 - false);
	char IsRain;
	char IsFog;
	char IsDark;
	//Darkness state;
	char DarknessState; //0 - disable, 1 - middle, 2 - flashlight;
	//Player state;
	float PositionX;
	float PositionY;
	Direction PlayerLookAt;
	char PlayerHealth;
	//What a room is enabled;
	char RoomId;
	//Inventory;
	char Pocket[16];
	//Companion state;
	char IsCompanionActive;
	float CompanionPositionX;
	float CompanionPositionY;
	Direction CompanionLookAt;
}GameFile;

#endif
