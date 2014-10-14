#include <iostream>
#include "Bullet.h"
#include "AIE.h"


Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}

void Bullet::fire(float a_DeltaTime)
{
	y += speed * a_DeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Bullet::setDimensions(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
}
void Bullet::setID(int newID)
{
	spriteID = newID;
}
void Bullet::updateFireSpeed(float newFireSpeed)
{
	fireSpeed = newFireSpeed;
}
void Bullet::updateFireCooldown(float a_deltaTime)
{
	fireCooldown += a_deltaTime;
}
void Bullet::setPos(float newX, float newY)
{
	x = newX;
	y = newY;
	MoveSprite(spriteID, x, y);
}
void Bullet::setSpeed(int newSpeed)
{
	speed = newSpeed;
}