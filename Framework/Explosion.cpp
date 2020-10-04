#include "Explosion.h"
#include <cassert>

Explosion::Explosion()
{

}

Explosion::~Explosion()
{

}
bool
Explosion::Initialise(BackBuffer* backBuffer,Entity* plane)
{
	assert(plane);
	m_pPlane = plane;
	m_pBackBuffer = backBuffer;
	return (true);
}
void
Explosion::setUpExplosionSprite() {
	pExplosionSprite = new AnimatedSprite();
	pExplosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\Plane\\death.png");
	pExplosionSprite->Initialise(*pExplosionSprite->GetTexture());
	pExplosionSprite->SetFrameSpeed(0.2f);
	pExplosionSprite->SetFrames(4);
	this->m_pSprite = pExplosionSprite;
}

AnimatedSprite*
Explosion::getAnimatedSprite() {
	return pExplosionSprite;
}

void
Explosion::draw()
{
	assert(pExplosionSprite);
	pExplosionSprite->SetX(static_cast<float>(m_x));
	pExplosionSprite->SetY(static_cast<float>(m_y));
	pExplosionSprite->Draw(*m_pBackBuffer);
}
void
Explosion::process(float deltaTime)
{
	this->SetPositionX(m_pPlane->GetPositionX());
	this->SetPositionY(m_pPlane->GetPositionY());
	pExplosionSprite->Process(deltaTime);
}