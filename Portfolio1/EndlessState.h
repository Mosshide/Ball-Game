#pragma once
#include "GameState.h"
#include "WindowBorder.h"
#include "Bar.h"
#include "Ball.h"
#include "Tile.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"

class EndlessState : public GameState
{
public:
	EndlessState();
	~EndlessState();
	StateEnum update();
	void draw();

private:	
	bool _paused;
	bool _gameOver;

	Bar _bar;
	Ball _ball;

	WindowBorder _border;
	PauseScreen _pauseScreen;
	GameOverScreen _gameOverScreen;

	std::vector<Tile> _tiles;
	int _tileW, _tileH;
	int _respawnTime;
	int _respawnTimer;

	int _score;
	TextBox _scoreText;
};