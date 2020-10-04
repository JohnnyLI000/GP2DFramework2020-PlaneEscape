#include <iostream>
#include "Particle.h"
#include "game.h"
#include "logmanager.h"

Particle::Particle()
{

}
Particle::~Particle()
{

}
void Particle::initializeSprite(Sprite* sprite)
{
	this->m_pSprite= sprite;
}

void Particle::process(float deltaTime) {
	this->SetPositionX(this->GetPositionX()-this->GetHorizontalVelocity()*deltaTime);
	this->SetPositionY(this->GetPositionY()+this->GetVerticalVelocity()*deltaTime);
}
//void
//Particle::setStartPosX(float x) {
//	startPosX = x;
//}
//
//void
//Particle::setStartPosY(float y) {
//	startPosY = y;
//}