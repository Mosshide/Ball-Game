#include "UICircle.h"

UICircle::UICircle()
{
	_shader = render->getUIShader();
	_vbo = 0;
	_ibo = 0;
	_txr = textureBox->texture["blank"];
	_wf = false;
	_numVertices = 41;
	initVBO();

	setCircle(0.f, 0.f, 64.f);
	setRGBA(Color(.1f, .1f, .8f, .3f));
}

UICircle::UICircle(const UICircle& v)
{
	_shader = render->getUIShader();
	_vbo = 0;
	_ibo = 0;
	_numVertices = 41;
	initVBO();

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setTexture(v._txr);
	_wf = v._wf;
}

UICircle& UICircle::operator=(const UICircle& v)
{
	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	setTexture(v._txr);
	setWireframe(v._wf);

	return *this;
}

UICircle::~UICircle()
{
	freeVBO();
}

void UICircle::draw()
{
	//Set texture ID
	glBindTexture(GL_TEXTURE_2D, _txr);

	//_shader->enableVertexPointer();
	//_shader->enableTexCoordPointer();

	//Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//Update vertex buffer data
	glBufferSubData(GL_ARRAY_BUFFER, 0, _numVertices * sizeof(VertexData3D), vertices);

	//Set texture coordinate data
	_shader->setTexCoordPointer(sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, texCoord));

	//Set vertex data
	_shader->setVertexPointer(sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, position));

	_shader->setTextureColor(_color);

	//Draw quad using vertex data and index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	if (_wf)
	{
		glDrawElements(GL_LINE_LOOP, 3 * (_numVertices - 1), GL_UNSIGNED_INT, NULL);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, 3 * (_numVertices - 1), GL_UNSIGNED_INT, NULL);
	}
}

void UICircle::drawClipped(fRectangle clip)
{
	draw();
}

void UICircle::setRGBA(Color c)
{
	_color = c;
}

void UICircle::setTexture(GLuint t)
{
	_txr = t;
}

void UICircle::setWireframe(bool b)
{
	_wf = b;
}

void UICircle::freeVBO()
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

void UICircle::initVBO()
{
	//If texture is loaded and VBO does not already exist
	if (_vbo == 0)
	{
		//Vertex data
		VertexData2D *vData = new VertexData2D[_numVertices];
		GLuint *iData = new GLuint[3 * (_numVertices - 1)];

		//Set rendering indices
		for (int i = 0; i < 3 * (_numVertices - 1); i += 3)
		{
			iData[i] = 0;
		}
		for (int i = 1; i < 3 * (_numVertices - 1); i += 3)
		{
			iData[i] = (i / 3) + 1;
		}
		for (int i = 2; i < 3 * (_numVertices - 1) - 1; i += 3)
		{
			iData[i] = (i / 3) + 2;
		}
		iData[3 * (_numVertices - 1) - 1] = 1;

		//Create VBO
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _numVertices * sizeof(VertexData3D), vData, GL_DYNAMIC_DRAW);

		//Create IBO
		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * (_numVertices - 1) * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] vData;
		delete[] iData;
	}
}

void UICircle::setCircle(GLfloat x, GLfloat y, GLfloat r)
{
	vertices[0].position.x = x;
	vertices[0].position.y = y;

	GLfloat twicePi = GLfloat(2.0f * M_PI);
	for (int i = 1; i < _numVertices; i++) {
		vertices[i].position.x = x + (r * cos(i *  twicePi / (_numVertices - 1)));
		vertices[i].position.y = y + (r * sin(i * twicePi / (_numVertices - 1)));
	}
}