#include "AIE.h"
#include "Enemy.h"
#include <iostream>
Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}
void Enemy::setSpawnTime(float newSpawnTime)
{
	spawnTime = newSpawnTime;
}
void Enemy::enemyCheck(float a_deltaTime, int a_screenHeight)
{
	if (alive == true)
	{
		moveDown(a_deltaTime);
		DrawSprite(spriteID);
		if (y < (a_screenHeight / 2))
		{
			if (flip == true)
			{
				RotateSprite(spriteID, -45 * a_deltaTime);
				moveLeft(a_deltaTime);
			}
			if (flip == false)
			{
				RotateSprite(spriteID, 45 * a_deltaTime);
				moveRight(a_deltaTime);
			}
		}
		if (hit == true)
		{
			health -= 5;
			hit = false;
		}
	}
}