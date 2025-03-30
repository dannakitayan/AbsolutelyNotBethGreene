#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include <cglm.h>
#include "Enums.h"

typedef struct
{
	bool Weapons[10];
	char AmmoAmount[10];
	bool Keys[3];
}Inventory;

typedef struct
{
	//Stats;
	char Health;
	char Armor;

	//Space;
	vec2 Position;
	Direction DirectionAngle;
}Player;

void InitializeInventory();

void IncreaseHealth(char);
void DecreaseHealth(char);

void IncreaseArmor(char);
void DecreaseArmor(char);

void UnlockWeapon(char);
void AddAmmo(char, char);
void RemoveAmmo(char, char);


void SetPosition(vec2, Direction);
#endif
