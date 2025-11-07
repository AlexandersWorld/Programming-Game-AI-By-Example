#pragma once
#include "iostream"
#include "State.h"

class Miner;

class GoHomeAndSleepTilRested : public State<Miner>
{
public:
	GoHomeAndSleepTilRested();

	~GoHomeAndSleepTilRested();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static GoHomeAndSleepTilRested* Instance();
};