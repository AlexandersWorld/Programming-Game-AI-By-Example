#include "LocationType.h"
#include "EntitiesEnum.h"
#include "Bank.h"
#include "Miner.h"
#include "EnterMineAndDigForNugget.h"

#include "VisitBankAndDepositGold.h"

VisitBankAndDepositGold::VisitBankAndDepositGold()
	:m_pBank(Bank::Instance())
{
}

VisitBankAndDepositGold::~VisitBankAndDepositGold()
{
}

void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
	if (m_pBank != nullptr)
	{
		int gold = pMiner->GoldToDeposit();
		std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "Depositing gold." << " Total savings now: " << m_pBank->Deposit(gold);


		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
		pMiner->ChangeLocation(goldmine);
	}
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
	if (pMiner->Location() != bank)
	{
		std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "Goin' to the bank. Yes siree";

		pMiner->ChangeLocation(bank);
	}
}

void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
	if (pMiner->Location() == bank)
	{
		std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "Leavin' the bank";
	}
}


std::string VisitBankAndDepositGold::GetNameOfEntity(int ID)
{
	switch (ID)
	{
	case ENTITY_MINER_BOB:
		return "Miner Bob";
	case ENTITY_WIFE_ELSA:
		return "Wife Elsa";
	default:
		return "Unkown";
	}
}

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;

	return &instance;
}


