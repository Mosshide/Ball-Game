#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
	quit = false;

	_quitButton.setText("Quit");
	_quitButton.setPosition(render->getScreenWidth() / 2 - 100, render->getScreenHeight() - 50);
	_quitButton.setRGBA(Color(.1f, .1f, .1f, 1.f));
	_quitButton.setSize(200, 15);

	_bg.setRect(fRectangle(1, 26, render->getScreenWidth() - 2, render->getScreenHeight() - 27));
	_bg.setTexture("blank");
	_bg.setRGBA(Color(.1f, .1f, .1f, .5f));

	_request.setText("Please Enter Your Name");
	_request.setPosition(render->getScreenWidth() / 2 - 100, render->getScreenHeight() / 2);

	_name.setStyle(boxScroll);
	_name.setPosition(render->getScreenWidth() / 2 - 100, 50 + render->getScreenHeight() / 2);
	_name.setSize(_request.presence.w, _request.presence.h);
	_name.setText("");

	_scoreList.setRect(fRectangle(100, 100, 200, 150));
	_scoreList.noScroll = true;

	_saveFileName = "saves/highscores.ns";
	_highScoreCount = 10;
	for (int i = 0; i < _highScoreCount; i++)
	{
		_highScore.push_back(0);
		_highScoreName.push_back("");
	}
	
	load();
}

GameOverScreen::~GameOverScreen()
{
	save();
}

void GameOverScreen::update()
{
	_quitButton.update();
	if (_quitButton.getClick(leftClick) == clickUp) quit = true;

	_name.update();
	if (_name.editState == edited && _name.active)
	{
		_name.active = false;
		submitScore();
	}

	_scoreList.update();
}

void GameOverScreen::draw()
{
	_bg.draw();

	_request.draw();
	_name.draw();

	_quitButton.draw();
	_scoreList.draw();
}

void GameOverScreen::load()
{
	_scoreList.clear();
	for (int i = 0; i < _highScoreCount; i++)
	{
		_highScore[i] = 0;
		_highScoreName[i] = "";
	}

	SDL_RWops *saveFile = SDL_RWFromFile(_saveFileName.c_str(), "r+b");

	if (saveFile == nullptr)
	{
		save();
		saveFile = SDL_RWFromFile(_saveFileName.c_str(), "r+b");
	}

	if (saveFile != NULL)
	{
		//retrieve data
		for (int i = 0; i < _highScoreCount; i++)
		{
			SDL_RWread(saveFile, &_highScore[i], sizeof(int), 1);
			int l = 0;
			SDL_RWread(saveFile, &l, sizeof(int), 1);
			for (int ii = 0; ii < l; ii++)
			{
				char c = ' ';
				SDL_RWread(saveFile, &c, sizeof(char), 1);
				_highScoreName[i].push_back(c);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			HighScoreElement * ele = new HighScoreElement();
			ele->score.setText(std::string(_highScoreName[i]));
			ele->name.setText(_highScore[i]);
			_scoreList.addElement(ele);
		}

		_scoreList.constrainToElements();

		//Close file handler
		SDL_RWclose(saveFile);
	}
	else printf("Could not load: %s\n", SDL_GetError());
}

void GameOverScreen::save()
{
	SDL_RWops *saveFile = SDL_RWFromFile(_saveFileName.c_str(), "w+b");
	if (saveFile != nullptr)
	{
		//save data
		for (int i = 0; i < _highScoreCount; i++)
		{
			SDL_RWwrite(saveFile, &_highScore[i], sizeof(int), 1);
			int l = _highScoreName[i].length();
			SDL_RWwrite(saveFile, &l, sizeof(int), 1);
			for (int ii = 0; ii < l; ii++) SDL_RWwrite(saveFile, &_highScoreName[i][ii], sizeof(char), 1);
		}

		//Close file handler
		SDL_RWclose(saveFile);
	}
	else printf("Could not save: %s\n", SDL_GetError());
}

void GameOverScreen::endGame(int score)
{
	_newScore = score;
}

void GameOverScreen::submitScore()
{
	for (int i = 0; i < _highScoreCount; i++)
	{
		if (_newScore > _highScore[i])
		{
			_highScore.insert(_highScore.begin() + i, _newScore);
			_highScore.pop_back();
			_highScoreName.insert(_highScoreName.begin() + i, _name.text);
			_highScoreName.pop_back();
			save();
			load();
			break;
		}
	}
}