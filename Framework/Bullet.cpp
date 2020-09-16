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
	this->SetPositionX(this->GetPositionX());
	this->SetPositionY(this->GetPositionY()-this->m_velocityY * deltaTime);
};





