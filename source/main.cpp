#include "AIE.h"
#include <iostream>
#include <math.h>
#include "Car.h"
#include "Player.h"
#include "Bullet.h"
#include "StateManager.h"
#include "Collision.h"
#include "Enemy.h"
#include "Button.h"
int screenWidth = 600;
int screenHeight = 800;
int enemyXbuffer = screenWidth * .25;
int enemyYbuffer = screenHeight * 1.05;
int enemiesSlain = 0;
int enemyBuffer = 0;
int bulletBuffer = 0;
int bossBulletBuffer = 0;
const int bulletCap = 99;
const int enemyCount = 10;
double mouseX;
double mouseY;
void mouseConversion();
void enemyChecks(float a_deltaTime, int a_screenHeight);
void bulletChecks(float a_deltaTime);
void trackMouse();
void reset();
void initializing();
void playerChecks();
void bossLogic(float a_deltaTime);
void enemySpawns(float a_deltaTime);
float enemySpawnBuffer;
float bossSpawnBuffer;
float levelProgress = screenHeight;
float levelSpeed = 125;
char deadEnemies[6];
bool gameRunning = true;
Enemy enemy[enemyCount];
Enemy enemyTwo[enemyCount];
Bullet bullet[bulletCap];
Player player;
Button startButton;
Enemy boss;
Bullet bossBullet[bulletCap];
StateManager GameStates;
Button instructionsButton;
Button quitButton;
int main(int argc, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Shoot And Scoot");
	SetBackgroundColour(SColour(0, 0, 0, 255));
	GameStates.SetState(GameStates.SPLASH_SCREEN);
	int level = CreateSprite("./images/shootandscoot_level.png", screenWidth, screenHeight * 2, true);
	int mainMenu = CreateSprite("./images/shootandscoot_title.png", screenWidth, screenHeight, true);
	int splashScreen = CreateSprite("./images/shootandscoot_splash.png", screenWidth, screenHeight, true);
	int instructionScreen = CreateSprite("./images/shootandscoot_instructions.png", screenWidth, screenHeight, true);
	int gameOver = CreateSprite("./images/shootandscoot_gameover.png", screenWidth, screenHeight, true);
	//Creates all the sprites, limitations, and commands for all entities
	initializing();
	do
	{
		float deltaTime = GetDeltaTime();
		switch (GameStates.currentState)
		{
		case GameStates.SPLASH_SCREEN:
			MoveSprite(splashScreen, screenWidth / 2, screenHeight / 2);
			DrawSprite(splashScreen);
			if (IsKeyDown(' '))
			{
				GameStates.currentState = GameStates.MAIN_MENU;
			}
			break;
		case GameStates.GAME_OVER:
			MoveSprite(gameOver, screenWidth / 2, screenHeight / 2);
			DrawSprite(gameOver);
			reset();
			if (IsKeyDown(' '))
			{
				GameStates.currentState = GameStates.MAIN_MENU;
			}
			break;
		case GameStates.MAIN_MENU:
			MoveSprite(mainMenu, screenWidth / 2, screenHeight / 2);
			DrawSprite(mainMenu);
			DrawSprite(instructionsButton.spriteID);
			MoveSprite(instructionsButton.spriteID, instructionsButton.x, instructionsButton.y);
			MoveSprite(startButton.spriteID, startButton.x, startButton.y);
			DrawSprite(startButton.spriteID);
			DrawSprite(quitButton.spriteID);
			MoveSprite(quitButton.spriteID, quitButton.x, quitButton.y);
			trackMouse();
			for (int i = 0; i < enemyCount; i++)
			{
				enemy[i].levelTwo = false;
			}
			if (pointBoxCollision(mouseX, mouseY, startButton.x, startButton.y, startButton.height, startButton.width) && GetMouseButtonDown(MOUSE_BUTTON_1))
			{
				GameStates.currentState = GameStates.LEVEL_ONE;
			}
			if (pointBoxCollision(mouseX, mouseY, instructionsButton.x, instructionsButton.y, instructionsButton.height, instructionsButton.width) && GetMouseButtonDown(MOUSE_BUTTON_1))
			{
				GameStates.currentState = GameStates.INSTRUCTIONS;
			}
			if (pointBoxCollision(mouseX, mouseY, quitButton.x, quitButton.y, quitButton.height, quitButton.width) && GetMouseButtonDown(MOUSE_BUTTON_1))
			{
				gameRunning = false;
			}
			ClearScreen();
			break;
		case GameStates.LEVEL_ONE:
			MoveSprite(level, screenWidth / 2, levelProgress);
			levelProgress -= levelSpeed * deltaTime;
			if (levelProgress <= 0)
			{
				levelProgress = screenHeight;
			}
			DrawSprite(level);
			itoa(enemiesSlain, deadEnemies, 10);
			DrawString(deadEnemies, screenWidth * .5, screenHeight * .95);
			DrawSprite(player.spriteID);
			//Player actions
			player.action(deltaTime);
			MoveSprite(player.spriteID, player.x, player.y);
			playerChecks();
			//Bullet actions
			bulletChecks(deltaTime);
			//Enemy actions
			enemySpawns(deltaTime);
			enemyChecks(deltaTime, screenHeight);
			if (enemiesSlain == 15)
			{
				GameStates.currentState = GameStates.LEVEL_TWO;
				enemiesSlain = 0;
				for (int i = 0; i < enemyCount; i++)
				{
					enemy[i].levelTwo = true;
				}
				
			}
			ClearScreen();
			break;
		case GameStates.LEVEL_TWO:
			MoveSprite(level, screenWidth / 2, levelProgress);
			levelProgress -= levelSpeed * deltaTime;
			if (levelProgress <= 0)
			{
				levelProgress = screenHeight;
			}
			DrawSprite(level);
			itoa(enemiesSlain, deadEnemies, 10);
			DrawString(deadEnemies, screenWidth * .5, screenHeight * .95);
			DrawSprite(player.spriteID);
			//Player actions
			player.action(deltaTime);
			MoveSprite(player.spriteID, player.x, player.y);
			playerChecks();
			//Bullet actions
			bulletChecks(deltaTime);
			//Enemy actions
			enemySpawns(deltaTime);
			enemyChecks(deltaTime, screenHeight);
			if (enemiesSlain == 25)
			{
				GameStates.currentState = GameStates.LEVEL_THREE;
				enemiesSlain = 0;
			}
			ClearScreen();
			break;
		case GameStates.LEVEL_THREE:
			MoveSprite(level, screenWidth / 2, levelProgress);
			levelProgress -= levelSpeed * deltaTime;
			if (levelProgress <= 0)
			{
				levelProgress = screenHeight;
			}
			DrawSprite(level);
			itoa(enemiesSlain, deadEnemies, 10);
			DrawString(deadEnemies, screenWidth * .5, screenHeight * .95);
			DrawSprite(player.spriteID);
			//Player actions
			player.action(deltaTime);
			MoveSprite(player.spriteID, player.x, player.y);
			playerChecks();
			//Bullet actions
			bulletChecks(deltaTime);
			//Boss actions
			bossLogic(deltaTime);
			ClearScreen();
			break;
		}	
		ClearScreen();
	} while (!FrameworkUpdate() && gameRunning == true);
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
void enemyChecks(float a_deltaTime, int a_screenHeight)
{
	for (int i = 0; i < enemyCount; i++)
	{
		enemy[i].enemyCheck(a_deltaTime, a_screenHeight);
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
			if ((enemy[i].health <= 0) && (enemy[i].alive == true))
			{
				enemy[i].alive = false;
				enemiesSlain++;
			}
		}
	}
	for (int i = 0; i < enemyCount; i++)
	{
		enemyTwo[i].enemyCheck(a_deltaTime, a_screenHeight);
		if (enemyTwo[i].alive == true)
		{
			if (enemyXbuffer < 0)
			{
				enemyTwo[enemyBuffer].flip = true;
			}
			else if (enemyXbuffer > 0)
			{
				enemyTwo[enemyBuffer].flip = false;
			}
			if ((enemyTwo[i].health <= 0) && (enemyTwo[i].alive == true))
			{
				enemyTwo[i].alive = false;
				enemiesSlain++;
			}
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
		if (collision(bullet[i].x, bullet[i].y, boss.x, boss.y, bullet[i].width, boss.height) && (bullet[i].firing == true))
		{
 			boss.hit = true;
			bullet[i].setPos(screenWidth + bullet[i].width, screenHeight + bullet[i].height);
		}
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
			if (collision(bullet[i].x, bullet[i].y, enemyTwo[ii].x, enemyTwo[ii].y, bullet[i].width, enemyTwo[ii].width) && (bullet[i].firing == true))
			{
				if (enemyTwo[ii].alive == true)
				{
					bullet[i].setPos(screenWidth + bullet[i].width, screenHeight + bullet[i].height);
					enemyTwo[ii].hit = true;
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
	player.setSpeed(350);
	player.setLives(3);
	player.setMoveExtremes(player.width / 2, screenWidth - (player.width / 2), screenHeight - (player.height / 2), player.height / 2);
	player.setPos(screenWidth / 2, screenHeight / 4);
	player.setBuffer();

	startButton.setDimensions(200, 64);
	startButton.setPos(screenWidth / 2, screenHeight * .4);
	startButton.setID(CreateSprite("./images/shootandscoot_startbutton.png", startButton.width, startButton.height, true));

	instructionsButton.setDimensions(600, 64);
	instructionsButton.setPos(screenWidth / 2, screenHeight * .3);
	instructionsButton.setID(CreateSprite("./images/shootandscoot_instructionsbutton.png", instructionsButton.width, instructionsButton.height, true));

	quitButton.setDimensions(200, 64);
	quitButton.setPos(screenWidth / 2, screenHeight * .2);
	quitButton.setID(CreateSprite("./images/shootandscoot_quitbutton.png", quitButton.width, quitButton.height, true));

	boss.setDimensions(128, 96);
	boss.setSpeed(250);
	boss.setHealth(450);
	boss.setPos(screenWidth / 2, screenHeight + boss.width);
	boss.setID(CreateSprite("./images/shootandscoot_boss.png", boss.width, boss.height, true));

	for (int i = 0; i < enemyCount; i++)
	{
		enemy[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemy.png", enemy[i].width, enemy[i].height, true));
		enemy[i].setSpawnTime(1.2f);
		enemy[i].setSpeed(350);
		enemy[i].setHealth(15);
		enemyTwo[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemy.png", enemyTwo[i].width, enemyTwo[i].height, true));
		enemyTwo[i].setSpawnTime(1.2f);
		enemyTwo[i].setSpeed(350);
		enemyTwo[i].setHealth(15);
	}
	for (int i = 0; i < bulletCap; i++)
	{
		bullet[i].setDimensions(9, 16);
		bullet[i].setID(CreateSprite("./images/shootandscoot_bullet.png", bullet[i].width, bullet[i].height, true));
		bullet[i].updateFireSpeed(0.1f);
		bullet[i].setPos(player.x, player.y);
		bullet[i].setSpeed(1000);
	}
	for (int i = 0; i < bulletCap; i++)
	{
		bossBullet[i].setDimensions(16, 28);
		bossBullet[i].setID(CreateSprite("./images/shootandscoot_missle.png", bossBullet[i].width, bossBullet[i].height, true));
		bossBullet[i].updateFireSpeed(0.5f);
		bossBullet[i].setPos(boss.x,boss.y);
		bossBullet[i].setSpeed(-700);
	}
}
void enemySpawns(float a_deltaTime)
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
		if (enemy[enemyBuffer].levelTwo == true)
		{
			enemyTwo[enemyBuffer].setDimensions(64, 64);
			enemyTwo[enemyBuffer].setHealth(15);
			enemyTwo[enemyBuffer].setID(CreateSprite("./images/shootandscoot_enemy.png", enemyTwo[enemyBuffer].width, enemyTwo[enemyBuffer].height, true));
			enemyTwo[enemyBuffer].setPos((screenWidth / 2) + (enemyXbuffer * .33), enemyYbuffer);
			enemyTwo[enemyBuffer].alive = true;
		}
		enemyBuffer += 1;
		enemyXbuffer = -(enemyXbuffer);
		enemySpawnBuffer = 0;
	}
}
void bossLogic(float a_deltaTime)
{
	DrawSprite(boss.spriteID);
	if (boss.y > screenHeight * .8)
	{
		boss.moveDown(a_deltaTime);
	}
	else
	{
		if (boss.flip == true)
		{
			boss.moveLeft(a_deltaTime);
			if (boss.x < (boss.width / 2))
			{
				boss.flip = false;
			}
		}
		if (boss.flip == false)
		{
			boss.moveRight(a_deltaTime);
			if (boss.x > screenWidth - (boss.width / 2))
			{
				boss.flip = true;
			}
		}
	}
	if (boss.hit == true)
	{
		boss.health -= 5;
		boss.hit = false;
	}
	if (boss.health <= 0)
	{
		DestroySprite(boss.spriteID);
		boss.setPos(screenWidth * 2, screenHeight * 2);
	}
	bossBullet[bossBulletBuffer].updateFireCooldown(a_deltaTime);
	if (bossBulletBuffer >= bulletCap - 1)
	{
		bossBulletBuffer = 0;
	}
	if ((bossBullet[bossBulletBuffer].fireCooldown > bossBullet[bossBulletBuffer].fireSpeed) && (boss.x > (player.x - 30)) && (boss.x < player.x + 30))
	{
		bossBullet[bossBulletBuffer].firing = true;
		bossBulletBuffer++;
	}
	for (int i = 0; i < bulletCap; i++)
	{
		if (bossBullet[i].firing == true)
		{
			bossBullet[i].fire(a_deltaTime);
			if (bossBullet[i].y < 0)
			{
				bossBullet[i].firing = false;
				bossBullet[i].fireCooldown = 0;
				bossBullet[i].collided = false;
			}
		}
		else
		{
			bossBullet[i].setPos(boss.x, boss.y);
		}
	}
}
void playerChecks()
{
	for (int i = 0; i < bulletCap; i++)
	{
		if (collision(player.x, player.y, bossBullet[i].x, bossBullet[i].y, player.width, bossBullet[i].width) && bossBullet[i].collided == false)
		{
			player.hit = true;
			bossBullet[i].collided = true;
			DestroySprite(bossBullet[i].spriteID);
		}
	}
	for (int i = 0; i < enemyCount; i++)
	{
		if (collision(player.x, player.y, enemy[i].x, enemy[i].y, player.width, enemy[i].width) && enemy[i].collided == false)
		{
			player.hit = true;
			enemy[i].collided = true;
			DestroySprite(enemy[i].spriteID);
		}
	}
	for (int i = 0; i < enemyCount; i++)
	{
		if (collision(player.x, player.y, enemyTwo[i].x, enemyTwo[i].y, player.width, enemyTwo[i].width && enemyTwo[i].collided == false))
		{
			player.hit = true;
			enemyTwo[i].collided  = true;
			DestroySprite(enemyTwo[i].spriteID);
		}
	}
	if (player.hit == true)
	{
		player.lives--;
		player.hit = false;
	}
	if (player.lives == 0)
	{
		GameStates.currentState = GameStates.GAME_OVER;
		player.setLives(3);
	}
}
void reset()
{
	enemyXbuffer = screenWidth * .25;
	enemyYbuffer = screenHeight * 1.05;
	enemiesSlain = 0;
	enemyBuffer = 0;
	bulletBuffer = 0;
	bossBulletBuffer = 0;
}