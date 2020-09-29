#pragma once
#ifndef __GameMenu_H__
#define __GameMenu_H__

#include "entity.h"
#include <vector>

class GameMenu : public Entity {
public:
	GameMenu();
	~GameMenu();
	//void Process(float deltaTime);
//	void setVisibility();
	//void setGameStartSprite(Sprite* gameStartSprite);
	//void setGameQuitSprite(Sprite* gameQuitSprite);
	//void addButton(Entity* button);

private:
	//Entity* gameStartButton;
	//Entity* gameQuitButton;
	//Sprite* gameStartSprite;
	//Sprite* gameQuitSprite;
	//std::vector<Entity*> gameButtonList;

};

#endif // ! __GameMenu_H__

