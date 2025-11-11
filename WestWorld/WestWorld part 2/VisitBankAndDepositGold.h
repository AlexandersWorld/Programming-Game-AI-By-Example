#pragma once
#include "iostream"
#include "State.h"

class Miner;
class Bank;

class VisitBankAndDepositGold : public State<Miner>
{

public:
	VisitBankAndDepositGold();

	~VisitBankAndDepositGold();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	Bank* m_pBank = nullptr;

	static VisitBankAndDepositGold* Instance();
};