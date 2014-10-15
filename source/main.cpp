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
void trackMouse();
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
	int mainMenu = CreateSprite("./images/shootandscoot_title.png", screenWidth, screenHeight, true);
	int startButton = CreateSprite("./images/shootandscoot_startbutton.png", 200, 64, true);
	//Creates all the sprites, limitations, and commands for all entities
	initializing();
	do
	{
		float deltaTime = GetDeltaTime();
		switch (GameStates.currentState)
		{
		case GameStates.MAIN_MENU:
			MoveSprite(mainMenu, screenWidth / 2, screenHeight / 2);
			MoveSprite(startButton, screenWidth / 2, screenHeight * .4);
			DrawSprite(mainMenu);
			DrawSprite(startButton);
			trackMouse();
			pointBoxCollision(mouseX, mouseY, startButton.x, startButton.y, startButton.height, startButton.width);
			break;
		case GameStates.LEVEL_ONE:
			MoveSprite(levelOne, screenWidth / 2, levelProgress);
			levelProgress -= levelSpeed * deltaTime;
			if (levelProgress <= 0)
			{
				levelProgress = screenHeight;
			}
			DrawSprite(levelOne);
			itoa(enemiesSlain, deadEnemies, 10);
			DrawString(deadEnemies, screenWidth * .5, screenHeight * .95);
			DrawSprite(player.spriteID);
			//Player actions
			player.action(deltaTime);
			MoveSprite(player.spriteID, player.x, player.y);
			//Bullet actions
			bulletChecks(deltaTime);
			//Enemy actions
			enemyChecks(deltaTime);
			if (enemiesSlain == 15)
			{
				GameStates.currentState = GameStates.LEVEL_TWO;
			}
			break;
		case GameStates.LEVEL_TWO:
			break;
		case GameStates.LEVEL_THREE:
			break;
		}	
		ClearScreen();
	} while (!FrameworkUpdate());
	Shutdown();
	return 0;
}
void trackMouse()
{
	GetMouseLocation(mouseX, mouseY);
	mouseConversion();
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
		enemy[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemy.png", enemy[enemyBuffer].width, enemy[enemyBuffer].height, true));
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
					RotateSprite(enemy[i].spriteID, -45 * a_deltaTime);
					enemy[i].moveLeft(a_deltaTime);
				}
				else if (enemy[i].flip == false)
				{
					RotateSprite(enemy[i].spriteID, 45 * a_deltaTime);
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
			if (bullet[i].swap == true)
			{
				bullet[i].setPos((player.x - 12), player.y);
				if (i == bulletCap)
				{ 
					bullet[0].swap = false;
				}
				else
				{
					bullet[i + 1].swap = false;
				}
			}
			if (bullet[i].swap == false)
			{
				bullet[i].setPos((player.x + 12), player.y);
				if (i == bulletCap)
				{
					bullet[0].swap = true;
				}
				else
				{
					bullet[i + 1].swap = true;
				}
			}
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
		enemy[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemy.png", enemy[i].width, enemy[i].height, true));
		enemy[i].setSpawnTime(2);
		enemy[i].setSpeed(350);
		enemy[i].setHealth(15);
	}
	for (int i = 0; i < bulletCap; i++)
	{
		bullet[i].setDimensions(9, 16);
		bullet[i].setID(CreateSprite("./images/shootandscoot_bullet.png", bullet[i].width, bullet[i].height, true));
		bullet[i].updateFireSpeed(0.07f);
		bullet[i].setPos(player.x, player.y);
		bullet[i].setSpeed(1000);
	}
}