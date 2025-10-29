#include "Miner.h"

Miner::Miner(int ID) 
	: BaseGameEntity(ID)
{
	
}

void Miner::Update()
{
	m_iThirst += 1;

	if (m_pCurrentState)
	{
		m_pCurrentState->Execute(this);
	}
}

void Miner::ChangeState(State* pNewState)
{
	m_pCurrentState = pNewState;
}
