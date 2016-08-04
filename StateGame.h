#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "StateBase.h"
class StateGame :
	public StateBase
{
public:
	StateGame(StateManager* stateManager);
	~StateGame();
};
#endif // !STATE_GAME_H
