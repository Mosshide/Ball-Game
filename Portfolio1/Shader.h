#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <cstdio>
#include <string>
#include <fstream>
#include "Color.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "fRectangle.h"

class Shader
{
public:
	Shader();
	~Shader();
	bool loadProgram(std::string path);
	void setPointers();
	void setVertexPointer(GLsizei stride, const GLvoid* data);
	void setNormalPointer(GLsizei stride, const GLvoid* data);
	void setTexCoordPointer(GLsizei stride, const GLvoid* data);
	void enableVertexPointer();
	void disableVertexPointer();
	void enableNormalPointer();
	void disableNormalPointer();
	void enableTexCoordPointer();
	void disableTexCoordPointer();
	void setProjection(glm::mat4 matrix);
	void setCamera(glm::mat4 matrix);
	void setLight(glm::vec3 v);
	//void setModelView(glm::mat4 matrix);
	void setModelView(glm::mat4 trans, glm::mat4 rot, glm::mat4 scale);
	void leftMultProjection(glm::mat4 matrix);
	//void leftMultModelView(glm::mat4 matrix);
	void leftMultCamera(glm::mat4 matrix);
	void updateProjection();
	void updateCamera();
	void updateLight();
	void updateModelView();
	void setTextureColor(Color color);
	//void setLightPosition(Color color);
	void setTextureUnit(GLuint unit);
	GLuint loadShaderFromFile(std::string path, GLenum shaderType);
	bool bind();
	void unbind();
	GLuint getProgramID();
	glm::mat4 getProjection() { return mProjectionMatrix; }
	glm::mat4 getCamera() { return mCameraMatrix; }

protected:
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);

	//Attribute locations
	GLint mVertexPos3DLocation;
	GLint mTexCoordLocation;
	GLint mNormalLocation;

	//Coloring location
	GLint mTextureColorLocation;

	//light location
	glm::vec3 mLightPosition;
	GLint mLightPositionLocation;

	//Texture unit location
	GLint mTextureUnitLocation;

	//Projection matrix
	glm::mat4 mProjectionMatrix;
	GLint mProjectionMatrixLocation;

	//Camera matrix
	glm::mat4 mCameraMatrix;
	GLint mCameraMatrixLocation;

	//Modelview matrix
	//glm::mat4 mModelViewMatrix;
	//GLint mModelViewMatrixLocation;
	glm::mat4 modelTranslation;
	GLint modelTranslationLocation;
	glm::mat4 modelRotation;
	GLint modelRotationLocation;
	glm::mat4 modelScale;
	GLint modelScaleLocation;
	
	GLuint mProgramID;
};

