#include "MinerGlobalState.h"

MinerGlobalState::MinerGlobalState()
{
}

MinerGlobalState::~MinerGlobalState()
{
}

void MinerGlobalState::Execute(Miner* pMiner)
{
}

void MinerGlobalState::Enter(Miner* pMiner)
{
}

void MinerGlobalState::Exit(Miner* pMiner)
{
}

MinerGlobalState* MinerGlobalState::Instance()
{
	static MinerGlobalState instance;

	return &instance;
}
