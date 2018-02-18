#include "TextureBox.h"

TextureBox::TextureBox()
{
	texture["blank"] = loadTxr("img/blank.png");
	texture["altar"] = loadTxr("img/altar.png");
	texture["altar light"] = loadTxr("img/altar light.png");
	texture["tab"] = loadTxr("img/tab.png");
	texture["minimize"] = loadTxr("img/minimize.png", true);
	texture["maximize"] = loadTxr("img/maximize.png", true);
	texture["close"] = loadTxr("img/close.png", true);
}

TextureBox::~TextureBox()
{
	for (std::map<std::string, GLuint>::iterator it = texture.begin(); it != texture.end(); ++it)
	{
		glDeleteTextures(1, &it->second);
	}
}

void TextureBox::newTxtTxr(GLuint *txr, std::string text, SDL_Color textColor, int f)
{
	if ((int)text.size() > 0)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = TTF_RenderText_Blended(render->getFont(f), text.c_str(), textColor);
		if (loadedSurface == nullptr)
		{
			printf("Unable to create text %s! SDL_image Error: %s\n", text.c_str(), IMG_GetError());
		}
		else
		{
			/*newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if( newTexture == nullptr )
			{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			}
			else SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);*/

			glGenTextures(1, txr);
			glBindTexture(GL_TEXTURE_2D, *txr);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Unbind texture
			glBindTexture(GL_TEXTURE_2D, NULL);

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
	}
}

void TextureBox::newUniTxtTxr(GLuint *txr, Uint16 textureText, SDL_Color textColor, int f)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = TTF_RenderGlyph_Blended(render->getFont(f), textureText, textColor);
	if (loadedSurface == nullptr)
	{
		printf("Unable to create text %s! SDL_image Error: %s\n", "UNICODE", IMG_GetError());
	}
	else
	{
		/*newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == nullptr )
		{
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);*/

		glGenTextures(1, txr);
		glBindTexture(GL_TEXTURE_2D, *txr);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Unbind texture
		glBindTexture(GL_TEXTURE_2D, NULL);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void TextureBox::newTxtTxr(GLuint *txr)
{
	glGenTextures(1, txr);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, *txr);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TextureBox::loadTxr(std::string path, bool filter)
{
	GLuint GLtxr = 0;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		glGenTextures(1, &GLtxr);
		glBindTexture(GL_TEXTURE_2D, GLtxr);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h,
			0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexImage2D! %s\n", gluErrorString(error));
		}

		if (filter)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexParameteri %s\n", gluErrorString(error));
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexParameteri 2! %s\n", gluErrorString(error));
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return GLtxr;
}

void TextureBox::clearTexture(GLuint txr)
{
	/*SDL_SetRenderTarget(renderer, txr);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_NONE);
	SDL_RenderClear(renderer);
	SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, nullptr);*/
}

TextureBox *textureBox;