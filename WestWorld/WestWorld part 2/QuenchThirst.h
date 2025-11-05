#pragma once
#include "iostream"
#include "State.h"
#include "Miner.h"
#include "LocationType.h"

class QuenchThirst : public State<Miner>
{

private:
	QuenchThirst();

public:
	~QuenchThirst();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static QuenchThirst* Instance();
};