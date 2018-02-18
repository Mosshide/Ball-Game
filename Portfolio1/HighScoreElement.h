#pragma once
#include "ListElement.h"

class HighScoreElement : public ListElement
{
public:
	HighScoreElement();
	~HighScoreElement();
	void draw();
	void drawClipped(fRectangle clip);
	void realign();

	UIText score;
	UIText name;
};

