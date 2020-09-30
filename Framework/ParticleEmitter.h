#pragma once
#ifndef __ParticleEmitter_H__
#define __ParticleEmitter_H__

#include "Particle.h"
#include <vector>

class ParticleEmitter  {
public:
	ParticleEmitter();
	~ParticleEmitter(); 
	void setParticle(Particle* particle);
	void setSize(int size);
	bool isParticleDead(Particle* particle);
	void respawnParticleHorizontal();
	void process(float deltaTime);
	void generateParticlesHorizontal();
	void draw(BackBuffer& backBuffer);
	void generateParticle();
	//std::vector<Particle*> getParticleList();
private:
	std::vector<Particle*> particleList;
	Particle* particle;
	Particle* randomParticle;
	int size;
};
#endif // !__ParticleEmitter_H__
