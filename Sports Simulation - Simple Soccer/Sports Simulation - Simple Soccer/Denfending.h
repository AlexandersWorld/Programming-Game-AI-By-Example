// Defending.h
#pragma once
#include "TeamState.h"

class Defending : public TeamState
{
private:
    Defending() {}

public:
    static Defending* Instance()
    {
        static Defending instance;
        return &instance;
    }

    void Enter(SoccerTeam* team) override
    {
        team->ReturnAllFieldPlayersToHome();
    }

    void Execute(SoccerTeam* team) override
    {
        // If we gain control, switch to attacking
        if (team->ControllingPlayer())
        {
            team->GetFSM()->ChangeState(Attacking::Instance());
        }
    }

    void Exit(SoccerTeam* team) override
    {
        // Cleanup if needed
    }
};
