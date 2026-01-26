#pragma once
#include "PlayerBase.h"
#include "StateMachine.h"
#include <iostream>

class GoalKeeper : public PlayerBase
{
public:
	void Update();
	void Render();

protected:
	bool HandleMessage(std::string telegram);

private:
	StateMachine<GoalKeeper*> m_pStateMachine;
	Vector2D m_vLookAt;
};
