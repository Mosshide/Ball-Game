#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
	presence = fRectangle(10, 50, 16, 16);

	active = true;
	frame = 0;
	time = 0;
	fps = 0;

	_text.setRGBA(Color(.4f, .4f, .4f, 1.f));
	_text.setText(std::to_string(fps));

	realign();
}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::update()
{
	if (active)
	{
		time += gameTimer.getDelta();
		frame++;
		if (time >= 1000)
		{
			fps = int((float)frame / (time / 1000.f));
			time = 0;
			frame = 0;
			_text.setText(std::to_string(fps));
		}
	}
}

void FPSCounter::draw()
{
	_text.draw();
}

void FPSCounter::realign()
{
	_text.setPosition(presence.x, presence.y);
}