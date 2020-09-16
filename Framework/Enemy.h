#pragma once
#ifndef __Enemy_H__
#define __Enemy_H__

#include "entity.h"

class Enemy : public Entity {
public:
	Enemy();
	~Enemy();

	void Process(float deltaTime);

};
#endif // !__PLAYER_SHIP_H__
#pragma once
