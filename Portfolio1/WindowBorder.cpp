#include "WindowBorder.h"

WindowBorder::WindowBorder()
{
	quit = false;

	edge = fRectangle(1, 26, render->getScreenWidth() - 2, render->getScreenHeight() - 27);

	_border[0].setRect(fRectangle(0, 25, render->getScreenWidth(), 1));
	_border[0].setRGBA(Color(.5f, .5f, .5f, 1.f));
	_border[1].setRect(fRectangle(0, 25, render->getScreenWidth(), render->getScreenHeight() - 25));
	_border[1].setRGBA(Color(.5f, .5f, .5f, 1.f));

	_tab.setRect(fRectangle(0, 0, render->getScreenWidth() - 75, 24));
	_tab.setText("", false);
	_tab.setBackgroundRGBA(Color(0.f, 0.f, 0.f, 0.f));
	_tab.setRGBA(Color(0.f, 0.f, 0.f, 1.f));
	//tab.setBackgroundTxr("tab");
	_tab.border = false;

	_minimize.setRect(fRectangle(render->getScreenWidth() - 73, 3, 20, 20));
	_minimize.setText("", false);
	_minimize.setBackgroundRGBA(Color(.4f, .4f, .4f, 1.f));
	_minimize.setRGBA(Color(0.f, 0.f, 0.f, 1.f));
	_minimize.setBackgroundTxr("minimize");
	_minimize.border = false;

	_maximize.setRect(fRectangle(render->getScreenWidth() - 48, 3, 20, 20));
	_maximize.setText("", false);
	_maximize.setBackgroundRGBA(Color(.4f, .4f, .4f, 1.f));
	_maximize.setRGBA(Color(0.f, 0.f, 0.f, 1.f));
	_maximize.setBackgroundTxr("maximize");
	_maximize.border = false;
	_maximize.active = false;

	_close.setRect(fRectangle(render->getScreenWidth() - 23, 3, 20, 20));
	_close.setText("", false);
	_close.setBackgroundRGBA(Color(.4f, .4f, .4f, 1.f));
	_close.setRGBA(Color(0.f, 0.f, 0.f, 1.f));
	_close.setBackgroundTxr("close");
	_close.border = false;

	_bg.setRect(edge);
	_bg.setTexture("blank");
	_bg.setRGBA(Color(.1f, .1f, .1f, 1.f));
}

WindowBorder::~WindowBorder()
{
}

void WindowBorder::update()
{
	_fps.update();
	_tab.update();
	_minimize.update();
	_maximize.update();
	_close.update();

	if (_tab.getClick(leftClick) == clickDown)
	{
		localMouse[0] = mouse->x;
		localMouse[1] = mouse->y;
	}

	if (_tab.getClick(leftClick) == clickHold)
	{
		int globalMouse[2];
		SDL_GetGlobalMouseState(&globalMouse[0], &globalMouse[1]);
		SDL_SetWindowPosition(render->getWindow(), globalMouse[0] - localMouse[0], globalMouse[1] - localMouse[1]);
	}

	//window controls
	if (_minimize.getClick(leftClick) == clickUp)
	{
		SDL_MinimizeWindow(render->getWindow());
	}
	if (_maximize.getClick(leftClick) == clickUp)
	{
		//SDL_MaximizeWindow(render->getWindow());
	}
	if (_close.getClick(leftClick) == clickUp)
	{
		quit = true;
	}
}

void WindowBorder::draw()
{
	_border[1].draw();
	_border[0].draw();

	_tab.draw();
	_minimize.draw();
	_maximize.draw();
	_close.draw();

	_bg.draw();
	_fps.draw();
}