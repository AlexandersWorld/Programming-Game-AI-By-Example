#include <iostream>

class State
{
public:
	virtual void Execute(Troll* troll) = 0;
};

class Troll
{
	State* m_pCurrentState;

public:

	void Update()
	{
		m_pCurrentState->Execute(this);
	}

	void ChangeState(State* pNewState)
	{
		delete m_pCurrentState;
		m_pCurrentState = pNewState;
	}

	bool isSafe()
	{
		return true;
	}

	void MoveAwayFromEnemy()
	{
		std::cout << "Moving Away from enemy\n";
	}

	bool isThreatened()
	{
		std::cout << "Feeling threatened\n";
		return true;
	}

	void Snore()
	{
		std::cout << "Troll is snoring\n";
	}
};

class State_RunAway : public State
{
	void Execute(Troll* troll)
	{
		if (troll->isSafe())
		{
			troll->ChangeState(new State_Sleep());
		}
		else
		{
			troll->MoveAwayFromEnemy();
		}
	}
};

class State_Sleep : public State
{
public:
	void Execute(Troll* troll)
	{
		if (troll->isThreatened())
		{
			troll->ChangeState(new State_RunAway());
		}
		else
		{
			troll->Snore();
		}
	}
};

int main()
{
	std::cout << "Hello Bob the miner!" << std::endl;
	return 0;
}