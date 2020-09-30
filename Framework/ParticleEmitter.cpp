#include <iostream>;
#include "ParticleEmitter.h"
#include "Particle.h"
#include "logmanager.h"
#include <time.h>
ParticleEmitter::ParticleEmitter():
	particle(),
	particleList()
{

}

ParticleEmitter::~ParticleEmitter()
{

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

			particleList.erase(std::find(particleList.begin(), particleList.end() - 1, particle));
			particle->~Particle();
			respawnParticleHorizontal();
		}
	}
}

void ParticleEmitter::draw(BackBuffer& backBuffer)
{	
	int i = 0;
	for (Particle* particle : particleList)
	{
		particle->Draw(backBuffer);
	}
}

void ParticleEmitter::respawnParticleHorizontal() {
	if (particleList.size() <= size)
	{
		generateParticle();
	}
}
void ParticleEmitter::generateParticlesHorizontal() {

	for (int i = 0; i < size; i++)
	{
		srand(rand());

		generateParticle();
	}
}

void ParticleEmitter::generateParticle() {

	randomParticle = new Particle();
	randomParticle = particle;
	srand(rand());
	float randomPosX = rand() % 80000*0.01*2.5;
	randomParticle->SetPositionX(randomPosX);
	randomParticle->SetPositionY(0);
	//char buffer[64];
	//sprintf(buffer, "the position x : %f", randomParticle->GetPositionX());
	//LogManager::GetInstance().Log(buffer);
	srand(rand());
	float horizontalSpeed = rand() % 1000*0.0001;
	randomParticle->SetHorizontalVelocity(horizontalSpeed);
	srand(rand());
	float verticalSpeed = rand() % 1000 * 0.0001;
	randomParticle->SetVerticalVelocity(10);
	particleList.push_back(randomParticle);
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
void ParticleEmitter::setParticle(Particle* particle)
{
	this->particle = particle;
}

