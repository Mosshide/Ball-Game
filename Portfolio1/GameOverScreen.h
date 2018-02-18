#pragma once
#include "Button.h"
#include "ListContainer.h"
#include "HighScoreElement.h"
#include "TextEntryBox.h"

class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();
	void update();
	void draw();
	void load();
	void save();
	void endGame(int score);

	bool quit;

private:
	void submitScore();

	int _newScore;

	UIRectangle _bg;
	Button _quitButton;
	TextBox _request;
	TextEntryBox _name;

	std::string _saveFileName;
	int _highScoreCount;
	std::vector<int> _highScore;
	std::vector<std::string> _highScoreName;
	ListContainer _scoreList;
};