// COMP710 GP 2D Framework 2020
// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <string>

// Static Members:
Game* Game::sm_pInstance = 0;
float Game::width = 800.0f;
float Game::height = 600.0f;
Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, m_PlayerPlane()
	, pPlayerSprite()
	, m_Enemy()
	, pEnemySprite()
	, score(0)
	, isGameOver(true)
{

}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool
Game::Initialise()
{

	m_pBackBuffer = new BackBuffer();

	if (!m_pBackBuffer->Initialise(this->width, this->height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(0xCC, 0xCC, 0xCC);
	
	gravity = 1.4f;
	pPlayerSprite = new Sprite();
	pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\plane\\default.png");
	generatePlayerPlane(gravity);

	pBackgroundSprite = new Sprite();
	pBackgroundSprite = m_pBackBuffer->CreateSprite("assets\\Background.png");
	generateBackground();


	pBulletSprite = new Sprite();
	pBulletSprite = m_pBackBuffer->CreateSprite("assets\\Bullet.png");

	pExplosionSprite = new AnimatedSprite();
	pExplosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\Plane\\death.png");
	pEnemySprite = new Sprite();
	pEnemySprite = m_pBackBuffer->CreateSprite("assets\\enemyPlaneDefault.png");
	
	//generate enemy 
	generateEnemy();

	pGameMenuSprite= new Sprite();
	pGameMenuSprite = m_pBackBuffer->CreateSprite("assets\\game menu\\gameMenu.png");

	pArrowSprite = new Sprite();
	pArrowSprite = m_pBackBuffer->CreateSprite("assets\\game menu\\arrow.png");
	m_pBackBuffer->clearSprite();

	setUpGameMenu();
	return (true);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);

		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}
		Draw(*m_pBackBuffer);

	}
	m_pInputHandler->~InputHandler();

	return (m_looping);
}

void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	m_GameMenu->Process(deltaTime);
	m_Arrow->Process(deltaTime);

	if(!isGameOver)
	{
	// Update player...
	m_PlayerPlane->Process(deltaTime);
	//char buffer[64];
	//sprintf(buffer, "seconds: %f",m_elapsedSeconds);
	//LogManager::GetInstance().Log(buffer);
	for (Enemy* enemy : enemyList)
	{
		enemy->Process(deltaTime);
		if (abs(enemy->GetPositionY() - m_PlayerPlane->GetPositionY())<20)
		{
			if ((int)(m_elapsedSeconds*100)%20== 0)
			{
				FireBullet(true, enemy);
			}
		}
	}
	// Process each bullet in the container.
	for (Bullet* bullet : bulletList)
	{
		bullet->Process(deltaTime);
	}
	
	// Check for bullet vs alien enemy collisions...
	// For each bullet
	// For each alien enemy
	// Check collision between two entities.
	// If collided, destory both and spawn explosion.
	// Remove any dead bullets from the container...
	// Remove any dead enemy aliens from the container...
	for (Bullet* bullet : bulletList)
	{

		bool isCollide = false;
		for (Enemy* enemy : enemyList)
		{
			isCollide = bullet->IsCollidingWith(*enemy);
			if (isCollide) {
				generateExplosion(bullet->GetPositionX(), bullet->GetPositionY());
				if (bulletList.size() != 0)
				{
					bulletList.erase(std::find(bulletList.begin(), bulletList.end() - 1, bullet));
					bullet->~Bullet();

				}
				if (enemyList.size() != 0)
				{
					enemyList.erase(std::find(enemyList.begin(), enemyList.end() - 1, enemy));
					enemy->~Enemy();
				}

				if (enemyList.size() == 0)
				{
					generateEnemy();
				}
				continue;
			}

		}
		isCollide = bullet->IsCollidingWith(*m_PlayerPlane);
		if (isCollide) {
			//system("PAUSE");
			//system("CLS");
			isGameOver = true;
			generateExplosion(bullet->GetPositionX(), bullet->GetPositionY());
			if (bulletList.size() != 0)
			{
				bulletList.erase(std::find(bulletList.begin(), bulletList.end() - 1, bullet));
				bullet->~Bullet();
			}
		}
		if (bullet->GetPositionX() >= width||bullet->GetPositionX()<0)
		{
			bulletList.erase(std::find(bulletList.begin(), bulletList.end() - 1, bullet));
		}
	}

	//Remove any dead explosions from the container...
	for (Explosion* explosion : explosionList)
	{
		explosion->Process(deltaTime);
		if (explosion->IsPaused())
		{
			explosion->~Explosion();
		}
	}
	for (Background* background : backgroundList)
	{
		if(isGameOver)
		{
			background->Process(deltaTime, m_PlayerPlane, true);
		}
		else {
			background->Process(deltaTime, m_PlayerPlane, false);
		}
		if (abs(background->GetPositionX()) >= pBackgroundSprite->GetWidth()) {
			backgroundList.erase(std::find(backgroundList.begin(), backgroundList.end() - 1, background));
		}
		if (backgroundList.size() == 1)
		{
			prepareBackground(backgroundList.at(backgroundList.size() - 1)->GetPositionX()+ pBackgroundSprite->GetWidth());
		}
		if (!isGameOver)
		{
			score++;
		}

	}
	 }
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;
	backBuffer.Clear();
	m_GameMenu->Draw(backBuffer);
	m_Arrow->Draw(backBuffer);

	if (!isGameOver)
	{
		for (Background* background : backgroundList)
		{
			background->Draw(backBuffer);
		}
		// Draw the player ship...
		m_PlayerPlane->Draw(backBuffer);

		//  Draw all enemy aliens in container...
		for (Enemy* enemy : enemyList)
		{
			enemy->Draw(backBuffer);
		}


		//Draw all bullets in container...
		for (Bullet* bullet : bulletList)
		{
			bullet->Draw(backBuffer);
		}



		for (Explosion* explosion : explosionList)
		{
			explosion->Draw(backBuffer);
		}


		m_pBackBuffer->SetTextColour(255, 0, 0);
		m_pBackBuffer->DrawText(100, 100, std::to_string((int)score).c_str());//memory leak from here
	}
	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void
