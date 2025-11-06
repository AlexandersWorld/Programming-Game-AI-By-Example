#pragma once
#include "iostream"
#include "State.h"
#include "Miner.h"
#include "LocationType.h"

class MinerGlobalState : public State<Miner>
{

private:
	MinerGlobalState();

public:
	~MinerGlobalState();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static MinerGlobalState* Instance();
};