#include "EndlessState.h"

EndlessState::EndlessState()
{
	id = endlessState;
	_paused = false;
	_gameOver = false;

	_ball.set(_bar.presence);

	_tileW = 15;
	_tileH = 6;
	for (int i = 0; i < _tileW; i++)
	{
		for (int ii = 0; ii < _tileH; ii++)
		{
			_tiles.push_back(Tile());
			_tiles.back().setPosition(75 + (render->getScreenWidth() - 100) * ((float)i / _tileW), 100.f + 40 * ii);
		}
	}
	_respawnTime = 500;
	_respawnTimer = 0;

	_score = 0;
	_scoreText.setRGBA(Color(.4f, .4f, .4f, 1.f));
	_scoreText.setText("Score: " + std::to_string(_score));
	_scoreText.setPosition(10, 75);
}

EndlessState::~EndlessState()
{
}

StateEnum EndlessState::update()
{
	_border.update();

	if (keyboard->getKey(escKey) == keyUp && !_gameOver) _paused = !_paused;

	if (_gameOver) _gameOverScreen.update();
	else if (_paused) _pauseScreen.update();
	else
	{
		_bar.update();
		_ball.update();

		if (_ball.gameOver)
		{
			_gameOver = true;
			_gameOverScreen.endGame(_score);
		}

		//bar
		if (_ball.isSet)
		{
			if (_bar.vel != 0.f || keyboard->getKey(' ') == keyUp) _ball.launch((1 + rand() % 9) / 10.f);
		}
		else
		{
			float wratio = 0.f;
			int side = _bar.collision(_ball.getTrajectory(), &wratio);
			if (side > -1)
			{
				if (side == 0 || side == 2) _ball.launch(wratio);
				else _ball.bounceHor();
			}
		}

		//tiles
		for (int i = 0; i < _tileW * _tileH; i++)
		{
			if (_tiles[i].alive)
			{
				int side = _tiles[i].collision(_ball.getTrajectory());
				if (side > -1)
				{
					_tiles[i].alive = false;
					_score++;
					_scoreText.setText("Score: " + std::to_string(_score));
					if (side == 0 || side == 2) _ball.bounceVert();
					else _ball.bounceHor();
				}
			}
		}
		_respawnTimer += gameTimer.getDelta();
		if (_respawnTimer > _respawnTime)
		{
			_respawnTimer -= _respawnTime;
			int r = rand() % (_tileW * _tileH);
			if (!_tiles[r].alive) _tiles[r].alive = true;
		}
	}

	if (_pauseScreen.quit || _gameOverScreen.quit) return mainMenuState;
	if (_border.quit) return quitState;
	else return endlessState;
}

void EndlessState::draw()
{
	_border.draw();

	_bar.draw();
	_ball.draw();

	for (int i = 0; i < _tileW * _tileH; i++)
	{
		_tiles[i].draw();
	}

	_scoreText.draw();
	
	if (_gameOver) _gameOverScreen.draw();
	else if (_paused) _pauseScreen.draw();
}