Game::setPlaneGravity()
{
	m_PlayerPlane->SetVerticalVelocity(gravity);
}
void
Game::movePlaneUp()
{
	m_PlayerPlane->SetPositionY(m_PlayerPlane->GetPositionY()-3);
	m_PlayerPlane->SetVerticalVelocity(0);


}

void
Game::generatePlayerPlane(float verticalSpeed) {
	m_PlayerPlane = new PlayerPlane();
	m_PlayerPlane->Initialise(pPlayerSprite);
	m_PlayerPlane->SetVerticalVelocity(verticalSpeed);
}
void
Game::generateEnemy()
{
	srand(rand());
	for (int i = 0; i < 3; i++)
	{
		int randomPosY = rand() % ((int)height-300);
		char buffer[64];
		SpawnEnemy(width - 100, randomPosY);
	}
}
//  Spawn a Enemy in game.
void
Game::SpawnEnemy(float x, float y)
{

	m_Enemy = new Enemy();
	m_Enemy->Initialise(pEnemySprite);
	m_Enemy->setStartPosX(x);
	m_Enemy->SetPositionX(width);
	m_Enemy->SetPositionY(y);
	m_Enemy->SetHorizontalVelocity(100);
	//  Add the new Enemy to the enemy container.
	enemyList.push_back(m_Enemy);

}


void
Game::FireBullet(bool isEnemy,Entity* plane)
{
	m_Bullet = new Bullet();
	m_Bullet->Initialise(pBulletSprite);
	m_Bullet->setIsEnemy(isEnemy);
	if (!isEnemy) {
		m_Bullet->SetPositionX(plane->GetPositionX() + pPlayerSprite->GetWidth() / 2+80);
	}
	else {
		m_Bullet->SetPositionX(plane->GetPositionX() + pPlayerSprite->GetWidth() / 2-80);

	}
	m_Bullet->SetPositionY(plane->GetPositionY()+pPlayerSprite->GetHeight()/2);
	m_Bullet->SetHorizontalVelocity(500.0f);
	bulletList.push_back(m_Bullet);
}
void
Game::generateExplosion(int x, int y) {
	m_Explosion = new Explosion();
	m_Explosion->Initialise(*pExplosionSprite->GetTexture());
	m_Explosion->SetFrameSpeed(0.2f);
	m_Explosion->SetLooping(false);
	m_Explosion->SetX(x);
	m_Explosion->SetY(y);
	explosionList.push_back(m_Explosion);
}
void
Game::generateBackground() {
	m_Background = new Background();
	m_Background->Initialise(pBackgroundSprite);
	m_Background->setStartPosX(0);
	backgroundList.push_back(m_Background);
	m_Background = new Background();
	m_Background->Initialise(pBackgroundSprite);
	m_Background->setStartPosX(pBackgroundSprite->GetWidth());
	backgroundList.push_back(m_Background);
}
void
Game::prepareBackground(float x) {
	m_Background = new Background();
	m_Background->Initialise(pBackgroundSprite);
	m_Background->setStartPosX(x);
	backgroundList.push_back(m_Background);
}

Entity*
Game::getPlayerPlane()
{
	return m_PlayerPlane;
}

void
Game::setUpGameMenu() {
	m_GameMenu = new GameMenu();
	m_GameMenu->SetPositionX(300);
	m_GameMenu->SetPositionY(200);
	m_GameMenu->Initialise(pGameMenuSprite);

	m_Arrow = new Entity();
	m_Arrow->SetPositionX(100);
	m_Arrow->SetPositionY(180);
	m_Arrow->Initialise(pArrowSprite);
} 

void
Game::moveArrowUpInGameMenu() {
	if(m_Arrow->GetPositionY()-80>=180)
	{ 
		m_Arrow->SetPositionY(m_Arrow->GetPositionY() - 80);
	}
}
void
Game::moveArrowDownInGameMenu() {
	if (m_Arrow->GetPositionY()+80 <= 260)
	{
		m_Arrow->SetPositionY(m_Arrow->GetPositionY() +80);
	}
}
void
Game::menuEnter() {
	if (m_Arrow->GetPositionY() - m_GameMenu->GetPositionY() <= 10)
	{
		isGameOver = false;
		restartGame();
	}
	else {
		Quit();
	}
}

bool
Game::getIsGameOver() {
	return isGameOver;
}

void
Game::restartGame() {
	score = 0;
	generatePlayerPlane(gravity);
	enemyList.clear();
	generateEnemy();
	bulletList.clear();
}

