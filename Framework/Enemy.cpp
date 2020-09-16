#include <iostream>;
#include "Enemy.h";
#include "game.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void 
Enemy::Process(float deltaTime) {
	this->SetPositionX(this->GetPositionX());
	this->SetPositionY(this->GetPositionY());
	
};




