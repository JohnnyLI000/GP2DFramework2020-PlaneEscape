#include <iostream>;
#include "PlayerPlane.h";
#include "game.h"
#include <cassert>
#include "logmanager.h"
#include <cmath>
PlayerPlane::PlayerPlane()
{

}

PlayerPlane::~PlayerPlane()
{

}
void
PlayerPlane::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->DrawScale(backBuffer,3.0f);
}
void 
PlayerPlane::Process(float deltaTime) { //pass up or down which is -1 or 1
	// SS04.4: Generic position update, based upon velocity (and time).
	this->SetPositionX(100);
	this->SetPositionY(400);
	//this->SetPositionX(std::sin(100 * deltaTime)*2+ this->GetPositionX());
	//if (deltaTime >= 0.016) //if greater than 0.016 delta time , go up . If I can modify this to press one go up once and always go down by gravity
	//{
	//	this->SetPositionY(std::sin(100 * deltaTime) * 2 + this->GetPositionY());
	//	char buffer[64];
	//	sprintf(buffer, "plane X: %f", deltaTime);
	//	LogManager::GetInstance().Log(buffer);
	//}
	//else {
	//	this->SetPositionY(std::sin(-100 * deltaTime) * 6 + this->GetPositionY());

	//}
}




