#pragma once
#include "UIRectangle.h"

class Tile : public Entity
{
public:
	Tile();
	~Tile();
	void update();
	void draw();
	void realign();
	int collision(lineSeg l);

	bool alive;

protected:
	UIRectangle _pic;
};