#pragma once
#include "iostream"
#include "State.h"

class Miner;

class QuenchThirst : public State<Miner>
{

public:
	QuenchThirst();

	~QuenchThirst();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static QuenchThirst* Instance();
};