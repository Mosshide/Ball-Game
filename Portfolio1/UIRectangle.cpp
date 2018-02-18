#include "UIRectangle.h"

UIRectangle::UIRectangle()
{
	_shader = render->getUIShader();
	_vbo = 0;
	_ibo = 0;
	_txr = textureBox->texture["blank"];
	_wf = false;
	_numVertices = 4;
	initVBO();

	_rotation = glm::mat4();

	setPosition(0, 0);
	setSize(64, 64);

	setClip(fRectangle(0.f, 0.f, 1.f, 1.f));

	setRGBA(Color(1.f, 1.f, 1.f, 1.f));

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i].position.x = 0;
		vertices[i].position.y = 0;
		vertices[i].position.z = 0;
	}

	visible = true;
}

UIRectangle::UIRectangle(const UIRectangle& v)
{
	_shader = render->getUIShader();
	_vbo = 0;
	_ibo = 0;
	_numVertices = 4;
	initVBO();
	_color = v._color;
	_clip = v._clip;
	_wf = v._wf;
	presence = v.presence;
	_rotation = v._rotation;

	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	_txr = v._txr;
	setWireframe(v._wf);
	_rotation = v._rotation;
}

UIRectangle& UIRectangle::operator=(const UIRectangle& v)
{
	for (int i = 0; i < _numVertices; i++)
	{
		vertices[i] = v.vertices[i];
	}

	_txr = v._txr;
	setWireframe(v._wf);
	_rotation = v._rotation;
	_color = v._color;
	_clip = v._clip;
	_wf = v._wf;
	presence = v.presence;
	_rotation = v._rotation;

	return *this;
}

UIRectangle::~UIRectangle()
{
	freeVBO();
}

void UIRectangle::draw()
{
	if (visible)
	{
		vertices[0].position.x = presence.x;
		vertices[0].position.y = presence.y;
		vertices[1].position.x = presence.x + presence.w;
		vertices[1].position.y = presence.y;
		vertices[2].position.x = presence.x + presence.w;
		vertices[2].position.y = presence.y + presence.h;
		vertices[3].position.x = presence.x;
		vertices[3].position.y = presence.y + presence.h;

		vertices[0].texCoord.s = _clip.x;
		vertices[0].texCoord.t = _clip.y;
		vertices[1].texCoord.s = _clip.x + _clip.w;
		vertices[1].texCoord.t = _clip.y;
		vertices[2].texCoord.s = _clip.x + _clip.w;
		vertices[2].texCoord.t = _clip.y + _clip.h;
		vertices[3].texCoord.s = _clip.x;
		vertices[3].texCoord.t = _clip.y + _clip.h;

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
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_LINE_LOOP, _numVertices, GL_UNSIGNED_INT, NULL);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else glDrawElements(GL_TRIANGLE_FAN, _numVertices, GL_UNSIGNED_INT, NULL);


		//_shader->disableVertexPointer();
		//_shader->disableTexCoordPointer();

		//glBindTexture(GL_TEXTURE_2D, 0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//_shader->setModelView(glm::mat4());
		//_shader->updateModelView();
	}
}

void UIRectangle::drawClipped(fRectangle clip)
{
	if (visible)
	{
		if (rectCollison(clip, presence))
		{
			//VertexData2D temp[4] = { vertices[0], vertices[1], vertices[2], vertices[3] };

			clip = rectIntersection(presence, clip);

			vertices[0].position.x = clip.x;
			vertices[0].position.y = clip.y;
			vertices[1].position.x = clip.x + clip.w;
			vertices[1].position.y = clip.y;
			vertices[2].position.x = clip.x + clip.w;
			vertices[2].position.y = clip.y + clip.h;
			vertices[3].position.x = clip.x;
			vertices[3].position.y = clip.y + clip.h;

			clip.x = _clip.x + ((vertices[0].position.x - presence.x) / presence.w) * _clip.w;
			clip.y = _clip.y + ((vertices[0].position.y - presence.y) / presence.h) * _clip.h;
			clip.w = (clip.w / presence.w) * _clip.w;
			clip.h = (clip.h / presence.h) * _clip.h;

			vertices[0].texCoord.s = clip.x;
			vertices[0].texCoord.t = clip.y;
			vertices[1].texCoord.s = clip.x + clip.w;
			vertices[1].texCoord.t = clip.y;
			vertices[2].texCoord.s = clip.x + clip.w;
			vertices[2].texCoord.t = clip.y + clip.h;
			vertices[3].texCoord.s = clip.x;
			vertices[3].texCoord.t = clip.y + clip.h;



			//Set texture ID
			if (_txr != 0) glBindTexture(GL_TEXTURE_2D, _txr);

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
				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_LINE_LOOP, _numVertices, GL_UNSIGNED_INT, NULL);
				//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else glDrawElements(GL_TRIANGLE_FAN, _numVertices, GL_UNSIGNED_INT, NULL);

			//_shader->disableVertexPointer();
			//_shader->disableTexCoordPointer();

			//glBindTexture(GL_TEXTURE_2D, 0);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			//_shader->setModelView(glm::mat4());
			//_shader->updateModelView();
		}
	}
}

void UIRectangle::setPosition(GLfloat x, GLfloat y)
{
	presence.x = x;
	presence.y = y;
}

void UIRectangle::offsetPosition(GLfloat x, GLfloat y)
{
	presence.x += x;
	presence.y += y;
}

void UIRectangle::setSize(GLfloat w, GLfloat h)
{
	presence.w = w;
	presence.h = h;
}

void UIRectangle::setRect(fRectangle r)
{
	presence = r;
}

void UIRectangle::setRGBA(Color c)
{
	_color = c;
}

void UIRectangle::setRotation(glm::mat4 r)
{
	_rotation = r;
}

void UIRectangle::setTexture(std::string t)
{
	_txr = textureBox->texture[t];
}

void UIRectangle::setWireframe(bool b)
{
	_wf = b;
}

void UIRectangle::setClip(fRectangle *t)
{
	_clip = *t;
}

void UIRectangle::initVBO()
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
		iData[3] = 3;

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

void UIRectangle::freeVBO()
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