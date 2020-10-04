#include "ParticleEmitter.h"
#include "Particle.h"
#include "logmanager.h"
#include <time.h>
#include "backbuffer.h"
ParticleEmitter::ParticleEmitter():
	particleList(),
	m_pBackBuffer(0),
	m_Particle(0),
	size(0)
{

}

ParticleEmitter::~ParticleEmitter()
{

}
bool ParticleEmitter::initialize(BackBuffer* backBuffer)
{
	this->m_pBackBuffer = backBuffer;
	return true;
}

void ParticleEmitter::process(float deltaTime) {
	for (Particle* particle : particleList)
	{
		particle->process(deltaTime);

		if (!isParticleDead(particle))
		{
			particle->process(deltaTime);
		}
		else {
			if (particleList.size() != 0)
			{
	//			particleList.erase(std::remove(particleList.begin(), particleList.end(), particle), particleList.end());
				particleList.erase(std::find(particleList.begin(), particleList.end() - 1, particle));
		//		delete particle;
				particle = 0;
		
				respawnParticleHorizontal();
			}
		}
	}
}

void ParticleEmitter::draw()
{	
	for (Particle* particle : particleList)
	{
		particle->Draw(*this->m_pBackBuffer);
	}
}

void ParticleEmitter::respawnParticleHorizontal() {
	if (particleList.size() <= size)
	{
		generateParticle();
	}
}
void ParticleEmitter::generateParticlesHorizontal() {

	for (size_t i = 0; i < size; i++)
	{
		generateParticle();
	}
}

void ParticleEmitter::generateParticle() {
	m_Particle = new Particle();
	m_Particle->initializeSprite(m_pBackBuffer->CreateSprite("assets\\parashute.png"));
	float randomPosX = rand() % 80000*0.01f*2.5f;
	m_Particle->SetPositionX(randomPosX);
	m_Particle->SetPositionY(0);
	float horizontalSpeed = rand() % 1000*0.1f;
	m_Particle->SetHorizontalVelocity(horizontalSpeed);
	float verticalSpeed = rand() % 1000 * 0.1f;
	m_Particle->SetVerticalVelocity(verticalSpeed);
	particleList.push_back(m_Particle);
}

void ParticleEmitter::setSize(int size) {
	this->size = size;
}
bool ParticleEmitter::isParticleDead(Particle* particle) {
	if (particle->GetPositionX() < 0)
	{
		return true;
	}
	if (particle->GetPositionY() >600 )
	{
		return true;			
	}
	else
	{
		return false;
	}
}


