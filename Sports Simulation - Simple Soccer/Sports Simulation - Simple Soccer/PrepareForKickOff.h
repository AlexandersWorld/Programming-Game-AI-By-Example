// PrepareForKickOff.h
#pragma once
#include "TeamState.h"

class PrepareForKickOff : public TeamState
{
private:
    PrepareForKickOff() {}

public:
    static PrepareForKickOff* Instance()
    {
        static PrepareForKickOff instance;
        return &instance;
    }

    void Enter(SoccerTeam* team) override
    {
        team->ReturnAllFieldPlayersToHome();
    }

    void Execute(SoccerTeam* team) override
    {
        if (team->AllPlayersAtHome() &&
            team->Opponents()->AllPlayersAtHome())
        {
            team->GetFSM()->ChangeState(Defending::Instance());
        }
    }

    void Exit(SoccerTeam* team) override
    {
    }
};
