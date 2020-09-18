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
	m_pSprite->Draw(backBuffer);
}
void 
PlayerPlane::Process(float deltaTime) { 
	this->SetPositionX(100);
	this->SetPositionY(this->GetPositionY() +std::sin(100 * deltaTime) * this->m_velocityY );
}




