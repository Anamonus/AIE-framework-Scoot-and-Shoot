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
	void action(float a_fDeltaTime);
	void iDMotion(int newSpriteID);
	void returnID();
	int spriteMotion;
	int spriteBuffer;
private:
	int leftKey;
	int rightKey;
	int leftExtreme;
	int rightExtreme;
};

#endif
