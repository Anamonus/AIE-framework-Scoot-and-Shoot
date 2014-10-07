#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Car.h"
 
class player : public Car
{
public:
	player();
	~player();
	void setMoveKeys(int a_moveLeft, int a_moveRight);
	void setMoveExtremes(int a_leftExtreme, int a_rightExtreme);
	void setFireKey(int a_fire);
	void action(float a_DeltaTime);
	void iDfire(int newSpriteID);
	void setBuffer();
	int spritefire;
	int spriteBuffer;
	int fireKey;
private:
	int leftKey;
	int rightKey;
	int leftExtreme;
	int rightExtreme;
};

#endif
