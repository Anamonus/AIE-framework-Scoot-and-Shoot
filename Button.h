#ifndef _BUTTON_H_
#define _BUTTON_H_
 
class Button
{
public:
	Button();
	~Button();
	int spriteID, height, width;
	float x, y;
	void setDimensions(int newWidth, int newHeight);
	void setID(int newSpriteID);
	void setPos(float newX, float newY);
	bool isClicked = false;
};


#endif