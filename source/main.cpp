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
	player.setID(CreateSprite("./images/shootandscoot_player.png", 64, 64, true);
	player.setMoveKeys('A', 'D');
	player.setMoveExtremes(player.width / 2, screenWidth - (player.width / 2));
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
 