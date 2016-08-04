#ifndef STATE_INTRO_H
#define STATE_INTRO_H


#include "StateBase.h"
class StateIntro :
	public StateBase
{
public:
	StateIntro(StateManager* stateManager);
	~StateIntro();
};
#endif // !STATE_INTRO_H