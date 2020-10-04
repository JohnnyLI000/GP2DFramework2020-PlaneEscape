#include "HUD.H"



HUD::HUD():
	m_fuel(0),
	m_fuelTank(0)
{

}
HUD::~HUD() {

}
bool HUD::initialize(BackBuffer* backBuffer)
{
	this->m_pBackBuffer = backBuffer;
	return true;
}
void HUD::process(int fuel)
{
	this->m_fuel = fuel;
}

void HUD::draw() {
	//TO-do : draw outline of a rectangle which is fueltank , and another rectangle
	//inside which is fuel 
	m_pBackBuffer->SetDrawColour(0, 0, 0);
	m_pBackBuffer->DrawRectangle(20, 550, 20 + m_fuelTank, 570);
	m_pBackBuffer->SetDrawColour(255, 0, 0);
	m_pBackBuffer->DrawRectangle(20,550, 20+m_fuel, 570);

}
void HUD::setUpFuelOdemeter(int fuel ,int fuelTank) {
	this->m_fuel = fuel;
	this->m_fuelTank = fuelTank;
}

