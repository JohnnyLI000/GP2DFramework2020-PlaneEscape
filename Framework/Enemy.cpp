#include "Enemy.h"
#include "game.h"

Enemy::Enemy():
	startPosX()
	,startPosY()
{

}

Enemy::~Enemy()
{

}

void 
Enemy::Process(float deltaTime) {
	// if(it's greater or eaqual to the start X )from width - horizontal speed *deltaTime
	if (this->GetPositionX()>= startPosX)
	{
		this->SetPositionX(this->GetPositionX()-GetHorizontalVelocity()*deltaTime);
	}
	this->SetPositionY(this->GetPositionY());
};
void
Enemy::setStartPosX(float x) {
	startPosX = x;
}

void
Enemy::setStartPosY(float y) {
	startPosY = y;
}



