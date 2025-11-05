#pragma once

#include "iostream"
#include "State.h"
#include "Miner.h"
#include "LocationType.h"

class EnterMineAndDigForNugget : public State<Miner>
{

private:

public:
	EnterMineAndDigForNugget();

	~EnterMineAndDigForNugget();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static EnterMineAndDigForNugget* Instance();
};