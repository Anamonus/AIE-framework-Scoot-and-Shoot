#include <iostream>
#include "Player.h"
#include "AIE.h"

player::player()
{
}
player::~player()
{
}

void player::setMoveKeys(int a_moveLeft, int a_moveRight)
{
	leftKey = a_moveLeft;
	rightKey = a_moveRight;
}
void player::setFireKey(int a_fire)
{
	fireKey = a_fire;
}
void player::setMoveExtremes(int a_leftExtreme, int a_rightExtreme)
{
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
}
void player::action(float a_DeltaTime)
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
		MoveSprite(spritefire, x, y);

	}
	if (IsKeyDown(rightKey))
	{
		moveRight(a_DeltaTime);
		MoveSprite(spritefire, x, y);
	}
}
void player::iDfire(int newSpriteID)
{
	spritefire = newSpriteID;
}
void player::setBuffer()
{
	spriteBuffer = spriteID;
}
