#include <iostream>
#include "Weapon.h"
#include "AIE.h"
#include "Projectile.h"


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
void Weapon::setFireRate(int newRate)
{
	fireRate = newRate;
}
void Weapon::setFireKey(int a_FireKey)
{
	fireKey = a_FireKey;
}
void Weapon::shoot(float a_deltaTime)
{
	
}
//void Weapon::setAngle(int newAngle)
//{
//	angle = newAngle;
//}
//void Weapon::setDirection()
//{
//	RotateSprite(spriteID, angle);
//}

//int Weapon::getDif(double a_mouseY, double a_mouseX, int a_x, int a_y, int a_xDif, int a_yDif)
//{
//	a_xDif = a_mouseX - a_x;
//	a_yDif = a_mouseY - a_y;
//	return a_xDif, a_yDif;

//}
//void Weapon::getAngle(int a_xDif, int a_yDif, float a_radToDeg)
//{
//	angle = (tan(a_yDif / a_xDif) * a_radToDeg);
//}
