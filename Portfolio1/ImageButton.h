#pragma once
#include "Button.h"
#include "UIRectangle.h"

class ImageButton : public Entity
{
public:
	ImageButton();
	~ImageButton();
	void update();
	void draw();
	void drawClipped(fRectangle clip);
	ClickState getClick(MouseClick mc);
	void setRGBA(Color c);
	void setBackgroundRGBA(Color c);
	void setImage(std::string txr);
	void setClip(fRectangle *clip);
	void setClip(fRectangle clip) { setClip(&clip); };
	void realign();

	bool visible;
	bool background;

	bool active;
	bool greedy;
	std::string name;

	bool hovering;
	bool hasBeenPressed;
	int timesPressed;

protected:
	Color _color;
	Color _bgColor;
	ClickState _clickState[3];
	Background _bg;
	UIRectangle _pic;
};

