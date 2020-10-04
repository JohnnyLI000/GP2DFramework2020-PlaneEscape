#pragma once
#ifndef __HUD_H__
#define __HUD_H__

#include "backbuffer.h"
#include <iostream>
#include "entity.h"

class HUD : public Entity {
public:
	HUD();
	~HUD();
	bool initialize(BackBuffer* backbuffer);

	void process(int fuel);
	void draw();
	
	void setUpFuelOdemeter(int fuel, int fuelTank);
private:
	BackBuffer* m_pBackBuffer;
	int m_fuel;
	int m_fuelTank;
};
#endif // !__HUD_H__
