#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Car.h"
#include "Player.h"
#include "Bullet.h"
#include "StateManager.h"
#include "Collision.h"
#include "Enemy.h"
int screenWidth = 600;
int screenHeight = 800;
int enemyXbuffer = screenWidth * .25;
int enemyYbuffer = screenHeight * 1.05;
int enemiesSlain = 0;
int enemyBuffer = 0;
int bulletBuffer = 0;
const int bulletCap = 99;
const int enemyCount = 10;
double mouseX;
double mouseY;
void mouseConversion();
void enemyChecks(float a_deltaTime);
void bulletChecks(float a_deltaTime);
void initializing();
float enemySpawnBuffer;
float levelProgress = screenHeight;
float levelSpeed = 125;
char deadEnemies[6];
Enemy enemy[enemyCount];
Bullet bullet[bulletCap];
Player player;
int main(int argc, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Shoot And Scoot");
	SetBackgroundColour(SColour(0, 0, 0, 255));
	StateManager GameStates;
	GameStates.SetState(GameStates.MAIN_MENU);
	int levelOne = CreateSprite("./images/shootandscoot_level.png", screenWidth, screenHeight * 2, true);
	//Creates all the sprites, limitations, and commands for all entities
	initializing();
	do
	{
		float deltaTime = GetDeltaTime();
		MoveSprite(levelOne, screenWidth / 2, levelProgress);
		levelProgress -= levelSpeed * deltaTime;
		if (levelProgress <= 0)
		{
			levelProgress = screenHeight;
		}
		DrawSprite(levelOne);
		itoa(enemiesSlain, deadEnemies, 10);
		DrawString(deadEnemies, screenWidth * .5, screenHeight * .95);
		GetMouseLocation(mouseX, mouseY);
		//Coverting the mouse inputs so that it matches the way the AIE Framwork draws a window
		mouseConversion();
		DrawSprite(player.spriteID);
		//Player actions
		player.action(deltaTime);
		MoveSprite(player.spriteID, player.x, player.y);
		//Bullet actions
		bulletChecks(deltaTime);
		//Enemy actions
		enemyChecks(deltaTime);
		ClearScreen();
	} while (!FrameworkUpdate());
	Shutdown();
	return 0;
}
void mouseConversion()
{
	mouseY = (mouseY - screenHeight);
	mouseY = (mouseY * -1);
}
void enemyChecks(float a_deltaTime)
{
	enemySpawnBuffer += a_deltaTime;
	if (enemyBuffer >= enemyCount - 1)
	{
		enemyBuffer = 0;
	}
	if (enemySpawnBuffer >= enemy[enemyBuffer].spawnTime)
	{
		enemy[enemyBuffer].setDimensions(64, 64);
		enemy[enemyBuffer].setHealth(15);
		enemy[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemyplaceholder.png", enemy[enemyBuffer].width, enemy[enemyBuffer].height, true));
		enemy[enemyBuffer].setPos((screenWidth / 2) - enemyXbuffer, enemyYbuffer);
		enemy[enemyBuffer].alive = true;
		enemyBuffer += 1;
		enemyXbuffer = -(enemyXbuffer);
		enemySpawnBuffer = 0;
	}
	
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i].alive == true)
		{
			if (enemyXbuffer < 0)
			{
				enemy[enemyBuffer].flip = true;
			}
			else if (enemyXbuffer > 0)
			{
				enemy[enemyBuffer].flip = false;
			}
			enemy[i].moveDown(a_deltaTime);
			DrawSprite(enemy[i].spriteID);
			if (enemy[i].y < screenHeight / 2)
			{
				if (enemy[i].flip == true)
				{
					enemy[i].moveLeft(a_deltaTime);
				}
				else if (enemy[i].flip == false)
				{
					enemy[i].moveRight(a_deltaTime);
				}
			}
		}
		if (enemy[i].hit == true)
		{
			enemy[i].health -= 5;
			enemy[i].hit = false;
		}
		if ((enemy[i].health <= 0) && (enemy[i].alive == true))
		{
			enemy[i].alive = false;
			enemiesSlain++;
		}
	}
}
void bulletChecks(float a_deltaTime)
{
	bullet[bulletBuffer].updateFireCooldown(a_deltaTime);
	if (IsKeyDown(player.fireKey) && bullet[bulletBuffer].fireCooldown > bullet[bulletBuffer].fireSpeed)
	{
		bulletBuffer++;
		bullet[bulletBuffer].firing = true;
	}
	if (bulletBuffer == bulletCap - 1)
	{
		bulletBuffer = 0;
	}
	for (int i = 0; i < bulletCap; i++)
	{
		if (bullet[i].firing == true)
		{
			bullet[i].fire(a_deltaTime);
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
			if (collision(bullet[i].x, bullet[i].y, enemy[ii].x, enemy[ii].y, bullet[i].width, enemy[ii].width) && (bullet[i].firing == true))
			{
				if (enemy[ii].alive == true)
				{
					bullet[i].setPos(screenWidth + bullet[i].width, screenHeight + bullet[i].height);
					enemy[ii].hit = true;
				}
			}
		}
	}
}
void initializing()
{
	player.setDimensions(64, 64);
	player.setID(CreateSprite("./images/shootandscoot_player.png", player.width, player.height, true));
	player.iDfire(CreateSprite("./images/shootandscoot_player_fire.png", player.width, player.height, true));
	player.setMoveKeys('A', 'D', 'W', 'S');
	player.setFireKey(' ');
	player.setSpeed(250);
	player.setMoveExtremes(player.width / 2, screenWidth - (player.width / 2), screenHeight - (player.height / 2), player.height / 2);
	player.setPos(screenWidth / 2, screenHeight / 4);
	player.setBuffer();
	for (int i = 0; i < enemyCount; i++)
	{
		enemy[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemyplaceholder.png", enemy[i].width, enemy[i].height, true));
		enemy[i].setSpawnTime(2);
		enemy[i].setSpeed(350);
		enemy[i].setHealth(15);
	}
	for (int i = 0; i < bulletCap; i++)
	{
		bullet[i].setDimensions(40, 16);
		bullet[i].setID(CreateSprite("./images/shootandscoot_bullet.png", bullet[i].width, bullet[i].height, true));
		bullet[i].updateFireSpeed(0.15f);
		bullet[i].setPos(player.x, player.y);
		bullet[i].setSpeed(1000);
	}
}