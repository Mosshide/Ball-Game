#pragma once
#include "UIRectangle.h"
#include "Navigator.h"

class Ball : public Entity
{
public:
	Ball();
	~Ball();
	void update();
	void draw();
	void realign();
	void set(fRectangle bar);
	void launch(float horizontal);
	void bounceVert();
	void bounceHor();
	lineSeg getTrajectory();

	bool isSet;
	bool gameOver;

protected:
	UIRectangle _pic;
	Navigator _nav;
	Vertex _lastPos;
};