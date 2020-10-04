#pragma once
#ifndef __ParticleEmitter_H__
#define __ParticleEmitter_H__

#include "Particle.h"
#include <vector>

class ParticleEmitter  {
public:
	ParticleEmitter();
	~ParticleEmitter(); 
	void setSize(int size);
	bool isParticleDead(Particle* particle);
	bool initialize(BackBuffer* backBuffer);
	void respawnParticleHorizontal();
	void process(float deltaTime);
	void draw();
	void generateParticlesHorizontal();
	void setUpRainSprite();
	void generateParticle();
	//void generateParticle();
	//std::vector<Particle*> getParticleList();
private:
	std::vector<Particle*> particleList;
	size_t size;
	BackBuffer* m_pBackBuffer;
	Particle* m_Particle;
};
#endif // !__ParticleEmitter_H__


//TO do : intialize(backbuffer) : pass the backbuffer , so inside particle emitter it can generate the particle itself intialize the sprite
//, does not need to set up in the game class . 
//remove particle and random particle 
//fix the warnings
//fix the includ "" ; <- remove them 
//orginze the header methods 


