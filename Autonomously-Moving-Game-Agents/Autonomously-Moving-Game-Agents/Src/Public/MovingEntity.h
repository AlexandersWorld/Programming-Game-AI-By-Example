
#pragma once
#include "GameWorld.h"
#include "BaseGameEntity.h"

class MovingEntity : public BaseGameEntity
{
public:
    
    virtual void Update(double time_elapsed) override;
    virtual void Render() override;
    
protected:
    SVector2D m_vVelocity;
    
    SVector2D m_vHeading;
    
    SVector2D m_vSide;

    SVector2D m_vPos;
    
    double m_dMass;
    
    double m_dMaxSpeed;

    double m_dSpeed;
    
    double m_dMaxForce;
    
    double m_dMaxTurnRate;
private:
    
};
