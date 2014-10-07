#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Car.h"
#include "Player.h"
#include "Bullet.h"

using namespace std;

int screenWidth = 600;
int screenHeight = 800;
bool playerTurn = false;
double mouseX;
double mouseY;
int bulletBuffer = 0;
void mouseConversion();

int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "Shoot And Scoot");
    SetBackgroundColour(SColour(0, 0, 0, 255));
	player player;
	player.setDimensions(64, 64);
	player.setID(CreateSprite("./images/shootandscoot_player.png", player.width, player.height, true));
	player.iDfire(CreateSprite("./images/shootandscoot_player_fire.png", player.width, player.height, true));
	player.setMoveKeys('A', 'D');
	player.setFireKey(' ');
	player.setSpeed(500);
	player.setMoveExtremes(player.width / 2, screenWidth - (player.width / 2));
	player.setPos(screenWidth /2, screenHeight  / 4);
	player.setBuffer();
	Car enemy[10];
	bullet bullet[50];
	for (int i = 0; i < 50; i++)
	{
		bullet[i].setDimensions(40, 16);
		bullet[i].setID(CreateSprite("./images/shootandscoot_bullet.png", bullet[i].width, bullet[i].height, true));
		bullet[i].updateFireSpeed(0.5f);
		bullet[i].setPos(player.x, player.y);
		bullet[i].setSpeed(1000);
	}
    do
    {
		float deltaTime = GetDeltaTime();
		bullet[bulletBuffer].updateFireCooldown(deltaTime);
		GetMouseLocation(mouseX, mouseY);
		mouseConversion();
		if (IsKeyDown(player.fireKey) && bullet[bulletBuffer].fireCooldown > bullet[bulletBuffer].fireSpeed)
		{
			bullet[bulletBuffer].fire(deltaTime);
			bulletBuffer = (bulletBuffer + 1);
		}
		DrawSprite(player.spriteID);
		player.action(deltaTime);
		MoveSprite(player.spriteID, player.x, player.y);
        ClearScreen();
		if (bulletBuffer > 49)
		{
			bulletBuffer = 0;
		}
    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}

void mouseConversion()
{
	mouseY = (mouseY - screenHeight);
	mouseY = (mouseY * -1);
}
 