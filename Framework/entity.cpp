// COMP710 GP 2D Framework 2020

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "game.h"

// Library includes:
#include <cassert>
#include <iostream>
#include <SDL_stdinc.h>


Entity::Entity()
	: m_pSprite(0)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_velocityX(0.0f)
	, m_velocityY(0.0f)
	, m_dead(false)
{

}

Entity::~Entity()
{

}

void Entity::clearSprite() {
	delete this->m_pSprite;
	this->m_pSprite = nullptr;
}
bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}


void
Entity::Process(float deltaTime)
{
	this->SetPositionX(this->GetPositionX());
	this->SetPositionY(this->GetPositionY());
}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<float>(m_x));
	m_pSprite->SetY(static_cast<float>(m_y));
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// SS04.6: Generic Entity Collision routine.
	bool isCollide = false;
	// SS04.6: Does this object collide with the e object?
	// SS04.6: Create a circle for each entity (this and e).

	float circle = 3.0f * 3.0f * (float)M_PI;//area of the circle 

	// SS04.6: Check for intersection.

	if (std::abs((this->GetPositionX() - e.GetPositionX())) < circle) {
		if (std::abs((this->GetPositionY() - e.GetPositionY()-e.m_pSprite->GetHeight()/2)) < circle)
		{
			isCollide = true;
		}
	}
	// SS04.6: Using circle-vs-circle collision detection.

	// SS04.6: Return result of collision.
	return isCollide; // SS04.6 Change return value!
}

void
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool
Entity::IsDead()
{
	return m_dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float
Entity::GetPositionX() const
{
	return (m_x);
}

float
Entity::GetPositionY() const
{
	return (m_y);
}

float
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}
