#include "Miner.h"

Miner::Miner(int ID)
	: BaseGameEntity(ID),
		m_Location(shack),
		m_iMoneyInBank(0),
		m_iFatigue(0),
		m_iThirst(0),
		m_iGoldCarried(0)
{
	m_pStateMachine = new StateMachine<Miner>(this);
	m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
	m_pStateMachine->SetGlobalState(MinerGlobalState::Instance());
}

Miner::~Miner()
{
	delete m_pStateMachine;
}

StateMachine<Miner>* Miner::GetFSM() const
{
	return m_pStateMachine;
}

void Miner::Update()
{
	++m_iThirst;

	m_pStateMachine->Update();
}

void Miner::ChangeState(State<Miner> *pNewState)
{
	if (m_pStateMachine && pNewState)
	{
		m_pStateMachine->ChangeState(pNewState);
	}
}

void Miner::RevertToPreviousState()
{
	m_pStateMachine->RevertToPreviousState();
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
