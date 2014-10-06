#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "Weapon.h"

class projectile
{

public:

	projectile();
	~projectile();
	
	void setPos(float a_x, float a_y);
	void fire(float a_deltaTime);
	void setID(int newID);
	int speed;

private:
	int width, height, spriteID, x, y;
};

#endif