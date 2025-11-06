#pragma once
#include "iostream"
#include "State.h"
#include "Miner.h"
#include "LocationType.h"

class GoHomeAndSleepTilRested : public State<Miner>
{

private:
	GoHomeAndSleepTilRested();

public:
	~GoHomeAndSleepTilRested();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static GoHomeAndSleepTilRested* Instance();
};
