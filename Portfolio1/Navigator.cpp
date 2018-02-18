#include "Navigator.h"

Navigator::Navigator()
{
	moved = false;
	nextNode = false;
	reachedTarget = false;

	//_points.setModel("square");
}

Navigator::~Navigator()
{
}

void Navigator::draw()
{
	/*for (int i = 0; i < (int)path.size(); i++)
	{
		_points.setTranslation(path[i].x, .01f, path[i].y);
		_points.draw();
	}*/
}

void Navigator::moveTowardTarget(fRectangle &pres)
{
	moved = false;

	Vertex d = { vel.x * gameTimer.getDelta(), vel.y * gameTimer.getDelta() };

	if (d.x != 0.f || d.y != 0.f) moved = true;

	direction = getDirection(pres.getMiddle(), target);
	while (direction < 0.f) direction += float(2.f * M_PI);
	while (direction > 2.f * M_PI) direction -= float(2.f * M_PI);

	Vertex origin = pres.getMiddle();
	if (distance(origin, d) > distance(origin, target))
	{
		pres.x = target.x;
		pres.y = target.y;
		nextNode = true;
	}
	else
	{
		pres.x -= d.x;
		pres.y -= d.y;
	}
}

void Navigator::moveAlongPath(fRectangle &pres)
{
	if (!reachedTarget)
	{
		if (!path.empty())
		{
			moveTowardTarget(pres);

			if (nextNode)
			{
				path.pop_back();
				if (path.empty()) reachedTarget = true;
				else
				{
					target.x = path.back().x;
					target.y = path.back().y;
				}
				nextNode = false;
			}
		}
	}
}

void Navigator::setPath(std::vector<Vertex> p)
{
	path = p;
	if ((int)path.size() > 0)
	{
		target.x = path.back().x;
		target.y = path.back().y;
		reachedTarget = false;
	}
}

void Navigator::move(fRectangle &pres)
{
	moved = false;
	dist = 0;

	vel.x += acc.x * gameTimer.getDelta();
	vel.y += acc.y * gameTimer.getDelta();
	Vertex d = { vel.x * gameTimer.getDelta(), vel.y * gameTimer.getDelta() };
	if (d.x != 0.f || d.y != 0.f) moved = true;

	pres.x -= d.x;
	pres.y -= d.y;
}

void Navigator::turn(float t)
{
	direction += t;

	if (direction < 0.f) direction += 2.f * (float)M_PI;
	if (direction > 2.f * (float)M_PI) direction -= 2.f * (float)M_PI;
}

void Navigator::setDirection(float d)
{
	direction = d;

	if (direction < 0.f) direction += 2.f * (float)M_PI;
	if (direction > 2.f * (float)M_PI) direction -= 2.f * (float)M_PI;
}