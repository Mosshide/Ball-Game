#pragma once
#include "TextureBox.h"

class UIRectangle : public Entity
{
public:
	UIRectangle();
	UIRectangle(const UIRectangle& v);
	UIRectangle& operator=(const UIRectangle& v);
	~UIRectangle();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setPosition(GLfloat x, GLfloat y);
	void offsetPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat w, GLfloat h);
	void setSize(int w, int h) { setSize((float)w, (float)h); }
	void setRect(fRectangle r);
	void setClip(fRectangle *clip);
	void setClip(fRectangle clip) { setClip(&clip); };
	void setRGBA(Color c);
	void setRotation(glm::mat4 r);
	void setTexture(std::string t);
	void setWireframe(bool b);
	void initVBO();
	void freeVBO();

	VertexData3D vertices[4];
	bool visible;

protected:
	UIShader *_shader;
	Color _color;
	glm::mat4 _rotation;
	fRectangle _clip;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
};