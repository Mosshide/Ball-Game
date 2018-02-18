#pragma once
#include "ImageButton.h"
#include "TextBox.h"
#include "Entity.h"

class ListElement : public Entity
{
public:
	ListElement();
	virtual ~ListElement();
	void update();
	void updateClipped(fRectangle clip);
	virtual void draw();
	virtual void drawClipped(fRectangle clip);
	virtual void realign();
	ClickState getClick(MouseClick mc);
	void setWidth(GLfloat w);

	bool selected;
	bool hovering;
	bool active;
	bool greedy;
	std::string name;

	fRectangle *_clip;
	ListElement *prev;
	ListElement *next;

protected:
	UIRectangle _highlight;
	UIRectangle _selection;
	ClickState _clickState[3];
};