#pragma once
#include "iostream"
#include "State.h"

class Miner;

enum EntityType
{
	ENTITY_MINER_BOB,
	ENTITY_WIFE_ELSA,
	NUM_ENTITY_TYPES // Helper for counting
};

class EnterMineAndDigForNugget : public State<Miner>
{

private:

public:
	EnterMineAndDigForNugget();

	~EnterMineAndDigForNugget();

	void Execute(Miner* pMiner) override;
	void Enter(Miner* pMiner) override;
	void Exit(Miner* pMiner) override;
	std::string GetNameOfEntity(int ID);

	static EnterMineAndDigForNugget* Instance();
};