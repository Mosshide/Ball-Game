#pragma once
#include "Button.h"
#include "GameState.h"
#include "TextureBox.h"
#include "WindowBorder.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();
	StateEnum update();
	void draw();

private:
	Button _startButton;

	WindowBorder _border;
};