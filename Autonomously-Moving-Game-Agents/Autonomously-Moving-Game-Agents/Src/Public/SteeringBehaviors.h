#pragma once
#include "GameWorld.h"
#include <random>
#include <chrono>

enum EDeceleration { Slow = 3, Normal = 2, Fast = 1 };

class Vehicle;
class BaseGameEntity;

class SteeringBehaviors
{
private:
    Vehicle* m_pVehicle; // Owner vehicle
    double m_dWanderRadius;
    double m_dWanderDistance;
    double m_dWanderJitter;
    double m_dDBoxLength;
    SVector2D m_vWanderTarget;

    mutable std::mt19937 m_RNG;
    mutable std::uniform_real_distribution<double> m_Distribution;

protected:
    SteeringBehaviors(Vehicle* owner);
    SteeringBehaviors();


    // Main steering force calculation
    SVector2D Calculate();

    // Seek behavior
    SVector2D Seek(const SVector2D& Target);

    SVector2D Flee(const SVector2D& TargetPos);
    
    SVector2D Pursuit(const Vehicle* Evader);

    SVector2D Arrive(const SVector2D& TargetPos, EDeceleration Deceleration);

    double TurnaoundTime(const Vehicle* pAgent, SVector2D TargetPos);

    SVector2D Evade(const Vehicle* pursuer);

    SVector2D Wander();

    double RandomClamped() const
    {
        return m_Distribution(m_RNG);
    }

    SVector2D PointToWorldSpace(SVector2D targetLocal, SVector2D VehicleHeading, SVector2D VehicleSide, SVector2D VehiclePos);

    SVector2D ObstacleAvoidance(const std::vector<BaseGameEntity*>& obstacles);
};
