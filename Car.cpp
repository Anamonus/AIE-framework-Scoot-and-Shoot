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
void Car::moveRight(int a_fDeltaTime)
{
	x += speed * a_fDeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Car::moveLeft(int a_fDeltaTime)
{
	x -= speed * a_fDeltaTime;
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}