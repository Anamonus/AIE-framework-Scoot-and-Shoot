#include <iostream>
#include "Car.h"
#include "AIE.h"
Car::Car()
{

}
Car::~Car()
{

}
void Car::setSpeed(int newSpeed)
{
	speed = newSpeed;
}
void Car::setHealth(int newHealth)
{
	health = newHealth;
}
void Car::setID(int newSpriteID)
{
	spriteID = newSpriteID;
}
void Car::moveRight(float a_fDeltaTime)
{
	x += speed * a_fDeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Car::moveLeft(float a_fDeltaTime)
{
	x -= speed * a_fDeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Car::moveUp(float a_fDeltaTime)
{
	y += speed * a_fDeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Car::moveDown(float a_fDeltaTime)
{
	y -= speed * a_fDeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Car::setDimensions(int a_width, int a_height)
{
	width = a_width;
	height = a_height;
}
void Car::setPos(int newX, int newY)
{
	x = newX;
	y = newY;
	MoveSprite(spriteID, x, y);
}