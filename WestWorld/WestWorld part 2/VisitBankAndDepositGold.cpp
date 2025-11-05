#include "VisitBankAndDepositGold.h"

VisitBankAndDepositGold::~VisitBankAndDepositGold()
{
}

void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
}

void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
}


VisitBankAndDepositGold::VisitBankAndDepositGold()
{
}

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;

	return &instance;
}


