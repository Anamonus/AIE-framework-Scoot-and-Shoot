#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Car.h"
#include "Weapon.h"
#include "Player.h"

int screenWidth = 600;
int screenHeight = 800;

int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "Shoot And Scoot");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));
	player player;
	Car enemy[10];
	Weapon playerGun;
    do
    {
		float deltaTime = GetDeltaTime();
        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
