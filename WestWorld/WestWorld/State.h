#pragma once
#include "BaseGameEntity.h"

class Miner;

class State
{

public:
	virtual ~State() {}

	virtual void Execute(Miner* miner) = 0;
	virtual void Enter(Miner* miner) = 0;
	virtual void Exit(Miner* miner) = 0;
};