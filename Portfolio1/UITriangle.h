#pragma once
#include "TextureBox.h"

class UITriangle// : public Entity
{
public:
	UITriangle();
	UITriangle(const UITriangle& v);
	UITriangle& operator=(const UITriangle& v);
	~UITriangle();
	//void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setRGBA(Color c);
	void setWireframe(bool b);
	void setUI(bool b);
	void initVBO();
	void freeVBO();
	void setTriangle(V3rtex a, V3rtex b, V3rtex c);

	VertexData3D vertices[3];

protected:
	UIShader *_shader;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
	bool _isUI;
	Color _color;
};

