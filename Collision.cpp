#include <iostream>
#include "Collision.h"
#include "AIE.h"
bool collision(int a_firstX, int a_firstY, int a_secondX, int a_secondY, int a_firstRadius, int a_secondRadius)
{
	int dX = a_firstX - a_secondX;
	int dY = a_firstY - a_secondY;
	int radii = (a_firstRadius / 2 ) + (a_secondRadius / 2 );
	if ((dX * dX) + (dY * dY) < (radii * radii))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool pointBoxCollision(int a_checkX, int a_checkY, int a_x, int a_y ,int a_height, int a_width)
{
	int upExtreme = a_y + (a_height / 2);
	int downExtreme = a_y - (a_height / 2);
	int leftExtreme = a_x - (a_width / 2);
	int rightExtreme = a_x + (a_width / 2);
	if (a_checkY > downExtreme && a_checkY < upExtreme && a_checkX > leftExtreme && a_checkX < rightExtreme)
	{
		return true;
	}
	else
	{
		return false;
	}
}