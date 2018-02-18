#pragma once
#include "Entity.h"
#include "TextureBox.h"

class UICircle : public Entity
{
public:
	UICircle();
	UICircle(const UICircle& v);
	UICircle& operator=(const UICircle& v);
	~UICircle();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setRGBA(Color c);
	void setTexture(GLuint t);
	void setWireframe(bool b);
	void initVBO();
	void freeVBO();
	void setCircle(GLfloat x, GLfloat y, GLfloat r);
	void setCircle(Vertex a, GLfloat r) { setCircle(a.x, a.y, r); }

	VertexData3D vertices[41];

protected:
	UIShader *_shader;
	Color _color;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
};

