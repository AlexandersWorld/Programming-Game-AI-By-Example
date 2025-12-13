#pragma once
#include "SVector2D.h"

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
    SVector2D Seek(const SVector2D& target);

    SVector2D Flee(const SVector2D& TargetPos);
};
