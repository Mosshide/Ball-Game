#include "Shader.h"

Shader::Shader()
{
	mProgramID = NULL;

	mVertexPos3DLocation = -1;
	mTexCoordLocation = -1;

	mProjectionMatrixLocation = -1;
	mCameraMatrixLocation = -1;
	//mModelViewMatrixLocation = -1;
	modelTranslationLocation = -1;
	modelRotationLocation = -1;
	modelScaleLocation = -1;
	mTextureColorLocation = -1;
	mTextureUnitLocation = -1;
	mLightPositionLocation = -1;
}

Shader::~Shader()
{
	glDeleteProgram(mProgramID);
}

bool Shader::loadProgram(std::string path)
{
	//Generate program
	mProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShaderFromFile((path + ".glvs").c_str(), GL_VERTEX_SHADER);

	//Check for errors
	if (vertexShader == 0)
	{
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach vertex shader to program
	glAttachShader(mProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = loadShaderFromFile((path + ".glfs").c_str(), GL_FRAGMENT_SHADER);

	//Check for errors
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach fragment shader to program
	glAttachShader(mProgramID, fragmentShader);

	//Link program
	glLinkProgram(mProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", mProgramID);
		printProgramLog(mProgramID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Clean up excess shader references
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	mProjectionMatrixLocation = glGetUniformLocation(mProgramID, "projection");
	if (mProjectionMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "projection");
	}

	mCameraMatrixLocation = glGetUniformLocation(mProgramID, "camera");
	if (mCameraMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "camera");
	}

	/*mModelViewMatrixLocation = glGetUniformLocation(mProgramID, "model");
	if (mModelViewMatrixLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "model");
	}*/
	modelTranslationLocation = glGetUniformLocation(mProgramID, "modelTranslation");
	if (modelTranslationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "modelTranslation");
	}
	modelRotationLocation = glGetUniformLocation(mProgramID, "modelRotation");
	if (modelRotationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "modelRotation");
	}
	modelScaleLocation = glGetUniformLocation(mProgramID, "modelScale");
	if (modelScaleLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "modelScale");
	}

	mLightPositionLocation = glGetUniformLocation(mProgramID, "lightPos");
	if (mLightPositionLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "lightPos");
	}

	/*mRotationLocation = glGetUniformLocation(mProgramID, "rotation");
	if (mRotationLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "rotation");
	}*/

	//Get variable locations
	mVertexPos3DLocation = glGetAttribLocation(mProgramID, "LVertexPos3D");
	if (mVertexPos3DLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LVertexPos3D");
	}

	mNormalLocation = glGetAttribLocation(mProgramID, "normal");
	if (mNormalLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "normal");
	}

	mTexCoordLocation = glGetAttribLocation(mProgramID, "LTexCoord");
	if (mTexCoordLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTexCoord");
	}

	mTextureColorLocation = glGetUniformLocation(mProgramID, "LTextureColor");
	if (mTextureColorLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTextureColor");
	}

	mTextureUnitLocation = glGetUniformLocation(mProgramID, "LTextureUnit");
	if (mTextureUnitLocation == -1)
	{
		printf("%s is not a valid glsl program variable!\n", "LTextureUnit");
	}

	return true;
}

void Shader::setPointers()
{
	glVertexAttribPointer(mVertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, position));
	glVertexAttribPointer(mNormalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, normals));
	glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (GLvoid*)offsetof(VertexData3D, texCoord));
}

void Shader::setVertexPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setNormalPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mNormalLocation, 3, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setTexCoordPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::enableVertexPointer()
{
	glEnableVertexAttribArray(mVertexPos3DLocation);
}

void Shader::disableVertexPointer()
{
	glDisableVertexAttribArray(mVertexPos3DLocation);
}

void Shader::enableNormalPointer()
{
	glEnableVertexAttribArray(mNormalLocation);
}

void Shader::disableNormalPointer()
{
	glDisableVertexAttribArray(mNormalLocation);
}

void Shader::enableTexCoordPointer()
{
	glEnableVertexAttribArray(mTexCoordLocation);
}

void Shader::disableTexCoordPointer()
{
	glDisableVertexAttribArray(mTexCoordLocation);
}

void Shader::setProjection(glm::mat4 matrix)
{
	mProjectionMatrix = matrix;
}

void Shader::setCamera(glm::mat4 matrix)
{
	mCameraMatrix = matrix;
}

void Shader::setLight(glm::vec3 v)
{
	mLightPosition = v;
}

//void Shader::setModelView(glm::mat4 matrix)
//{
//	mModelViewMatrix = matrix;
//}

void Shader::setModelView(glm::mat4 trans, glm::mat4 rot, glm::mat4 scale)
{
	modelTranslation = trans;
	modelRotation = rot;
	modelScale = scale;
	updateModelView();
}

void Shader::leftMultProjection(glm::mat4 matrix)
{
	mProjectionMatrix = matrix * mProjectionMatrix;
}

//void Shader::leftMultModelView(glm::mat4 matrix)
//{
//	mModelViewMatrix = matrix * mModelViewMatrix;
//}

void Shader::leftMultCamera(glm::mat4 matrix)
{
	mCameraMatrix = matrix * mCameraMatrix;
}

void Shader::updateProjection()
{
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
}

void Shader::updateCamera()
{
	glUniformMatrix4fv(mCameraMatrixLocation, 1, GL_FALSE, glm::value_ptr(mCameraMatrix));
}

void Shader::updateLight()
{
	glUniform3fv(mLightPositionLocation, 1, glm::value_ptr(mLightPosition));
}

//void Shader::updateModelView()
//{
//	glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelViewMatrix));
//}

void Shader::updateModelView()
{
	glUniformMatrix4fv(modelTranslationLocation, 1, GL_FALSE, glm::value_ptr(modelTranslation));
	glUniformMatrix4fv(modelRotationLocation, 1, GL_FALSE, glm::value_ptr(modelRotation));
	glUniformMatrix4fv(modelScaleLocation, 1, GL_FALSE, glm::value_ptr(modelScale));
}

void Shader::setTextureColor(Color color)
{
	glUniform4fv(mTextureColorLocation, 1, (const GLfloat*)&color.get());
}

void Shader::setTextureUnit(GLuint unit)
{
	glUniform1i(mTextureUnitLocation, unit);
}

GLuint Shader::loadShaderFromFile(std::string path, GLenum shaderType)
{
	//Open file
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	//Source file loaded
	if (sourceFile)
	{
		//Get shader source
		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
		//Create shader ID
		shaderID = glCreateShader(shaderType);

		//Set shader source
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

		//Compile shader source
		glCompileShader(shaderID);

		//Check shader for errors
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
			printShaderLog(shaderID);
			glDeleteShader(shaderID);
			shaderID = 0;
		}
	}
	else
	{
		printf("Unable to open file %s\n", path.c_str());
	}

	return shaderID;
}

bool Shader::bind()
{
	//Use shaderm
	glUseProgram(mProgramID);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error binding shader! %s\n", gluErrorString(error));
		printProgramLog(mProgramID);
		return false;
	}

	return true;
}

void Shader::unbind()
{
	//Use default program
	glUseProgram(NULL);
}

GLuint Shader::getProgramID()
{
	return mProgramID;
}

void Shader::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Shader::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}