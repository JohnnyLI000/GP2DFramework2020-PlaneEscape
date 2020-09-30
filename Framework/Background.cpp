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
Background::Process(float deltaTime,PlayerPlane* playerPlane,bool isStop) {
	//this->SetPositionX(startPosX-playerPlane->GetPositionX());
	if (!isStop) {
		this->SetPositionX(this->GetPositionX() - std::sin(100 * deltaTime) * 2);
		this->SetPositionY(-400);
	}
};

void 
Background::setStartPosX(float x) {
	startPosX = x;
	this->SetPositionX(startPosX);
}



