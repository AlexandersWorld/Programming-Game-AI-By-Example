#pragma oncew
#include "PlayerBase.h"
#include "StateMachine.h"
#include <iostream>

class GoalKeeper : public PlayerBase
{
public:
	GoalKeeper();

	void Update();
	void Render();

	bool HandleMessage(std::string telegram);

private:
	StateMachine<GoalKeeper*> m_pStateMachine;
};