#pragma once
#include "MovingEntity.h"
#include "GameWorld.h"

class GameWorld;

class Vehicle : public MovingEntity
{

private:
    GameWorld* m_pWorld;

public:
    Vehicle();

    SVector2D Pos() { return m_vPos; }
    SVector2D Velocity() { return m_vVelocity; }
    SVector2D Heading() { return m_vHeading; }
    
    double MaxSpeed() { return m_dMaxSpeed; }
    double Speed() { return m_dSPeed; }


    virtual void Update(double time_elapsed) override;
    virtual void Render() override;
};
