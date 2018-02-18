#include "Bar.h"

Bar::Bar()
{
	_pic.setTexture("blank");
	_pic.setRGBA(Color(.4, .4, .4, 1.f));
	presence = fRectangle(render->getScreenWidth() / 2 - 100, render->getScreenHeight() - 40, 200, 15);

	vel = 0.f;

	realign();
}

Bar::~Bar()
{
}

void Bar::update()
{
	vel = 0.f;
	if (keyboard->getKey('d') == keyHold) vel += 1.5f;
	if (keyboard->getKey('a') == keyHold) vel -= 1.5f;
	offsetPosition(gameTimer.getDelta() * vel, 0.f);

	if (presence.x < 0.f) presence.x = 0.f;
	if (presence.x > render->getScreenWidth() - presence.w) presence.x = render->getScreenWidth() - presence.w;
}

void Bar::draw()
{
	_pic.draw();
}

void Bar::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);
}

int Bar::collision(lineSeg l, float *wratio)
{
	Vertex ints[4];
	lineSeg s[4];

	int closest = -1;
	int closestd = INT_MAX;

	for (int i = 0; i < 4; i++)
	{
		s[i] = { presence.getVertex(i), presence.getVertex(i + 1) };
		if (segIntersection(l, s[i], &ints[i]))
		{
			int d = distance(l.a, ints[i]);
			if (d < closestd)
			{
				closest = i;
				closestd = d;
			}
		}
	}

	if (wratio != nullptr) *wratio = (ints[closest].x - presence.x) / presence.w;

	return closest;
}