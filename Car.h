#ifndef _CAR_H_
#define _CAR_H_

class Car
{
public:
	
	Car();
	~Car();
	
	float x, y;
	
	void setSpeed(int newSpeed);
	void setHealth(int newHealth);
	void setID(int newSpriteID);
	void moveRight(float a_fDeltaTime);
	void moveLeft(float a_fDeltaTime);
	
private:
	
	int spriteID;
	int health;
	int speed;
	
};

#endif