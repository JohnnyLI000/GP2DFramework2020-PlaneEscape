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
	this->SetPositionX(this->GetPositionX()+ this->m_velocityX * deltaTime);
	this->SetPositionY(this->GetPositionY());
};





