#include "Ball.h"

Ball::Ball()
{
	_pic.setTexture("blank");
	_pic.setRGBA(Color(.4, .4, .4, 1.f));

	presence = fRectangle(0, 0, 16, 16);
	_nav.vel = { 0.f, 0.f };

	isSet = true;
	gameOver = false;

	realign();
}

Ball::~Ball()
{
}

void Ball::update()
{
	_lastPos = presence.getMiddle();

	_nav.move(presence);

	if (presence.x < 0.f)
	{
		presence.x = -presence.x;
		bounceHor();
	}
	if (presence.x > render->getScreenWidth() - presence.w)
	{
		presence.x = 2 * render->getScreenWidth() - presence.w - presence.x;
		bounceHor();
	}

	if (presence.y < 0.f)
	{
		presence.y = -presence.y;
		bounceVert();
	}
	if (presence.y > render->getScreenHeight() - presence.h)
	{
		//gameOver = true;
		presence.y = 2 * render->getScreenHeight() - presence.h - presence.y;
		bounceVert();
	}
}

void Ball::draw()
{
	_pic.draw();

	realign();
}

void Ball::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);
}

void Ball::set(fRectangle bar)
{
	setPosition(bar.x + (bar.w / 2) - (presence.w / 2), bar.y - presence.h);
	_nav.vel = { 0.f, 0.f };
	_nav.acc = { 0.f, 0.f };
	isSet = true;
}

void Ball::launch(float horizontal)
{
	_nav.vel = { (float)cos((M_PI / 6) + (horizontal * (4 * M_PI / 6))), 1.2f };
	_nav.acc = { 0.f, -.001f };
	isSet = false;
}

void Ball::bounceVert()
{
	_nav.vel.y = -_nav.vel.y;
}

void Ball::bounceHor()
{
	_nav.vel.x = -_nav.vel.x;
}

lineSeg Ball::getTrajectory()
{
	lineSeg s = {_lastPos, presence.getMiddle()};
	return s;
}