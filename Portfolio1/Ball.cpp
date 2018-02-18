#include "Ball.h"

Ball::Ball()
{
	_pic.setTexture("blank");
	_color = Color(.4, .4, .4, 1.f);
	_pic.setRGBA(_color);

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
	_pic.setRGBA(_color);
	float _colorChange = .001f;
	if (_color.r > .4f) _color.r -= _colorChange;
	if (_color.r < .4f) _color.r = .4f;
	if (_color.g > .4f) _color.g -= _colorChange;
	if (_color.g < .4f) _color.g = .4f;
	if (_color.b > .4f) _color.b -= _colorChange;
	if (_color.b < .4f) _color.b = .4f;

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
		gameOver = true;
		//presence.y = 2 * render->getScreenHeight() - presence.h - presence.y;
		//bounceVert();
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
	_color.g += .6f;
	if (_color.g > 2.f) _color.g = 2.f;
}

void Ball::bounceVert()
{
	_nav.vel.y = -_nav.vel.y;
	_color.r += .6f;
	if (_color.r > 2.f) _color.r = 2.f;
}

void Ball::bounceHor()
{
	_nav.vel.x = -_nav.vel.x;
	_color.b += .6f;
	if (_color.b > 2.f) _color.b = 2.f;
}

lineSeg Ball::getTrajectory()
{
	lineSeg s = {_lastPos, presence.getMiddle()};
	return s;
}