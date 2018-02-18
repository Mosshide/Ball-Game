#pragma once
#include "UIRectangle.h"
#include "Navigator.h"

class Firefly : public Entity
{
public:
	Firefly();
	~Firefly();
	void update();
	void draw();
	void realign();

private:
	Navigator _nav;
	UIRectangle _fly;
	GLfloat _alpha;
};

