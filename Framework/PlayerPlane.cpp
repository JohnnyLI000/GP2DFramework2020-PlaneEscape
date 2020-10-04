#include <iostream>
#include "PlayerPlane.h"
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
PlayerPlane::Process(float deltaTime) { 
	this->SetPositionX(100);
	this->SetPositionY(this->GetPositionY() +std::sin(100 * deltaTime) * this->m_velocityY );
}




