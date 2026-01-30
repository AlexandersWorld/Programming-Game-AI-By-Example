// Attacking.h
#pragma once
#include "TeamState.h"

class Attacking : public TeamState
{
private:
    Attacking() {}

public:
    static Attacking* Instance()
    {
        static Attacking instance;
        return &instance;
    }

    void Enter(SoccerTeam* team) override
    {
        // Request support positions, push players up, etc
    }

    void Execute(SoccerTeam* team) override
    {
        // Lost control? Fall back
        if (!team->ControllingPlayer())
        {
            team->GetFSM()->ChangeState(Defending::Instance());
        }
    }

    void Exit(SoccerTeam* team) override
    {
    }
};
