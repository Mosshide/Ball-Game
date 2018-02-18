#pragma once
#include "UIText.h"

class FPSCounter : public Entity
{
public:
	FPSCounter();
	~FPSCounter();
	void update();
	void draw();
	void realign();

	bool active;
	int frame;
	int time;
	int fps;

private:
	UIText _text;
};

