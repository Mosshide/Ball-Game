#pragma once
#include <glew.h>
#include "glm/glm.hpp"

struct Vertex
{
	GLfloat x;
	GLfloat y;
};

struct lineSeg
{
	Vertex a;
	Vertex b;
};

struct V3rtex
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct TexCoord
{
	GLfloat s;
	GLfloat t;
};

struct VertexData2D
{
	Vertex position;
	TexCoord texCoord;
};

struct VertexData3D
{
	V3rtex position;
	TexCoord texCoord;
	V3rtex normals;
};

struct IndexData3D
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;
};