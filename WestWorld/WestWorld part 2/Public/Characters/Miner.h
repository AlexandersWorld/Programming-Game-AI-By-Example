#pragma once
#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "State.h"
#include "LocationType.h"

class Telegram;

class Miner : public BaseGameEntity
{
private:
	StateMachine<Miner>* m_pStateMachine;

	location_type m_Location;

	int m_iGoldCarried;
	int m_iMoneyInBank;
	int m_iThirst;
	int m_iFatigue;

public:
	void Update();
	void ChangeState(State<Miner>* pNewState);
	virtual bool HandleMessage(const Telegram& msg);
	void RevertToPreviousState();
	void IncreaseFadigue();
	void IncreaseThirsty();
	void AddToGoldCarried(int amount);
	bool PocketFull() const;
	bool Thirsty() const;
	bool Fadigued() const;
	int GetGoldAmount() const;
	int GoldToDeposit();
	location_type Location() const;
	void ChangeLocation(location_type location);
	~Miner();
	Miner(int ID);

	StateMachine<Miner>* GetFSM() const;
};
