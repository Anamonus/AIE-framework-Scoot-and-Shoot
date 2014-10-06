﻿#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Car.h"
#include "Weapon.h"
#include "Player.h"
#include <string>

using namespace std;

int screenWidth = 600;
int screenHeight = 800;
bool playerTurn = false;
double mouseX;
double mouseY;
double angleBuffer;
char angleDisplay[10] = "0";
void mouseConversion();
unsigned int xDif;
unsigned int yDif;
float radToDeg = 57.2957795;
double angleChecker;
int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "Shoot And Scoot");
    SetBackgroundColour(SColour(0, 0, 0, 255));
	player player;
	player.setDimensions(64, 64);
	player.setID(CreateSprite("./images/shootandscoot_player.png", player.width, player.height, true));
	player.iDMotion(CreateSprite("./images/shootandscoot_player_motion.png", player.width, player.height, true));
	player.setMoveKeys('A', 'D');
	player.setSpeed(500);
	player.setMoveExtremes(player.width / 2, screenWidth - (player.width / 2));
	player.setPos(screenWidth /2, screenHeight  / 4);
	Car enemy[10];
	Weapon playerGun;
    do
    {
		float deltaTime = GetDeltaTime();
		GetMouseLocation(mouseX, mouseY);
		mouseConversion();
		DrawSprite(player.spriteID);
		player.action(deltaTime);
        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}

void mouseConversion()
{
	mouseY = (mouseY - screenHeight);
	mouseY = (mouseY * -1);
}
 