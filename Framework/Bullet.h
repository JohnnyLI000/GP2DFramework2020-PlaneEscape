#pragma once
#ifndef __Bullet_H__
#define __Bullet_H__

#include "entity.h"

class Bullet : public Entity {
public:
	Bullet();
	~Bullet();

	void Process(float deltaTime);
	void setIsEnemy(bool enmey);
private:
	bool isEnemy;

};
#endif // !__Bullet_H__
