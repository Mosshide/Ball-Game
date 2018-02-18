#pragma once
#include <glew.h>
#include "Vertex.h"

class fRectangle
{
public:
	fRectangle();
	fRectangle(GLfloat ex, GLfloat why, GLfloat width, GLfloat height);
	fRectangle(Vertex a, Vertex b);
	fRectangle(int ex, int why, int width, int height);
	~fRectangle();
	void set(GLfloat ex, GLfloat why, GLfloat width, GLfloat height);
	Vertex getVertex(int v);
	Vertex getMiddle() { return Vertex({ x + w / 2, y + h / 2 }); }
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
};

