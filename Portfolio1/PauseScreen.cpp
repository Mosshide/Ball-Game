#include "PauseScreen.h"

PauseScreen::PauseScreen()
{
	quit = false;

	_quitButton.setText("Quit");
	_quitButton.setPosition(render->getScreenWidth() / 2 - 100, render->getScreenHeight() / 2);
	_quitButton.setRGBA(Color(.1f, .1f, .1f, 1.f));
	_quitButton.setSize(200, 15);

	_bg.setRect(fRectangle(1, 26, render->getScreenWidth() - 2, render->getScreenHeight() - 27));
	_bg.setTexture("blank");
	_bg.setRGBA(Color(.1f, .1f, .1f, .5f));
}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::update()
{
	_quitButton.update();
	if (_quitButton.getClick(leftClick) == clickUp) quit = true;
}

void PauseScreen::draw()
{
	_bg.draw();
	_quitButton.draw();
}
