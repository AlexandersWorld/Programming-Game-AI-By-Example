#pragma once
#include "iostream"
#include "State.h"

class Miner;

class VisitBankAndDepositGold : public State<Miner>
{

private:
	VisitBankAndDepositGold();

public:

	~VisitBankAndDepositGold();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static VisitBankAndDepositGold* Instance();
};