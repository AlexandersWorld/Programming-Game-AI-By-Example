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

void Miner::ChangeState(State<Miner> *pNewState)
{
	if (m_pCurrentState && pNewState)
	{
		m_pCurrentState->Exit(this);

		m_pCurrentState = pNewState;

		m_pCurrentState->Enter(this);
	}
}

void Miner::RevertToPreviousState()
{
}

void Miner::AddToGoldCarried(int amount)
{
	m_iGoldCarried += amount;
}

void Miner::IncreaseFadigue()
{
	m_iFatigue += 2;
}

bool Miner::PocketFull() const
{
	return m_iGoldCarried > 10.0f;
}

bool Miner::Thirsty() const
{
	return m_iThirst > 10.0f;
}

location_type Miner::Location() const
{
	return m_Location;
}
