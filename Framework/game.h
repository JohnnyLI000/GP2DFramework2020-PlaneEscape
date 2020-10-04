// COMP710 GP 2D Framework 2020
#include "PlayerPlane.h"
#include "Enemy.h"
#include <list>
#include "Bullet.h"
#include <vector>
#include "Explosion.h"
#include "Background.h"
#include "GameMenu.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "HUD.h"
#ifndef __GAME_H__
#define __GAME_H__

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();
	static float width;
	static float height;

	void setPlaneGravity();
	void movePlaneUp();

	void FireBullet(bool isEnemy, Entity* plane);
	void generateExplosion(Entity* plane, bool isLooping);
	void SpawnEnemy(float x, float y);
	Entity* getPlayerPlane();
	void setUpGameMenu();
	void moveArrowUpInGameMenu();
	void moveArrowDownInGameMenu();
	void menuEnter();
	void restartGame();

	bool getIsGameOver();

	void generateRainParticle();
	void generatePlayerPlane(float verticalSpeed);
	void generateEnemy();
	void generateBackground();

	void prepareBackground(int x);
	bool isGameOver;
	void setUpGame();
	void processGame(float deltaTime);
	void drawGame(BackBuffer& backBuffer);
	void setUpHUD();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;
	float score;
	float gravity;
	PlayerPlane* m_PlayerPlane;
	Sprite* pPlayerSprite;

	Sprite* pEnemySprite;
	Enemy* m_Enemy;

	Sprite* pBulletSprite;
	Bullet* m_Bullet;

	Sprite* pBackgroundSprite;
	Background* m_Background;


	Explosion* m_Explosion;

	Sprite* pGameMenuSprite;
	GameMenu* m_GameMenu;
	Sprite* pArrowSprite;
	Entity* m_Arrow;

	Sprite* pRainParticleSprite;
	Particle* m_RainParticle;
	ParticleEmitter* m_RainParticleEmitter;

	HUD* m_HUD;
	int m_fuel;
	int m_fuelTank; 
	std::vector<Enemy*> enemyList;
	std::vector<Bullet*> bulletList;
	std::vector<Explosion*> explosionList;
	std::vector<Background*> backgroundList;

private:




};

#endif // __GAME_H__
