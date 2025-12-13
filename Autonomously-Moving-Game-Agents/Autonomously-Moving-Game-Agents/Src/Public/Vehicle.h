#pragma once
#include "SVector2D.h"
#include "MovingEntity.h"

class GameWorld;

class Vehicle : public MovingEntity
{

private:
    GameWorld* m_pWorld;

public:
    Vehicle();

    virtual void Update(double time_elapsed) override;
    virtual void Render() override;
};
