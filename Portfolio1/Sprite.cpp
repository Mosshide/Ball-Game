#include "Sprite.h"

Sprite::Sprite()
{
	_shader = render->getShader();
	_vibo = { 0, 0, 4 };
	_txr = textureBox->texture["blank"];
	_bounds = TILE_WIDTH / 2;

	_color = Color(white, .1f);
}

Sprite::Sprite(const Sprite& v)
{
	_shader = render->getShader();
	_vibo = v._vibo;
	_scalar = v._scalar;
	_rotation = v._rotation;
	_translation = v._translation;
	_color = v._color;
	_txr = v._txr;
	_bounds = v._bounds;
}

Sprite& Sprite::operator=(const Sprite& v)
{
	_vibo = v._vibo;
	_scalar = v._scalar;
	_rotation = v._rotation;
	_translation = v._translation;
	_color = v._color;
	_txr = v._txr;
	_bounds = v._bounds;

	return *this;
}

Sprite::~Sprite()
{
}

void Sprite::setTxr(std::string t)
{
	_txr = textureBox->texture[t];
}

void Sprite::setColor(Color c)
{
	_color = c;
}

void Sprite::setBounds(GLfloat b)
{
	_bounds = b;
}

void Sprite::setTranslation(float x, float y, float z)
{
	//_translation = glm::translate(glm::vec3(x, y, z));
	_translation = glm::mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);
	//_transformation = _translation * _scalar * _rotation;
}

void Sprite::setRotation(float angle, float x, float y, float z)
{
	_rotation = glm::rotate(angle, glm::vec3(x, y, z));
	//_transformation = _translation * _scalar * _rotation;
}

void Sprite::setScalar(float x, float y, float z)
{
	_scalar = glm::scale(glm::vec3(x, y, z));
	//_transformation = _translation * _scalar * _rotation;
}

void Sprite::setTransformation(glm::mat4 m)
{
	_transformation = m;
}

bool Sprite::isPicked()
{
	GLfloat dist = 0;
	if (rayPlaneCollision(render->getCameraPos(), mouse->worldRay, mouse->worldRay, glm::vec3(_translation[3]), &dist))
	{
		glm::vec3 target = render->getCameraPos() + mouse->worldRay * dist;
		V3rtex a = { target.x, target.y, target.z };
		V3rtex b = { _translation[3][0], _translation[3][1], _translation[3][2] };

		if (distanc3(a, b) < _bounds) return true;
	}

	return false;
}

void Sprite::draw()
{
	_shader->setModelView(_translation, _rotation, _scalar);
	//_shader->updateModelView();

	//Set texture ID
	glBindTexture(GL_TEXTURE_2D, _txr);
	/*GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
	printf("Error binding model texture model! %s\n", gluErrorString(error));
	}*/

	//Update vertex buffer data
	glBindBuffer(GL_ARRAY_BUFFER, _vibo.vbo);
	/*error = glGetError();
	if (error != GL_NO_ERROR)
	{
	printf("Error binding model vbo! %s\n", gluErrorString(error));
	}*/

	//Set texture coordinate data
	_shader->setPointers();
	/*error = glGetError();
	if (error != GL_NO_ERROR)
	{
	printf("Error setting model vertex pointer! %s\n", gluErrorString(error));
	}*/

	_shader->setTextureColor(_color);
	/*error = glGetError();
	if (error != GL_NO_ERROR)
	{
	printf("Error setting model color! %s\n", gluErrorString(error));
	}*/

	//Draw quad using vertex data and index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vibo.ibo);
	/*error = glGetError();
	if (error != GL_NO_ERROR)
	{
	printf("Error binding model ibo! %s\n", gluErrorString(error));
	}*/

	glDrawElements(GL_TRIANGLE_FAN, _vibo.size, GL_UNSIGNED_INT, NULL);
	/*error = glGetError();
	if (error != GL_NO_ERROR)
	{
	printf("Error drawing model! %s\n", gluErrorString(error));
	}*/
}

void Sprite::initVBO()
{
	//If texture is loaded and VBO does not already exist
	if (_vibo.vbo == 0)
	{
		//Vertex data
		VertexData3D *vData = new VertexData3D[_vibo.size];

		vData[0].position.x = 0.f;
		vData[0].position.y = 0.f;
		vData[1].position.x = 1.f;
		vData[1].position.y = 0.f;
		vData[2].position.x = 1.f;
		vData[2].position.y = 1.f;
		vData[3].position.x = 0.f;
		vData[3].position.y = 1.f;

		vData[0].texCoord.s = _clip.x;
		vData[0].texCoord.t = _clip.y;
		vData[1].texCoord.s = _clip.x + _clip.w;
		vData[1].texCoord.t = _clip.y;
		vData[2].texCoord.s = _clip.x + _clip.w;
		vData[2].texCoord.t = _clip.y + _clip.h;
		vData[3].texCoord.s = _clip.x;
		vData[3].texCoord.t = _clip.y + _clip.h;

		/*vertices[0].normals.x = presence.x;
		vertices[0].normals.y = presence.y;
		vertices[1].normals.x = presence.x + presence.w;
		vertices[1].normals.y = presence.y;
		vertices[2].normals.x = presence.x + presence.w;
		vertices[2].normals.y = presence.y + presence.h;
		vertices[3].normals.x = presence.x;
		vertices[3].normals.y = presence.y + presence.h;*/


		GLuint *iData = new GLuint[_vibo.size];

		//Set rendering indices
		iData[0] = 0;
		iData[1] = 1;
		iData[2] = 2;
		iData[3] = 3;

		//Create VBO
		glGenBuffers(1, &_vibo.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vibo.vbo);
		glBufferData(GL_ARRAY_BUFFER, _vibo.size * sizeof(VertexData3D), vData, GL_DYNAMIC_DRAW);

		//Create IBO
		glGenBuffers(1, &_vibo.ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vibo.ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _vibo.size * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] vData;
		delete[] iData;
	}
}

void Sprite::freeVBO()
{
	//Free VBO and IBO
	if (_vibo.vbo != 0)
	{
		glDeleteBuffers(1, &_vibo.vbo);
		glDeleteBuffers(1, &_vibo.ibo);
		_vibo.vbo = 0;
		_vibo.ibo = 0;
	}
}