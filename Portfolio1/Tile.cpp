#include "Tile.h"

Tile::Tile()
{
	setSize(48, 16);
	setPosition(0, 0);

	_pic.setTexture("blank");
	_pic.setRGBA(Color(.4f, .4f, .4f, 1.f));

	alive = true;
}

Tile::~Tile()
{
}

void Tile::update()
{

}

void Tile::draw()
{
	if (alive) _pic.draw();
}

void Tile::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);
}

int Tile::collision(lineSeg l)
{
	Vertex ints[4];
	lineSeg s[4];

	int closest = -1;
	int closestd = INT_MAX;

	for (int i = 0; i < 4; i++)
	{
		s[i] = { presence.getVertex(i), presence.getVertex(i + 1) };
		if (segIntersection(l, s[i], &ints[i]))
		{
			int d = distance(l.a, ints[i]);
			if (d < closestd)
			{
				closest = i;
				closestd = d;
			}
		}
	}

	return closest;
}