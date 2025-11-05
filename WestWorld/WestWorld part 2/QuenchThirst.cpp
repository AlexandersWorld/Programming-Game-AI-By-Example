#include "QuenchThirst.h"

QuenchThirst::QuenchThirst()
{
}

QuenchThirst::~QuenchThirst()
{
}

void QuenchThirst::Execute(Miner* pMiner)
{
}

void QuenchThirst::Enter(Miner* pMiner)
{
	if (pMiner->Location() != goldmine)
	{
		std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
			<< "Walking' to the gold mine";
	}
}

void QuenchThirst::Exit(Miner* pMiner)
{
	std::cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
		<< "Ah'm leavin' the gold mine with mah pockets full o' sweet gold";
}

std::string QuenchThirst::GetNameOfEntity(int ID)
{
	return std::string();
}

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;

	return &instance;
}
