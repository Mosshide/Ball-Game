 #include "Inputmouse.h"

InputMouse::InputMouse()
{
	wheel = 0;
	p = { 0, 0 };
	x = 0;
	y = 0;
	worldRay = { 0, 0, 0 };
	worldX = 0;
	worldY = 0;
	dX = 0;
	dY = 0;
	
	for (int i = 0; i < 3; i++)
	{
		_click[i] = clickNone;
		clicked[i] = "no click";
		_lockclick[i] = false;
	}
}

InputMouse::~InputMouse()
{
}

void InputMouse::update()
{
	for (int i = 0; i < 3; i++)
	{
		clicked[i] = "no click";
		_lockclick[i] = false;
	}
	wheel = 0;

	for (int i = 0; i < 3; i++)
	{
		if (_click[i] == clickDown)
		{
			_click[i] = clickHold;
			clicked[i] = "none";
		}
		if (_click[i] == clickHold)
		{
			clicked[i] = "none";
		}
		if (_click[i] == clickUp)
		{
			_click[i] = clickNone;
		}
	}

	//2d position
	SDL_GetMouseState(&dX, &dY);
	dX = dX - x;
	dY = dY - y;
	SDL_GetMouseState(&x, &y);
	p = { (GLfloat)x, (GLfloat)y };

	//3d ray
	glm::vec3 ray = glm::vec3((2.0f * p.x) / render->getScreenWidth() - 1.0f,
		1.0f - (2.0f * p.y) / render->getScreenHeight(),
		1.0f);
	glm::vec4 ray_clip = glm::vec4(ray.x, ray.y, -1.0, 1.0);
	glm::vec4 ray_eye = glm::inverse(render->getShader()->getProjection()) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	glm::vec3 setup = glm::inverse(render->getShader()->getCamera()) * ray_eye;
	glm::vec3 ray_wor = glm::vec3(setup.x, setup.y, setup.z);
	worldRay = glm::normalize(ray_wor);
}

void InputMouse::receiveInput(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		_click[e.button.button - 1] = clickDown;
		clicked[e.button.button - 1] = "none";
	}
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		_click[e.button.button - 1] = clickUp;
		clicked[e.button.button - 1] = "none";
	}
	if (e.type == SDL_MOUSEWHEEL)
	{
		wheel = e.wheel.y;
	}
}

ClickState InputMouse::getClick(MouseClick mc)
{
	if (_lockclick[mc])
	{
		return clickNone;
	}
	else
	{
		return _click[mc];
	}
}

void InputMouse::lockClick(std::string *object, MouseClick mc)
{
	if (!_lockclick[mc])
	{
		_lockclick[mc] = true;
		clicked[mc] = *object;
		//printf("Click locked: %s; Button: %d\n", *object, mc);
	}
}

void InputMouse::sendInfoUI(bool greedy, fRectangle *pres, bool active, std::string *name, bool &h, ClickState *cs)
{
	h = false;
	Vertex pos = p;

	if (active)
	{
		if (pointInRect(pos, pres))
		{
			h = true;

			for (int i = 0; i < 3; i++)
			{
				if (getClick((MouseClick)i) == clickDown)
				{
					cs[i] = clickDown;
					if (greedy) lockClick(name, (MouseClick)i);
				}
				else if (getClick((MouseClick)i) == clickUp)
				{
					if (cs[i] == clickDown || cs[i] == clickHold)
					{
						cs[i] = clickUp;
						if (greedy) lockClick(name, (MouseClick)i);
					}
				}
				else if (cs[i] == clickDown)
				{
					cs[i] = clickHold;
					if (greedy) lockClick(name, (MouseClick)i);
				}
				else if (cs[i] == clickUp)
				{
					cs[i] = clickNone;
				}
				else if (cs[i] == clickHold)
				{
					if (greedy) lockClick(name, (MouseClick)i);
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				if (cs[i] != clickHold) cs[i] = clickNone;
				else if (getClick((MouseClick)i) == clickUp)
				{
					cs[i] = clickNone;
					if (greedy) lockClick(name, (MouseClick)i);
				}
				else if (getClick((MouseClick)i) == clickNone ||
					getClick((MouseClick)i) == clickDown) cs[i] = clickNone;
				else
				{
					if (greedy) lockClick(name, (MouseClick)i);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			cs[i] = clickNone;
		}

		if (greedy && pointInRect(pos, pres))
		{
			for (int i = 0; i < 3; i++)
			{
				lockClick(name, (MouseClick)i);
			}
		}
	}
}