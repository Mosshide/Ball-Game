#pragma once
#include "TextBox.h"
#include "Button.h"

enum EditState
{
	untouched,
	editing,
	edited
};

class TextEntryBox : public TextBox
{
public:
	TextEntryBox();
	~TextEntryBox();
	void update();
	void draw();
	void drawClipped(fRectangle clip);
	void realign();

	bool active;
	EditState editState;
	int maxCharCount;

protected:
	Button _btn;
};