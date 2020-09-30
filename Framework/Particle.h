#pragma once
#ifndef __Particle_H__
#define __Particle_H__

#include "entity.h"

class Particle : public Entity {
public:
	Particle();
	~Particle();
	void process(float deltaTime);
//	void setStartPosX(float x);
//	void setStartPosY(float y);
//private: 
//	float startPosX;
//	float startPosY;
};
#endif // ! __RainParticle_H__
