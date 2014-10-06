#include <iostream>
#include "Player.h"
#include "AIE.h"
#include "Projectile.h"

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
void player::setMoveExtremes(int a_leftExtreme, int a_rightExtreme)
{
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
}
void player::action(float a_fDeltaTime)
{


	if (IsKeyDown(leftKey))
	{
		moveLeft(a_fDeltaTime);
		spriteBuffer = spriteID;
		spriteID = spriteMotion;

	}
	if (IsKeyDown(rightKey))
	{
		moveRight(a_fDeltaTime);
		spriteBuffer = spriteID;
		spriteID = spriteMotion;
	}
}
void player::iDMotion(int newSpriteID)
{
	spriteMotion = newSpriteID;
}
void player::returnID()
{
	spriteID = spriteBuffer;
}