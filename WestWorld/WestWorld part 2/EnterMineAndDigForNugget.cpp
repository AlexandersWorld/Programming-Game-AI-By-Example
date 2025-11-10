#include "EnterMineAndDigForNugget.h"
#include "VisitBankAndDepositGold.h"
#include "LocationType.h"
#include "Miner.h"
#include "QuenchThirst.h"

EnterMineAndDigForNugget::~EnterMineAndDigForNugget()
{
}

EnterMineAndDigForNugget::EnterMineAndDigForNugget()
{
}

void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
	pMiner->AddToGoldCarried(1);

	pMiner->IncreaseFadigue();

	std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pikcin' up a nugget";

	if (pMiner->PocketFull())
	{
		pMiner->ChangeState(VisitBankAndDepositGold::Instance());
	}

	if (pMiner->Thirsty())
	{
		pMiner->ChangeState(QuenchThirst::Instance());
	}

	pMiner->Update();
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
	if (pMiner->Location() != goldmine)
	{
		std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "Walking' to the gold mine";

		pMiner->ChangeLocation(goldmine);
	}
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
	std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
		<< "Ah'm leavin' the gold mine with mah pockets full o' sweet gold";
}

std::string EnterMineAndDigForNugget::GetNameOfEntity(int ID)
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

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
	static EnterMineAndDigForNugget instance;

	return &instance;
}
