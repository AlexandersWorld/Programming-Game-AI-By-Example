#include "GoHomeAndSleepTilRested.h"
#include "LocationType.h"
#include "Miner.h"


GoHomeAndSleepTilRested::GoHomeAndSleepTilRested()
{
}

GoHomeAndSleepTilRested::~GoHomeAndSleepTilRested()
{
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
}

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return &instance;
}
