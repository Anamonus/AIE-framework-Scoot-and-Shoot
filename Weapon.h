#ifndef _WEAPON_H_
#define _WEAPON_H_

class Weapon
{
public:

	Weapon();
	~Weapon();

	float x, y;

	void setSpriteID(int newSpriteID);
	void setAngle(int newAngle);
	void setDirection();
	void setFireRate(int newRate);

private:

	int angle;
	int spriteID;
	int damage;
	int fireRate;

};

#endif