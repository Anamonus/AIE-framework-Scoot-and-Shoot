#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Car.h"

class Enemy : public Car
{
public:
	Enemy();
	~Enemy();
	void setSpawnTime(float newSpawnTime);
	void enemyCheck(float a_deltaTime, int a_screenHeight);
	float spawnTime;
	bool flip = false;
	bool levelTwo = false;
};


#endif