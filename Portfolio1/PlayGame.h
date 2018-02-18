#pragma once
#include "UserInput.h"
#include "Physics.h"
#include "StateEnum.h"
#include "AllStates.h"
#include <SDL_thread.h>

class PlayGame
{
public:
	PlayGame();
	~PlayGame();
	void runGame();

private:
	StateEnum _stateRequest;
	GameState *_currentState;
	bool _quit;
};