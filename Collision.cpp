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