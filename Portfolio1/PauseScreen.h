#pragma once
#include "Button.h"

class PauseScreen
{
public:
	PauseScreen();
	~PauseScreen();
	void update();
	void draw();

	bool quit;

private:
	UIRectangle _bg;
	Button _quitButton;
};

