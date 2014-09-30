#include <iostream>
#include "Weapon.h"
#include "AIE.h"

Weapon::Weapon()
{

}
Weapon::~Weapon()
{

}

void Weapon::setSpriteID(int newSpriteID)
{
	spriteID = newSpriteID;
}
void Weapon::setAngle(int newAngle)
{
	angle = newAngle;
}
void Weapon::setDirection()
{
	RotateSprite(spriteID, angle);
}
void Weapon::setFireRate(int newRate)
{
	fireRate = newRate;
}
