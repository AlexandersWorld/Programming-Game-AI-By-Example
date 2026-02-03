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

    void Enter(SoccerTeam* team) override;

    void Execute(SoccerTeam* team) override;

    void Exit(SoccerTeam* team) override;
};
