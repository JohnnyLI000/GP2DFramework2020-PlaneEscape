#pragma once
#ifndef __Explosion_H__
#define __Explosion_H__

#include "Entity.h"
#include "animatedsprite.h"
#include "backbuffer.h"

class Explosion : public Entity {
public:
	Explosion();
	~Explosion();
	void process(float deltaTime);
	bool Initialise(BackBuffer* backBuffer, Entity* plane);
	void setUpExplosionSprite();
	void draw();
	AnimatedSprite* getAnimatedSprite();
private:
	Entity* m_pPlane;
	BackBuffer* m_pBackBuffer;
	AnimatedSprite* pExplosionSprite;
};
#endif