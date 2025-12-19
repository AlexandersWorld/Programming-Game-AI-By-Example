#pragma once
#include "GameWorld.h"

enum EDeceleration { Slow = 3, Normal = 2, Fast = 1 };

class Vehicle;

class SteeringBehaviors
{
private:
    Vehicle* m_pVehicle; // Owner vehicle

public:
    SteeringBehaviors(Vehicle* owner);

    // Main steering force calculation
    SVector2D Calculate();

    // Seek behavior
    SVector2D Seek(const SVector2D& Target);

    SVector2D Flee(const SVector2D& TargetPos);
    
    SVector2D Pursuit(const Vehicle* Evader);

    SVector2D Arrive(const SVector2D& TargetPos, EDeceleration Deceleration);

    double TurnaoundTime(const Vehicle* pAgent, SVector2D TargetPos);

    SVector2D SteeringBehaviors::Evade(const Vehicle* pursuer);
};
