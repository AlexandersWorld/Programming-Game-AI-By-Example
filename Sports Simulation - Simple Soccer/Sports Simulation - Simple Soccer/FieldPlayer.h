#pragma once
#include "PlayerBase.h"
#include "StateMachine.h"
#include <iostream>

class FieldPlayer : public PlayerBase
{
public:
	FieldPlayer();

	void Upgrade();
	void Render();

protected:
	bool HandleMessage(std::string telegram);

private:
	StateMachine<FieldPlayer>* m_pStateMachine;
};