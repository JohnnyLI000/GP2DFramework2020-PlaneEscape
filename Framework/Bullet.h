#pragma once
#ifndef __Bullet_H__
#define __Bullet_H__

#include "entity.h"

class Bullet : public Entity {
public:
	Bullet();
	~Bullet();

	void Process(float deltaTime);


};
#endif // !__Bullet_H__
