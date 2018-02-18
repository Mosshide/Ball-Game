#pragma once
#include "UIRectangle.h"
#include "UserInput.h"

class Bar : public Entity
{
public:
	Bar();
	~Bar();
	void update();
	void draw();
	void realign();
	int collision(lineSeg l, float *wratio = nullptr);

	float vel;

protected:
	UIRectangle _pic;
};