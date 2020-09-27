#include <iostream>;
#include "Bullet.h";
#include "game.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{

}

void
Bullet::Process(float deltaTime) {
	if (!isEnemy)
	{
		this->SetPositionX(this->GetPositionX() + this->m_velocityX * deltaTime);
	}
	else {
		this->SetPositionX(this->GetPositionX() - this->m_velocityX * deltaTime);
	}
	this->SetPositionY(this->GetPositionY());
};

void
Bullet::setIsEnemy(bool enemy)
{
	this->isEnemy = enemy;
}




