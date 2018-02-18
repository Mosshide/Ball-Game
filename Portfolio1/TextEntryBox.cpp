#include "TextEntryBox.h"

TextEntryBox::TextEntryBox()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;
	setText("Enter Text");

	centered = true;

	visible = true;
	_style = boxDynamicWidth;
	background = true;

	_scrollAmount = 0;
	_scrollTotal = 0;
	active = true;

	editState = untouched;

	maxCharCount = INT_MAX;

	_bgColor = Color(.2f, .2f, .2f, 1.f);
}

TextEntryBox::~TextEntryBox()
{
}

void TextEntryBox::update()
{
	_btn.update();

	if (active)
	{
		if (_btn.getClick(leftClick) == clickUp)
		{
			if (editState == untouched)
			{
				setText("");
			}
			editState = editing;

			//Enable text input
			SDL_StartTextInput();
		}
		else if ((mouse->getClick(leftClick) == clickDown || keyboard->getKey(returnKey) == keyUp) && editState == editing)
		{
				editState = edited;

				//stop text input
				SDL_StopTextInput();
		}

		//if focused on this entry box
		if (editState == editing)
		{
			if (keyboard->inputText == "{b}")
			{
				if (text.length() > 0)
				{
					text.pop_back();
					setText(text);
				}
			}
			else if (keyboard->inputText == "{c}") SDL_SetClipboardText(text.c_str());
			else
			{
				text += keyboard->inputText;
				while (text.length() > maxCharCount)
				{
					text.pop_back();
				}
				setText(text);
			}
		}
	}
	else editState = edited;
}

void TextEntryBox::draw()
{
	drawClipped(presence);
}

void TextEntryBox::drawClipped(fRectangle clip)
{
	if (visible)
	{
		if (rectCollison(clip, presence))
		{
			if (active)
			{
				if (background) 
				{
					_bg.setRGBA(_bgColor);
					_bg.drawClipped(clip);
				}

				for (int i = 0; i < (int)_lines.size(); i++)
				{
					_lines[i].setRGBA(_color);
					_lines[i].drawClipped(clip);
				}
			}
			else
			{
				if (background)
				{
					_bg.setRGBA(Color(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a / 3.f));
					_bg.drawClipped(clip);
				}

				for (int i = 0; i < (int)_lines.size(); i++)
				{
					_lines[i].setRGBA(Color(_color.r, _color.g, _color.b, _color.a / 3.f));
					_lines[i].drawClipped(clip);
				}
			}
		}
	}
}

void TextEntryBox::realign()
{
	for (int i = 0; i < (int)_lines.size(); i++)
	{
		if (centered) _lines[i].setPosition(presence.x + (presence.w / 2) - (_lines[i].presence.w / 2), presence.y + (render->getFontSize(0) + 5) * i);
		else _lines[i].setPosition(presence.x, presence.y + (render->getFontSize(0) + 5) * i);
	}

	_bg.setPosition(presence.x, presence.y);
	_bg.setSize(presence.w, presence.h);

	_btn.setRect(presence);
}