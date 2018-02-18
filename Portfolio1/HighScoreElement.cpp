#include "HighScoreElement.h"

HighScoreElement::HighScoreElement()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 32;

	selected = false;
	hovering = false;

	_highlight.setWireframe(true);
	_highlight.setRGBA(Color(.6f, .6f, .6f, 1.f));

	_selection.setWireframe(false);
	_selection.setRGBA(Color(.2f, .2f, .2f, 1.f));

	prev = nullptr;
	next = nullptr;

	score.setText("0");
	name.setText("WLS");

	realign();
}

HighScoreElement::~HighScoreElement()
{

}

void HighScoreElement::draw()
{
	if (selected)
	{
		_selection.draw();
	}

	score.draw();
	name.draw();

	if (hovering)
	{
		_highlight.draw();
	}
}

void HighScoreElement::drawClipped(fRectangle clip)
{
	if (rectCollison(clip, presence))
	{
		clip = rectIntersection(presence, clip);

		if (selected)
		{
			_selection.drawClipped(clip);
		}

		score.drawClipped(clip);
		name.drawClipped(clip);

		if (hovering)
		{
			_highlight.drawClipped(clip);
		}
	}
}

void HighScoreElement::realign()
{
	_highlight.setRect(presence);
	_selection.setRect(presence);

	score.setPosition(presence.x + 60, presence.y + 5);
	name.setPosition(presence.x + 5, presence.y + 5);
}