// COMP710 GP 2D Framework 2020

// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include "logmanager.h"
#include <cassert>

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
	, m_frames(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	//  : Add the x coordinate to the frame coordinate container.
	m_frameCoordinates.push_back(x);

}

void
AnimatedSprite::Process(float deltaTime)
{
	SetFrameWidth(m_pTexture->GetWidth() / this->m_frames);
	if (m_frameCoordinates.size() <= 0)
	{
		for (int srcNum = 0; srcNum < m_frames; srcNum++)
		{
			int srcPosition = srcNum * (m_frameWidth);
			AddFrame(srcPosition);
		}
	}


	//  : If not paused...
	if (!m_paused)
	{
		// : Count the time elapsed..
		m_timeElapsed += deltaTime;
		// : If the time elapsed is greater than the frame speed.
		// : Move to the next frame.
		// : Reset the time elapsed counter.
		if (m_timeElapsed > m_frameSpeed) {
			m_currentFrame++;
			m_timeElapsed = 0;
		}

		char buffer[64];
		sprintf(buffer, "%d", m_currentFrame);
		LogManager::GetInstance().Log(buffer);
	}			

	// : Stop the animation if it is not looping...
	if (IsLooping() == false) {
		if (m_currentFrame >= m_frameCoordinates.size() ) {
			this->Pause();
			m_currentFrame = 0;
			char buffer[64];
			sprintf(buffer, "Pause: %d", IsPaused());
			LogManager::GetInstance().Log(buffer);
		}
	}

	// : If the current frame is greater than the number 
	//          of frame in this animation...
	// : Reset to the first frame.
	if (m_currentFrame >= m_frameCoordinates.size())
	{
		m_currentFrame = 0;
	}
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// Draw the particular frame into the backbuffer.

	//backbuffer.DrawSprite(*this);
//	backbuffer.DrawAnimatedSprite(*this, 128);
	if (!IsPaused())
	{
		backbuffer.DrawAnimatedSprite(*this, m_frameCoordinates.at(m_currentFrame), m_frames );
	}
	//for (int i = 0; i < m_frameCoordinates.size(); i++)
	//{
	//	backbuffer.DrawAnimatedSprite(*this,m_frameCoordinates.at(i));
	//}

}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}
void
AnimatedSprite::SetFrames(int frames)
{
	m_frames = frames;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}