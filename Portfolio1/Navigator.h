#pragma once
#include "Vertex.h"
#include <vector>
#include "fRectangle.h"
#include "Physics.h"
#include "TextureBox.h"

class Navigator
{
public:
	Navigator();
	~Navigator();
	void draw();
	void moveTowardTarget(fRectangle &pres);
	void moveAlongPath(fRectangle &pres);
	void setPath(std::vector<Vertex> p);
	void move(fRectangle &pres);
	void turn(float t);
	void setDirection(float d);

	bool moved;

	//Vertex vel;
	Vertex vel;
	Vertex acc;
	float dist;
	Vertex target;
	bool reachedTarget;
	bool nextNode;
	//std::vector<TerrainType> pathable;
	float direction;
	std::vector<Vertex> path;

	//Model _points;
};