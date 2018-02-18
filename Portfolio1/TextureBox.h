#pragma once
#include "Render.h"
#include <map>

class TextureBox
{
public:
	TextureBox();
	~TextureBox();
	void newTxtTxr(GLuint *txr, std::string textureText, SDL_Color textColor, int f);
	void newUniTxtTxr(GLuint *txr, Uint16 textureText, SDL_Color textColor, int f);
	void newTxtTxr(GLuint *txr);
	GLuint loadTxr(std::string path, bool filter = false);
	void clearTexture(GLuint txr);

	std::map<std::string, GLuint> texture;
};

extern TextureBox *textureBox;
