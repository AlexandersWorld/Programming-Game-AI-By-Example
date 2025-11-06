#pragma once
#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "State.h"
#include "LocationType.h"
#include "GoHomeAndSleepTilRested.h"
#include "MinerGlobalState.h"


class Miner : public BaseGameEntity
{
private:
	StateMachine<Miner>* m_pStateMachine;

	location_type m_Location;

	int m_iGoldCarried;
	int m_iMoneyInBank;
	int m_iThirst;
	int m_iFatigue;

protected:
	void Update();

public:
	void ChangeState(State<Miner>* pNewState);
	void RevertToPreviousState();
	void IncreaseFadigue();
	bool PocketFull() const;
	bool Thirsty() const;
	void AddToGoldCarried(int amount);
	location_type Location() const;
	Miner(int ID);
	~Miner();

	StateMachine<Miner>* GetFSM() const;
};