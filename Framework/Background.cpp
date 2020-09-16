#include <iostream>;
#include "Background.h";
#include "game.h"
#include "logmanager.h"
#include <cassert>

Background::Background()
{

}

Background::~Background()
{

}

void
Background::Process(float deltaTime,PlayerPlane* playerPlane) {
	//this->SetPositionX(startPosX-playerPlane->GetPositionX());
	this->SetPositionX(this->GetPositionX()-std::sin(100 * deltaTime)*2);
	this->SetPositionY(-400);

	//this->SetPositionY(-playerPlane->GetPositionY());
	char buffer[64];
	sprintf(buffer, "background : %f", this->GetPositionX());
	LogManager::GetInstance().Log(buffer);
};

void 
Background::setStartPosX(float x) {
	startPosX = x;
	this->SetPositionX(startPosX);
}





