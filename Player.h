#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Car.h"
 
class player : public Car
{
public:
	player();
	~player();
	void setMoveKeys(int a_moveLeft, int a_moveRight, int a_moveUp, int a_moveDown);
	void setMoveExtremes(int a_leftExtreme, int a_rightExtreme, int a_upExtreme, int a_downExtreme);
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
	int upKey;
	int upExtreme;
	int downKey;
	int downExtreme;
};

#endif
