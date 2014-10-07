#include <iostream>
#include "Projectile.h"
#include "AIE.h"

projectile::projectile()
{
}
projectile::~projectile()
{
}
void projectile::setPos(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}
void projectile::setID(int newID)
{
	spriteID = newID;
}
void projectile::fire(float a_deltaTime)
{
	x += speed * a_deltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}