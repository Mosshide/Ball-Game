#pragma once
#include "UserInput.h"
#include "Background.h"
#include "UIText.h"
#include "Entity.h"

enum BoxStyle
{
	boxDynamicWidth,
	boxDynamicHeight,
	boxScroll
};

class TextBox : public Entity
{
public:
	TextBox();
	~TextBox();
	void update();
	void draw();
	void drawClipped(fRectangle clip);
	void setRGBA(Color c);
	void setBackgroundRGBA(Color c);
	void setText(std::string txt);
	void setText(int n) { setText(std::to_string(n)); }
	void setStyle(BoxStyle s);
	void setSize(GLfloat w, GLfloat h);
	void realign();

	bool centered;

	bool visible;
	bool background;
	
	std::string text;

protected:
	Background _bg;
	Color _color;
	Color _bgColor;
	std::vector<UIText> _lines;

	BoxStyle _style;
	GLfloat _scrollTotal;
	GLfloat _scrollAmount;
};