#ifndef _WEAPON_H_
#define _WEAPON_H_

class Weapon
{
public:

	Weapon();
	~Weapon();

	float x, y;

	void setSpriteID(int newSpriteID);
	void setDirection();
	void setFireRate(int newRate);
	void setFireKey(int a_fireKey);
	void shoot(float a_DeltaTime);
	//int getDif(double a_mouseY, double a_mouseX, int a_x, int a_y, int a_xDif, int a_yDif);
	//void getAngle(int a_xDif, int a_yDif, float a_radToDeg);
	//void setAngle(int newAngle);
	//int angle;
	
	int damage;
	int fireRate;
	int fireCooldown;
	int bulletNumber;

private:
	int fireKey;
	int width, height, spriteID;

};

#endif