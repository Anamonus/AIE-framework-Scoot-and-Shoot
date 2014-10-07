#include <iostream>
#include "Bullet.h"
#include "AIE.h"


bullet::bullet()
{
}
bullet::~bullet()
{
}

void bullet::fire(float a_DeltaTime)
{
	y += speed * a_DeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
	if (y > screenHeight)
	{

	}
}
void bullet::setDimensions(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
}
void bullet::setID(int newID)
{
	spriteID = newID;
}
void bullet::updateFireSpeed(int newFireSpeed)
{
	fireSpeed = newFireSpeed;
}
void bullet::updateFireCooldown(float a_deltaTime)
{
	fireCooldown += a_deltaTime;
}
void bullet::setPos(float newX, float newY)
{
	x = newX;
	y = newY;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void bullet::setSpeed(int newSpeed)
{
	speed = newSpeed;
}