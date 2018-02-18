#include "UITriangle.h"

UITriangle::UITriangle()
{
	_shader = render->getUIShader();
	_vbo = 0;
	_ibo = 0;
	_txr = textureBox->texture["blank"];
	_isUI = false;
	_wf = false;
	_numVertices = 3;
	initVBO();

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i].position.x = 0;
		vertices[i].position.y = 0;
		vertices[i].position.z = 0;

		vertices[i].texCoord.s = 0.f;
		vertices[i].texCoord.t = 0.f;
	}

	setRGBA(Color(1.f, 1.f, 1.f, 1.f));
}

UITriangle::UITriangle(const UITriangle& v)
{
	_shader = render->getUIShader();
	_vbo = 0;
	_ibo = 0;
	_txr = 0;
	_numVertices = 3;
	initVBO();

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setWireframe(v._wf);
	setUI(v._isUI);
}

UITriangle& UITriangle::operator=(const UITriangle& v)
{
	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setWireframe(v._wf);
	_isUI = v._isUI;

	return *this;
}

UITriangle::~UITriangle()
{
	freeVBO();
}

void UITriangle::draw()
{
	//Set texture ID
	glBindTexture(GL_TEXTURE_2D, _txr);

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//Set texture coordinate data
	_shader->setTexCoordPointer(sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, texCoord));

	//Set vertex data
	_shader->setVertexPointer(sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, position));

	_shader->setTextureColor(_color);

	//Draw quad using vertex data and index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glDrawElements(GL_TRIANGLES, _numVertices, GL_UNSIGNED_INT, NULL);
}

void UITriangle::drawClipped(fRectangle clip)
{
	draw();
}

void UITriangle::setRGBA(Color c)
{
	_color = c;
}

void UITriangle::setWireframe(bool b)
{
	_wf = b;
}

void UITriangle::setUI(bool b)
{
	if (_isUI != b)
	{
		_isUI = b;
		if (!_isUI)
		{
			for (int i = 0; i < _numVertices; i++)
			{
				//vertices[i].position.x += gameCamera.x;
				//vertices[i].position.y += gameCamera.y;
			}
		}
		else
		{
			for (int i = 0; i < _numVertices; i++)
			{
				//vertices[i].position.x -= gameCamera.x;
				//vertices[i].position.y -= gameCamera.y;
			}
		}
	}
}

void UITriangle::initVBO()
{
	//If texture is loaded and VBO does not already exist
	if (_vbo == 0)
	{
		//Vertex data
		VertexData3D *vData = new VertexData3D[_numVertices];
		GLuint *iData = new GLuint[_numVertices];

		//Set rendering indices
		iData[0] = 0;
		iData[1] = 1;
		iData[2] = 2;

		//Create VBO
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _numVertices * sizeof(VertexData3D), vData, GL_DYNAMIC_DRAW);

		//Create IBO
		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numVertices * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] vData;
		delete[] iData;
	}
}

void UITriangle::freeVBO()
{
	//Free VBO and IBO
	if (_vbo != 0)
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ibo);
		_vbo = 0;
		_ibo = 0;
	}
}

void UITriangle::setTriangle(V3rtex a, V3rtex b, V3rtex c)
{
	vertices[0].position = a;
	vertices[1].position = b;
	vertices[2].position = c;

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//Update vertex buffer data
	glBufferSubData(GL_ARRAY_BUFFER, 0, _numVertices * sizeof(VertexData3D), vertices);
}