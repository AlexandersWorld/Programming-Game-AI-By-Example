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

    SVector2D Pos { return m_vPos; }
    SVector2D Velocity { return m_vVelocity; }
    double MaxSpeed { return m_dMaxSpeed; }


    virtual void Update(double time_elapsed) override;
    virtual void Render() override;
};
