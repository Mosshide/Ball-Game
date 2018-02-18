#pragma once
#include "FPSCounter.h"
#include "Button.h"

class WindowBorder
{
public:
	WindowBorder();
	~WindowBorder();
	void update();
	void draw();

	bool quit;
	fRectangle edge;

private:
	UIRectangle _border[2];
	Button _tab;
	Button _minimize;
	Button _maximize;
	Button _close;
	UIRectangle _bg;

	int localMouse[2];

	FPSCounter _fps;
};

