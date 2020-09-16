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
	
	m_PlayerPlane = new PlayerPlane();
	pPlayerSprite = new Sprite();

	pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\plane\\default.png");
	m_PlayerPlane->Initialise(pPlayerSprite);
	m_PlayerPlane->SetPositionX(0);
	m_PlayerPlane->SetPositionY(400);

	pBackgroundSprite = new Sprite();
	pBackgroundSprite = m_pBackBuffer->CreateSprite("assets\\Background.png");
	generateBackground();

	// SS04.5: Spawn four rows of 14 alien enemies.
	//generateEnemy();

	pBulletSprite = new Sprite();
	pBulletSprite = m_pBackBuffer->CreateSprite("assets\\playerbullet.png");

	pExplosionSprite = new AnimatedSprite();
	pExplosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\explosion.png");

	m_pBackBuffer->clearSprite();
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


		m_pInputHandler->~InputHandler();
		Draw(*m_pBackBuffer);
	}

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

	// Update the game world simulation:

	// : Process each alien enemy in the container.
	for (Enemy* enemy : enemyList)
	{
		enemy->Process(deltaTime);
	}
	// Process each bullet in the container.
	for (Bullet* bullet : bulletList)
	{
		bullet->Process(deltaTime);
	}

	// SS04.4: Update player...
	m_PlayerPlane->Process(deltaTime);

	
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
				bulletList.erase(std::find(bulletList.begin(), bulletList.end() - 1, bullet));
				enemyList.erase(std::find(enemyList.begin(), enemyList.end() - 1, enemy));
				bullet->~Bullet();
				enemy->~Enemy();
				continue;
			}

		}


		if (bullet->GetPositionY() < 0)
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
		background->Process(deltaTime, m_PlayerPlane);
		if (abs(background->GetPositionX()) >= pBackgroundSprite->GetWidth()) {
			backgroundList.erase(std::find(backgroundList.begin(), backgroundList.end() - 1, background));

		}
		if (backgroundList.size() == 1)
		{
			prepareBackground(backgroundList.at(backgroundList.size() - 1)->GetPositionX()+ pBackgroundSprite->GetWidth());
		}
		score++;

		char buffer[64];
		sprintf(buffer, "background : %d", backgroundList.size());
		LogManager::GetInstance().Log(buffer);
	}

}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();
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
	m_pBackBuffer->DrawText(100, 100, std::to_string((int)score).c_str());

	//m_pBackBuffer->DrawText(100, 100, std::to_string((int)(m_PlayerPlane->GetPositionX())).c_str());
	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void
Game::MoveSpaceShipLeft()
{
	m_PlayerPlane->SetVerticalVelocity(-1);
}
void
Game::MoveSpaceShipRight()
{
	m_PlayerPlane->SetVerticalVelocity(1);
}

void
Game::generateEnemy()
{
	float xb = 40;
	float yb = 30;
	float width = 50;
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 15; c++)
		{
			SpawnEnemy(xb, yb);
			xb += width;
		}
		xb = 40;
		yb += width;
	}
}
//  Spawn a Enemy in game.
void
Game::SpawnEnemy(float x, float y)
{
	pEnemySprite = new Sprite();
	pEnemySprite = m_pBackBuffer->CreateSprite("assets\\alienenemy.png");

	m_Enemy = new Enemy();
	m_Enemy->Initialise(pEnemySprite);
	m_Enemy->SetPositionX(x);
	m_Enemy->SetPositionY(y);
	//  Add the new Enemy to the enemy container.
	enemyList.push_back(m_Enemy);
	//char buffer[64];
	//sprintf(buffer, "%p", m_Enemy);
	//LogManager::GetInstance().Log(buffer);
}
// SS04.6: Space fires a Bullet in game.
void
Game::FireSpaceShipBullet()
{
	// SS04.6: Load the player bullet sprite.   

	// SS04.6: Create a new bullet object.
	m_Bullet = new Bullet();
	m_Bullet->Initialise(pBulletSprite);
	m_Bullet->SetPositionX(this->m_PlayerPlane->GetPositionX());
	m_Bullet->SetPositionY(this->m_PlayerPlane->GetPositionY());

	// SS04.6: Set the bullets vertical velocity.
	m_Bullet->SetVerticalVelocity(400.0f);
	// SS04.6: Add the new bullet to the bullet container.
	bulletList.push_back(m_Bullet);
}
void
Game::generateExplosion(int x, int y) {
	m_Explosion = new Explosion();
	m_Explosion->Initialise(*pExplosionSprite->GetTexture());
	m_Explosion->SetFrameSpeed(0.1f);
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
}void
Game::prepareBackground(float x) {
	m_Background = new Background();
	m_Background->Initialise(pBackgroundSprite);
	m_Background->setStartPosX(x);
	backgroundList.push_back(m_Background);
}

