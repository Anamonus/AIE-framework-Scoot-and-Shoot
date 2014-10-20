#include <iostream>
#include "Button.h"
#include "AIE.h"

Button::Button()
{}
Button::~Button()
{}
void Button::setDimensions(int newWidth, int newHeight)
{
	height = newHeight;
	width = newWidth;
}
void Button::setID(int newSpriteID)
{
	spriteID = newSpriteID;
}
void Button::setPos(float newX, float newY)
{
	x = newX;
	y = newY;
}
