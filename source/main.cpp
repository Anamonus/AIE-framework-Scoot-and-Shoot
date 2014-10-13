#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Car.h"
#include "Player.h"
#include "Bullet.h"
#include "StateManager.h"
#include "Collision.h"

using namespace std;

int screenWidth = 600;
int screenHeight = 800;
bool playerTurn = false;
double mouseX;
double mouseY;
int bulletBuffer = 0;
void mouseConversion();
const int bulletCap = 99;
int enemyXbuffer = screenWidth * .12;
int enemyYbuffer = screenHeight * .95;
const int enemyCount = 10;
float levelProgress = screenHeight;
float levelSpeed = 0.5;

int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "Shoot And Scoot");
    SetBackgroundColour(SColour(0, 0, 0, 255));
	int levelOne = CreateSprite("./images/shootandscoot_level.png", screenWidth, screenHeight * 2, true);
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
	Car enemy[enemyCount];
	for (int i = 0; i < enemyCount; i++)
	{
		enemy[i].setDimensions(64, 64);
		enemy[i].setHealth(15);
		enemy[i].setID(CreateSprite("./images/shootandscoot_enemyplaceholder.png", enemy[i].width, enemy[i].height, true));
		enemy[i].setPos(enemyXbuffer, enemyYbuffer);
		enemyXbuffer += enemy[i].width + 5;
		if (enemyXbuffer >= screenWidth - enemy[i].width)
		{
			enemyXbuffer = screenWidth * .12;
			enemyYbuffer -= enemy[i].height;
		}
	}

	bullet bullet[bulletCap];

	for (int i = 0; i < bulletCap; i++)
	{
		bullet[i].setDimensions(40, 16);
		bullet[i].setID(CreateSprite("./images/shootandscoot_bullet.png", bullet[i].width, bullet[i].height, true));
		bullet[i].updateFireSpeed(0.05f);
		bullet[i].setPos(player.x, player.y);
		bullet[i].setSpeed(1000);
	}
    do
    {
		MoveSprite(levelOne, screenWidth / 2, levelProgress);
		levelProgress -= levelSpeed;
		if (levelProgress == 0)
		{
			levelProgress = screenHeight;
		}
		DrawSprite(levelOne);
		for (int i = 0; i < enemyCount; i++)
		{
			DrawSprite(enemy[i].spriteID);
		}
		float deltaTime = GetDeltaTime();
		bullet[bulletBuffer].updateFireCooldown(deltaTime);
		GetMouseLocation(mouseX, mouseY);
		mouseConversion();
		if (IsKeyDown(player.fireKey) && bullet[bulletBuffer].fireCooldown > bullet[bulletBuffer].fireSpeed)
		{
			bulletBuffer++;
			bullet[bulletBuffer].firing = true;
		}
		if (bulletBuffer > 98)
		{
			bulletBuffer = 0;
		}
		DrawSprite(player.spriteID);
		player.action(deltaTime);
		MoveSprite(player.spriteID, player.x, player.y);
		for (int i = 0; i < bulletCap; i++)
		{
			if (bullet[i].firing == true)
			{
				bullet[i].fire(deltaTime);
				if (bullet[i].y > screenHeight)
				{
					bullet[i].firing = false;
					bullet[i].fireCooldown = 0;
					bullet[i].collided = false;
				}
			}
			else
			{
				bullet[i].setPos(player.x, player.y);
			}
			
		}
		for (int i = 0; i < bulletCap; i++)
		{
			for (int ii = 0; ii < enemyCount; ii++)
			{
				if (collision(bullet[i].x, bullet[i].y, enemy[ii].x, enemy[ii].y, bullet[bulletBuffer].width, enemy[ii].width))
				{
					if (enemy[ii].alive == true)
					{
						bullet[i].setPos(screenWidth + bullet[i].width, screenHeight + bullet[i].height);
						enemy[ii].hit = true;
					}
				}
			}
		}
		for (int i = 0; i < enemyCount; i++)
		{
			if (enemy[i].hit == true)
			{
				enemy[i].health -= 5;
				enemy[i].hit = false;
			}

			if (enemy[i].health <= 0)
			{
				enemy[i].alive = false;
			}
			if (enemy[i].alive == false)
			{
				DestroySprite(enemy[i].spriteID);
			}
		}
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
 