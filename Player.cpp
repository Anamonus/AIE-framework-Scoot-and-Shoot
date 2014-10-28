#include <iostream>
#include "Player.h"
#include "AIE.h"
Player::Player()
{
}
Player::~Player()
{
}
void Player::setMoveKeys(int a_moveLeft, int a_moveRight, int a_moveUp, int a_moveDown)
{
	leftKey = a_moveLeft;
	rightKey = a_moveRight;
	upKey = a_moveUp;
	downKey = a_moveDown;
}
void Player::setFireKey(int a_fire)
{
	fireKey = a_fire;
}
void Player::setMoveExtremes(int a_leftExtreme, int a_rightExtreme, int a_upExtreme, int a_downExtreme)
{
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
	upExtreme = a_upExtreme;
	downExtreme = a_downExtreme;
}
void Player::action(float a_DeltaTime)
{
	if (IsKeyDown(fireKey))
	{
		spriteID = spritefire;
		MoveSprite(spritefire, x, y);
	}
	else
	{
		MoveSprite(spritefire, x, y);
		spriteID = spriteBuffer;
	}
	if (IsKeyDown(leftKey))
	{
		moveLeft(a_DeltaTime);
		if (x < leftExtreme)
		{
			x = leftExtreme;
		}
		MoveSprite(spritefire, x, y);
	}
	if (IsKeyDown(rightKey))
	{
		moveRight(a_DeltaTime);
		if (x > rightExtreme)
		{
			x = rightExtreme;
		}
		MoveSprite(spritefire, x, y);
	}
	if (IsKeyDown(upKey))
	{
		moveUp(a_DeltaTime);
		if (y > upExtreme)
		{
			y = upExtreme;
		}
		MoveSprite(spritefire, x, y);
	}
	if (IsKeyDown(downKey))
	{
		moveDown(a_DeltaTime);
		if (y < downExtreme)
		{
			y = downExtreme;
		}
		MoveSprite(spritefire, x, y);
	}
}
void Player::iDfire(int newSpriteID)
{
	spritefire = newSpriteID;
}
void Player::setBuffer()
{
	spriteBuffer = spriteID;
}
void Player::setLives(int newLives)
{
	lives = newLives;
}
