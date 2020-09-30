#pragma once
#ifndef __PLAYER_SHIP_H__
#define __PLAYER_SHIP_H__

#include "entity.h"

class PlayerPlane : public Entity {
public:
	PlayerPlane();
	~PlayerPlane();

	void Process(float deltaTime);


};
#endif // !__PLAYER_SHIP_H__
