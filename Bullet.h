#ifndef _BULLET_H_
#define _BULLET_H_

class Bullet
{
public:
	Bullet();
	~Bullet();
	void fire(float a_deltaTime);
	void setID(int newID);
	void setPos(float newX, float newY);
	void setDimensions(int newWidth, int newHeight);
	void updateFireSpeed(float newFireSpeed);
	void updateFireCooldown(float a_deltaTime);
	void setSpeed(int newSpeed);
	float fireSpeed;
	float fireCooldown = 0;
	int spriteID;
	int speed;
	int width;
	int height;
	float x, y;
	bool firing = false;
	bool collided = false;
private:


};
#endif