#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	id = mainMenuState;

	_startButton.setText("Start");
	_startButton.setPosition(render->getScreenWidth() / 2 - 100, render->getScreenHeight() - 40);
	_startButton.setRGBA(Color(.1f, .1f, .1f, 1.f));
	_startButton.setSize(200, 15);
}

MainMenuState::~MainMenuState()
{
}

StateEnum MainMenuState::update()
{
	_border.update();

	_startButton.update();


	if (_startButton.getClick(leftClick) == clickUp) return endlessState;
	if (_border.quit) return quitState;
	else return mainMenuState;
}

void MainMenuState::draw()
{
	_border.draw();

	_startButton.draw();
}