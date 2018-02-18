#pragma once
#include <fstream>
#include "Entity.h"
#include "Shader.h"
#include "UIShader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

struct VIBO
{
	GLuint vbo;
	GLuint ibo;
	GLsizei size;
};

enum RenderType{
	imageRndr,
	textRndr,
	uniTextRndr,
	rectRndr,
	lineRndr
};

enum PositionType {
	uiPosition,
	worldPosition
};

enum RectType{
	filled,
	outlined
};

class Render
{
public:
	Render();
	~Render();
	void renderGame();

	//screen
	void setScreenSize(int w, int h);
	void setFullscreen(bool f);
	int getScreenWidth();
	int getScreenHeight();
	fRectangle getScreen();
	SDL_Window* getWindow();
	float getWidthRatio();
	float getHeightRatio();
	bool getFullscreen();

	//animation
	void setBaseFrameTime(int t);
	int getBaseFrameTime();

	//font
	TTF_Font *getFont(int f) { return font[f]; }
	GLfloat getFontSize(int f);
	GLfloat getTextWidth(std::string t, int f);

	void setLight(glm::vec3 pos);
	void setCamera(glm::vec3 pos, glm::vec3 YPR, glm::vec3 up);
	void translateCamera(glm::vec3 p);
	void rotateCamera(glm::vec3 q);
	void setCameraTranslate(glm::vec3 p);
	void setCameraRotate(glm::vec3 q);
	glm::vec3 getCameraPos() { return _cameraPos; }
	glm::vec3 getCameraFront() { return _cameraFront; }
	glm::vec3 getCameraYPR() { return _yawPitchRoll; }

	Shader *getShader();
	UIShader *getUIShader();
	
protected:
	bool initGL();
	void stopGL();
	SDL_Surface *_surfRender_text(std::string textureText, SDL_Color textColor, TTF_Font* ft);
	
	//fps
	bool _showFPS;
	int _frame;
	int _time;
	int _fps;

	//screen values
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_BPP;
	float WIDTH_RATIO;
	float HEIGHT_RATIO;
	bool FULLSCREEN;

	//OpenGL context
	SDL_GLContext gContext;
	Shader _shader;
	UIShader _UIShader;

	//sdl stuff
	SDL_Window *window;
	SDL_Rect rctDisplay;
	SDL_Surface *windowIcon;

	//fonts
	TTF_Font *font[3];
	int fontSize[3];
	char buffer[32];

	//camera
	glm::vec3 _cameraPos;
	glm::vec3 _yawPitchRoll;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;

	int BASE_FRAME_TIME;
};
extern Render *render;

extern char _buffer[33];
extern GLfloat TILE_WIDTH;
extern GLfloat TILE_HEIGHT;
extern const int TOOLTIP_DELAY;


