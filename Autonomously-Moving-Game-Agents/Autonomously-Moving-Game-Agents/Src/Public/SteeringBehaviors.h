#pragma once
#include "SVector2D.h"

enum Deceleration { Slow = 3, Normal = 2, Fast = 1 };

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

    SVector2D Arrive(const SVector2D& TargetPos, Deceleration deceleration);
};
