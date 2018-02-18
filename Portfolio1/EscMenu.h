#pragma once
#include "Button.h"
#include "StateEnum.h"

class EscMenu
{
public:
	EscMenu();
	~EscMenu();
	StateEnum update();
	void draw();

	bool active;
	StateEnum state;

private:
	UIRectangle _shade;
	UIText _title;
	Button _mainMenu;
	Button _exitGame;
};

