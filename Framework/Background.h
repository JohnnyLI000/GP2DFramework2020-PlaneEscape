#pragma once
#ifndef __Background_H__
#define __Background_H__

#include "entity.h"
#include "PlayerPlane.h"

class Background : public Entity {
public:
	Background();
	~Background();


	void Process(float deltaTime, PlayerPlane* playerPlane);

	void setStartPosX(float x);

	float startPosX;

};
#endif // !__Background_H__
