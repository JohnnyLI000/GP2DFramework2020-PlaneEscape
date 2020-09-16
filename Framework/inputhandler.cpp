// COMP710 GP 2D Framework 2020

// This include:
#include "inputhandler.h"
#include <iostream>
// Local includes:
#include "game.h"
#include "logmanager.h"

// Library includes:
#include <cassert>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// SS04.3: Receive Input Events below...

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
	
	 if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.Quit();
			}
		}
		// SS04.6: Tell the game to fire a player bullet...
		else if (event.key.keysym.sym == SDLK_SPACE) //10
		{
			game.FireSpaceShipBullet();
		}

		// SS04.3: Tell the game to move the space ship left...
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			 game.MoveSpaceShipLeft();
			 event.key.keysym.sym = 0;

		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{ 
			 game.MoveSpaceShipRight();
			 event.key.keysym.sym = 0;
		}
		// SS04.3: Tell the game to move the space ship right...
	}
}
