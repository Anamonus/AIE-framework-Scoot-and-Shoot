#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Car.h"

class Enemy : public Car
{
public:
	Enemy();
	~Enemy();
	void setSpawnTime(float newSpawnTime);
	float spawnTime;
	bool flip = false;
};


#endif